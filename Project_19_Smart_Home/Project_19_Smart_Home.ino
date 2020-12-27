#define BLYNK_PRINT Serial    
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <SimpleTimer.h>

//Ganti dengan Token anda
char auth[] = "";
// Ganti dengan WiFi anda
char ssid[] = "";
char pass[] = "";
WidgetLCD lcd(V3);                                             
int adc0;
float millivolts;
float celsius;

SimpleTimer timer;
 
int sensor_in;
#define pirPin D3 // sensor PIR
int pirValue; 
#define MQ2Pin D5 // sensor MQ2
int MQ2Value; 
void setup()
{
  Serial.begin(115200);
  delay(50);
  timer.setInterval(1000, sendData);
  Blynk.begin(auth, ssid, pass);  
  lcd.clear();
  lcd.print(0, 0, "== Smart Home ==");
  lcd.print(0, 1, "   FiliaSofia");
  delay(1000);  
  pinMode(pirPin, INPUT);
  pinMode(MQ2Pin, INPUT);    
}

void sendData()
{  
  adc0= analogRead(A0);
  millivolts= (adc0/1024.0) * 3300;   
  celsius= millivolts/10;
  Blynk.virtualWrite(0, celsius); 
}

void getPirValue(void)
{
  pirValue = digitalRead(pirPin);
  if (pirValue) 
  { 
    Serial.println("==> Motion detected");
    lcd.clear();
    lcd.print(0, 0, "  WASPADA !!!   ");
    lcd.print(0, 1, "Objek Terdeteksi"); 
    Blynk.notify("Object terdeteksi......");  
    while(digitalRead(pirPin));
    delay(1000);
  }  
}

void getMQ2Value(void)
{
  MQ2Value = digitalRead(MQ2Pin);
  if (!MQ2Value) 
  { 
    Serial.println("==>Gas terdeteksi");
    lcd.clear();
    lcd.print(0, 0, "  WASPADA !!!   ");
    lcd.print(0, 1, "Gas Bocor...."); 
    Blynk.notify("Kebocoran Gas terdeteksi.....!");  
    delay(1000);
  }  
}

void loop()
{
  Blynk.run();
  timer.run(); 
  getPirValue();
  getMQ2Value();
}
