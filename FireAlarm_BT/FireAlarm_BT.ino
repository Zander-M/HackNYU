int lb = 8;
int rb = 7;

int TrigPin = 9;
int EchoPin = 10;
float cm;
float dist;
void setup() {
  Serial.begin(9600);
  pinMode(7,OUTPUT);
  pinMode(8,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(11,HIGH);
  // put your setup code here, to run once:
}







void Direction(String dir){
  if (dir == "left"){
      tone(lb,560,500);
      delay(500);
      noTone(lb);
      tone(rb,440,500);
      delay(500);
      noTone(rb);

      
        }
//  if (dir == "right"){
//    tone(pinBuzzer,2597,30);
//    delay(100);
//    tone(pinBuzzer,2597,30);
//     delay(250);
//  }
//  if (dir == "exit"){
//    tone(pinBuzzer,440,25);
//    delay(100);
//    tone(pinBuzzer,440,25);
//    delay(100);
//    tone(pinBuzzer,440,25);
//    delay(300);
//  }
}

 float distance(){
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58; //将回波时间换算成cm
  cm = (int(cm * 100)) / 100; //保留两位小数 
  Serial.print(cm); 
  Serial.print("cm");//串口输出 
  Serial.println(); 
  return cm;
}

void loop() {
  Direction("left");
//  dist = distance();
//  while (Serial.available()>0 && dist<= 50)
//  {
//    Direction("right");
//    }
////   put your main code here, to run repeatedly:
//  while(!Serial.available() | dist > 50)
//  {
//     tone(pinBuzzer,500,100);
//      delay(100);
//      dist = distance();
//    }

}
