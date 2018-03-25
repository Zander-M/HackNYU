//emergency exit
int b = 9;
void setup() {
  pinMode(9,OUTPUT);
  Serial.begin(9600);
 
}
void loop() {
    while(Serial.available()>0)
   {Serial.read();
   while(Serial.available() == 0)
    // put your main code here, to run repeatedly:
  {
    digitalWrite(9,HIGH);
    delay(30);
    digitalWrite(9,LOW);
    delay(30);
    digitalWrite(9,HIGH);
    delay(30);
    digitalWrite(9,LOW);
    delay(30);
    digitalWrite(9,HIGH);
    delay(30);
    digitalWrite(9,LOW);
    delay(500);
    
  // put your setup code here, to run once:
}
Serial.read();}}

