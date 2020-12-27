#include <ESP8266WiFi.h> 
const char* ssid = "";
const char* password = "";

#define Relay1 D1
#define Relay2 D2 
#define Relay3 D5 
#define Relay4 D6 

WiFiServer server(80);
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

  if (request.indexOf("/Relay1off") > 0)  {
    digitalWrite(Relay1, HIGH);
   
  }
  if (request.indexOf("/Relay1on") >0)  {
    digitalWrite(Relay1, LOW);   
  }
   if (request.indexOf("/Relay2off") > 0)  {
    digitalWrite(Relay2, HIGH);   
  }
  if (request.indexOf("/Relay2on") >0)  {
    digitalWrite(Relay2, LOW);   
  }
  
  if (request.indexOf("/Relay1off") > 0)  {
    digitalWrite(Relay3, HIGH);
   
  }
  if (request.indexOf("/Relay1on") >0)  {
    digitalWrite(Relay3, LOW);   
  }
   if (request.indexOf("/Relay2off") > 0)  {
    digitalWrite(Relay4, HIGH);   
  }
  if (request.indexOf("/Relay2on") >0)  {
    digitalWrite(Relay4, LOW);   
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
  client.println("<body bgcolor = \"#f7e6ec\">"); 
  client.println("<hr/><hr>");
  client.println("<h4><center> IoT Starter Kit : Kontrol 4 Relay  </center></h4>");
  client.println("<hr/><hr>");
  client.println("<br><br>");
  client.println("<br><br>");
  client.println("<center>");
  client.println("Relay 1");
  client.println("<a href=\"/Relay1off\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Relay1on\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("Relay 2");
  client.println("<a href=\"/Relay2off\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Relay2on\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>");
  client.println("Relay 3");
  client.println("<a href=\"/Relay3off\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Relay3on\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>");   
  client.println("<br><br>");
  client.println("<center>");
  client.println("Relay 4");
  client.println("<a href=\"/Relay4off\"\"><button>Turn On </button></a>");
  client.println("<a href=\"/Relay4on\"\"><button>Turn Off </button></a><br />");  
  client.println("</center>"); 
  client.println("<br><br>");
  client.println("<center>"); 
  client.println("<table border=\"5\">");
  client.println("<tr>");
  //=====================
  if (digitalRead(Relay1))
         { 
           client.print("<td>Relay 1 = ON</td>");        
         }
  else
          {
            client.print("<td>Relay 1 = OFF</td>");
          }     
  client.println("<br/>");
  //======================           
  if (digitalRead(Relay2))
          { 
           client.print("<td>Relay 2 = ON</td>");
          }
  else
          {
            client.print("<td>Relay 2 = OFF</td>");
          }
  client.println("</br>");
  //=======================
  if (digitalRead(Relay3))
         { 
           client.print("<td>Relay 3 = ON</td>");        
         }
  else
          {
            client.print("<td>Relay 3 = OFF</td>");
          }     
  client.println("<br />");
  //======================
  if (digitalRead(Relay4))
         { 
           client.print("<td>Relay 4 = ON</td>");        
         }
  else
          {
            client.print("<td>Relay 4 = OFF</td>");
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
