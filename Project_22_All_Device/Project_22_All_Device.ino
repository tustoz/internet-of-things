//------------------------------------------------- necesarry libraries
#include<String.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include "constants.h"
#include <ESP8266WiFi.h> 
#include "stock.h"
#include "calculator.h"
#include "Quote.h"
#include "weather.h"
#include <DHT.h>
//------------------------------------------------- API Setup
char* response = " ";
String res = "";
String RAILWAY_API_KEY = "";//---------- API key from www.railwayapi.com
String WEATHER_API_KEY = "";//---------- API key from api.openweathermap.org
String THINGSPEAK_API_KEY = "";//---------- API key from api.thingspeak.com
const char* ssid = "";
const char* password = "";
//------------------------------------------------- define var
#define buzzer D1
#define MQ2 D2
#define pirMotion D5
#define DHTPIN D4 
#define LED1 D5
#define LED2 D6
#define LED3 D7 
#define LED4 D8
int led = 11;
//------------------------------------------------- define var song
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0
//------------------------------------------------- define song tempo
int tempo = 200;
//------------------------------------------------- define Client
DHT dht(DHTPIN, DHT11,15); 
ESP8266WiFiMulti WiFiMulti;
WiFiClient client;
WiFiServer server(80);
 
void setup() {

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(pirMotion, INPUT);
  pinMode(MQ2, INPUT);
  
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  int pirState = LOW;
  int MQ2State = LOW;
  int ledState = LOW;
  
  Serial.begin(115200);
  delay(10);
  dht.begin();
  
  // Connect to WiFi network
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid); 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  server.begin();
  Serial.println("Server started");
 
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/"); 
}
 
void loop() { 
  WiFiClient client = server.available();
  if (!client) {
    return;
  } 
  
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  } 
 
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();

  if (request.indexOf("/marioON") > 0)  {
    int melody[] = {

  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  
  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
  REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  NOTE_C5,2, REST,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
  REST,1, 
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
  
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
  REST,1,

  NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
  NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  
  //game over sound
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
  NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  

};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int divider = 0, noteDuration = 0;

  // iterate over the notes of the melody.
  // Remember, the array is twice the number of notes (notes + durations)
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    // calculates the duration of each note
    divider = melody[thisNote + 1];
    if (divider > 0) {
      // regular note, just proceed
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      // dotted notes are represented with negative durations!!
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; // increases the duration in half for dotted notes
    }

    // we only play the note for 90% of the duration, leaving 10% as a pause
    tone(buzzer, melody[thisNote], noteDuration * 0.9);

    // Wait for the specief duration before playing the next note.
    delay(noteDuration);

    // stop the waveform generation before the next note.
    noTone(buzzer);
  }}
  if (request.indexOf("/marioOFF") >0)  {
    noTone(buzzer);
    delay(1000);
  }
  if (request.indexOf("/PIR") > 0)  {
    if (digitalRead(pirMotion) == HIGH)
  {
  digitalWrite(led, HIGH);   
  delay(3000);                      
  digitalWrite(led, LOW);   
  delay(3000);                       
  tone(buzzer,1000);
  delay(3000);
  noTone(buzzer);
  delay(3000);
  }
}

if (request.indexOf("/MQ2") > 0)  {
    if (digitalRead(MQ2) == HIGH)
  {
  digitalWrite(led, HIGH);   
  delay(3000);                      
  digitalWrite(led, LOW);   
  delay(3000);                       
  tone(buzzer,1000);
  delay(3000);
  noTone(buzzer);
  delay(3000);
  }
}

  if (request.indexOf("/DHT") > 0)  {
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  if (isnan(h) || isnan(t)) {
    client.println("DHT11 tidak terbaca... !");
    return;
  }
  if (request.indexOf("/DHT") > 0) { 
    String postStr = THINGSPEAK_API_KEY;
    postStr +="&field1=";
    postStr += String(t);
    postStr +="&field2=";
    postStr += String(h);
    postStr += "\r\n\r\n";
    client.println("POST /update HTTP/1.1\n");
    client.println("Host: api.thingspeak.com\n");
    client.println("Connection: close\n");
    client.println("X-THINGSPEAKAPIKEY: "+THINGSPEAK_API_KEY+"\n");
    client.println("Content-Type: application/x-www-form-urlencoded\n");
    client.println("Content-Length: ");
    client.println(postStr.length());
    client.println("\n\n");
    client.println(postStr);

    Serial.println("Temperature: ");
    Serial.println(t);
    Serial.println("Celcius Humidity: ");
    Serial.println(h);
    Serial.println("Send to Thingspeak");
  }
  client.stop();
  Serial.println("Waiting…");
  delay(15000);  //minimal nunggu 15 detik update Thingspeak
}
      
  if (request.indexOf("/BlinkLEDon") > 0)  {
  digitalWrite(LED1, HIGH);
  delay(100);
  digitalWrite(LED1, LOW);
  delay(100);
  digitalWrite(LED2, HIGH);
  delay(105);
  digitalWrite(LED2, LOW);
  delay(105);
  digitalWrite(LED3, HIGH);
  delay(110);
  digitalWrite(LED3, LOW);
  delay(110);
  digitalWrite(LED4, HIGH);
  delay(115);
  digitalWrite(LED4, LOW);
  delay(115);
  }
  if (request.indexOf("/BlinkLEDoff") > 0)  {
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
  digitalWrite(LED4, LOW);
  }
  if (request.indexOf("/buzzeron") > 0)  {
    tone(buzzer, 1000);
    delay(1000);
  }
  if (request.indexOf("/buzzeroff") >0)  {
    noTone(buzzer);
    delay(1000);
  }
  
  if (request.indexOf("/led1on") > 0)  {
    digitalWrite(LED1, HIGH);
  }
  if (request.indexOf("/led1off") >0)  {
    digitalWrite(LED1, LOW);   
  }
   if (request.indexOf("/led2on") > 0)  {
    digitalWrite(LED2, HIGH);   
  }
  if (request.indexOf("/led2off") >0)  {
    digitalWrite(LED2, LOW);   
  }
  
  if (request.indexOf("/led3on") > 0)  {
    digitalWrite(LED3, HIGH);
   
  }
  if (request.indexOf("/led3off") >0)  {
    digitalWrite(LED3, LOW);   
  }
   if (request.indexOf("/led4on") > 0)  {
    digitalWrite(LED4, HIGH);   
  }
  if (request.indexOf("/led4off") >0)  {
    digitalWrite(LED4, LOW);   
  }
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); 
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name='apple-mobile-web-app-capable' content='yes' />");
  client.println("<meta name='apple-mobile-web-app-status-bar-style' content='black-translucent' />");
  client.println("</head>");
  client.println("<body>");
  client.println("<style> body{background: linear-gradient(to right, #457fca, #5691c8);</style>");
  client.println("<hr/><hr>");
  client.println("<h4><center> IoT Starter Kit : Kontrol All Device  </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 1");
  client.println("<a href=\"/led1on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led1off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 2");
  client.println("<a href=\"/led2on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led2off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 3");
  client.println("<a href=\"/led3on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led3off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED 4");
  client.println("<a href=\"/led4on\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/led4off\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("LED BLINK");
  client.println("<a href=\"/BlinkLEDon\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/BlinkLEDoff\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");  
  client.println("Buzzer");
  client.println("<a href=\"/buzzeron\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/buzzeroff\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("DHT");
  client.println("<a href=\"/DHT\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/\"\"><button>Turn Off </button></a><br />");   
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("PIR");
  client.println("<a href=\"/PIR\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/\"\"><button>Turn Off </button></a><br />");   
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("MQ2");
  client.println("<a href=\"/MQ2\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/\"\"><button>Turn Off </button></a><br />");   
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("Mario Song");
  client.println("<a href=\"/marioON\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/marioOFF\"\"><button>Turn Off </button></a><br />");   
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("<table border=\"5\">");
  client.println("<tr>");
  //=====================
  if (digitalRead(LED1))
         { 
           client.print("<td>LED 1 = ON</td>");        
         }
  else
          {
            client.print("<td>LED 1 = OFF</td>");
          }     
  client.println("<br/>");
  //======================           
  if (digitalRead(LED2))
          { 
           client.print("<td>LED 2 = ON</td>");
          }
  else
          {
            client.print("<td>LED 2 = OFF</td>");
          }
  client.println("</br>");
  //=======================
  if (digitalRead(LED3))
         { 
           client.print("<td>LED 3 = ON</td>");        
         }
  else
          {
            client.print("<td>LED 3 = OFF</td>");
          }     
  client.println("<br />");
  //======================
  if (digitalRead(LED4))
         { 
           client.print("<td>LED 4 = ON</td>");        
         }
  else
          {
            client.print("<td>LED 4 = OFF</td>");
          }     
  client.println("<br/>");
  //======================
  if (digitalRead(buzzer))
         { 
           client.print("<td>buzzer = ON</td>");        
         }
  else
          {
            client.print("<td>buzzer = OFF</td>");
          }     
  client.println("<br/>");
  //======================
  if (digitalRead(pirMotion))
         { 
           client.print("<td>PIR = ON</td>");        
         }
  else
          {
            client.print("<td>PIR = OFF</td>");
          }     
  client.println("<br/>");
  //======================
  if (digitalRead(MQ2))
         { 
           client.print("<td>MQ2 = ON</td>");        
         }
  else
          {
            client.print("<td>MQ2 = OFF</td>");
          }     
  client.println("<br/>");
  //======================
   if (digitalRead(DHTPIN))
         { 
           client.print("<td>DHT = ON</td>");        
         }
  else
          {
            client.print("<td>DHT = OFF</td>");
          }     
  client.println("<tr/>");
  //======================
  client.println("<tr>"); 
  client.println("</table>");
  client.println("</center>");
  client.println("</html>"); 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println(""); 
}
