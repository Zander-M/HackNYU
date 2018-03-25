
#include <CurieBLE.h>

const int TrigPin = 2; 
const int EchoPin = 4; 
float cm;
String direction;

int pinBuzzer = 7;

void setup() {
  Serial.begin(9600);    // initialize serial communication
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT);
  direction = "exit";
  BLE.begin();

  /* Set a local name for the BLE device
     This name will appear in advertising packets
     and can be used by remote devices to identify this BLE device
     The name can be changed but maybe be truncated based on space left in advertisement packet
  */
  BLE.setLocalName("Buzzer");

  /* Start advertising BLE.  It will start continuously transmitting BLE
     advertising packets and will be visible to remote BLE central devices
     until it receives a new connection */

  // start advertising
  BLE.advertise();

  Serial.println("Bluetooth device active, waiting for connections...");
}

void loop() {
  BLEDevice central = BLE.central();

  // if a central is connected to peripheral:
  if (central) {
    Serial.print("Connected to central: ");
    // print the central's MAC address:
    Serial.println(central.address());
  
    pinMode(pinBuzzer, OUTPUT);
    
    float dist = distance();
    while (central.connected() && dist>50){
      digitalWrite(pinBuzzer, LOW);
      delay(100);
      digitalWrite(pinBuzzer, HIGH);
      delay(100);
      dist = distance();
    }
    digitalWrite(pinBuzzer, LOW);
    delay(1500);
    digitalWrite(pinBuzzer, HIGH);
    delay(300);
    while (dist < 50){
      Direction(direction);
      dist = distance();
    }
  }
    Serial.print("Disconnected from central: ");
    Serial.println(central.address());
}

float distance(){
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58; //convert time to cm
  cm = (int(cm * 100)) / 100; //two digits 
  Serial.print(cm); 
  Serial.print("cm");//serial point output 
  Serial.println(); 
  return cm;
}

void Direction(String dir){
  if (dir == "left"){
      digitalWrite(pinBuzzer, LOW);
      delay(30);
      digitalWrite(pinBuzzer,HIGH);
      delay(500);
  }
  if (dir == "right"){
    digitalWrite(pinBuzzer, LOW);
    delay(30);
    digitalWrite(pinBuzzer,HIGH);
    delay(100);
    digitalWrite(pinBuzzer, LOW);
    delay(30);
    digitalWrite(pinBuzzer,HIGH);
    delay(250);
  }
  if (dir == "exit"){
    digitalWrite(pinBuzzer, LOW);
    delay(25);
    digitalWrite(pinBuzzer,HIGH);
    delay(75);
    digitalWrite(pinBuzzer, LOW);
    delay(25);
    digitalWrite(pinBuzzer,HIGH);
    delay(75);
    digitalWrite(pinBuzzer, LOW);
    delay(25);
    digitalWrite(pinBuzzer,HIGH);
    delay(300);
  }
}
