#define Relay1 D5
#define Relay2 D6 
#define Relay3 D7 
#define Relay4 D8 

void setup() {
  Serial.begin(115200);
  delay(10);
  pinMode(Relay1, OUTPUT);
  pinMode(Relay2, OUTPUT);
  pinMode(Relay3, OUTPUT);
  pinMode(Relay4, OUTPUT);
  digitalWrite(Relay1, LOW);
  digitalWrite(Relay2, LOW);
  digitalWrite(Relay3, LOW);
  digitalWrite(Relay4, LOW); 
}
void loop() {

  digitalWrite(Relay1, HIGH);
  delay(100);
  digitalWrite(Relay1, LOW);
  delay(100);
  digitalWrite(Relay2, HIGH);
  delay(105);
  digitalWrite(Relay2, LOW);
  delay(105);
  digitalWrite(Relay3, HIGH);
  delay(110);
  digitalWrite(Relay3, LOW);
  delay(110);
  digitalWrite(Relay4, HIGH);
  delay(115);
  digitalWrite(Relay4, LOW);
  delay(115);
  digitalWrite(Relay3, HIGH);
  delay(110);
  digitalWrite(Relay3, LOW);
  delay(110);
  digitalWrite(Relay2, HIGH);
  delay(105);
  digitalWrite(Relay2, LOW);
  delay(105);
}
