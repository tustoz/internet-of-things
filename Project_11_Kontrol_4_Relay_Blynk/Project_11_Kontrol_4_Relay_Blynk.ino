#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// Ganti dengan token anda yang dikirim via email.
char auth[] = "";

// Ganti dengan WiFi dan Password anda
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
