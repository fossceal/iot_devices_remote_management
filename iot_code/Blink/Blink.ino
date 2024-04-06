

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "pi";  // Enter SSID here
const char* password = "raspberry";  //Enter Password here

ESP8266WebServer server(80);

uint8_t LEDpin = 2;
bool LEDstatus = LOW;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(LEDpin, OUTPUT);

  // Connect to WiFi
  Serial.println("Connecting to " + String(ssid));
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  
  Serial.println(WiFi.localIP());

  // Setup HTTP server endpoints
  server.on("/", handle_OnConnect);
  server.on("/ledon", handle_ledon);
  server.on("/ledoff", handle_ledoff);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  
  // Control LED based on LEDstatus
  digitalWrite(LEDpin, LEDstatus ? HIGH : LOW);
}

void handle_OnConnect() {
  LEDstatus = LOW;
  server.send(200, "text/html", SendHTML(false)); 
}

void handle_ledon() {
  LEDstatus = HIGH;
  server.send(200, "text/html", SendHTML(true)); 
}

void handle_ledoff() {
  LEDstatus = LOW;
  server.send(200, "text/html", SendHTML(false)); 
}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

String SendHTML(uint8_t led){
  String ptr = "<!DOCTYPE html>\n";
  ptr +="<html>\n";
  ptr +="<head>\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>LED</h1>\n";
  ptr +="<p>Click to switch LED on and off.</p>\n";
  ptr +="<form method=\"get\">\n";
  if(led)
    ptr +="<input type=\"button\" value=\"LED ON\" onclick=\"window.location.href='/ledoff'\">\n";
  else
    ptr +="<input type=\"button\" value=\"LED OFF\" onclick=\"window.location.href='/ledon'\">\n";
  ptr +="</form>\n";
  ptr +="<p><a href=\"/temp\">Get Temperature</a></p>\n";
  ptr +="<p><a href=\"/humidity\">Get Humidity</a></p>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
