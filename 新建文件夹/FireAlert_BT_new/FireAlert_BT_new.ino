
#include <CurieBLE.h>

const int TrigPin = 2; 
const int EchoPin = 4; 
float cm;
String direction;

int pinBuzzer_left = 8;
int pinBuzzer_right = 7;


void setup() {
  Serial.begin(9600);    // initialize serial communication
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT);
  direction = "left";
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
  
    pinMode(pinBuzzer_left, OUTPUT);
    pinMode(pinBuzzer_right, OUTPUT);
    
    float dist = distance();
    while (central.connected() && dist>50){
      tone(pinBuzzer_left, 900, 500);
      delay(300);
      noTone(pinBuzzer_left);
      tone(pinBuzzer_right, 900, 500);
      delay(300);
      noTone(pinBuzzer_right);
      dist = distance();
    }
    tone(pinBuzzer_left, 900, 1500);
    delay(2000);
    noTone(pinBuzzer_left);
    tone(pinBuzzer_right, 900, 1500);
    delay(2000);
    noTone(pinBuzzer_right);
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
      tone(pinBuzzer_left, 900, 500);
      delay(500);
      noTone(pinBuzzer_left);
      tone(pinBuzzer_right, 300, 500);
      delay(500);
      noTone(pinBuzzer_right);
  }
  if (dir == "right"){
    tone(pinBuzzer_left, 300, 500);
    delay(500);
    noTone(pinBuzzer_left);
    tone(pinBuzzer_right, 900, 500);
    delay(500);
    noTone(pinBuzzer_right);
  }
  if (dir == "exit"){
    tone(pinBuzzer_left, 700, 500);
    delay(500);
    noTone(pinBuzzer_left);
    tone(pinBuzzer_right, 700, 500);
    delay(500);
    noTone(pinBuzzer_right);
  }
}
