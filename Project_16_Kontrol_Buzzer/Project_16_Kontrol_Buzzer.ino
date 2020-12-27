#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
//Ganti dengan Token anda
char auth[] = "";

// Ganti dengan WiFi anda
char ssid[] = "";
char pass[] = "";

void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);  
}

void loop()
{
  Blynk.run(); 
}
