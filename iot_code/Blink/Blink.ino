// #include <ESP8266WiFi.h>
// #include <ESP8266WebServer.h>
// #include <ArduinoJson.h>
// #include <DHT.h>

// #define DHTPIN 14   // D5

// // Uncomment whatever type you're using!
// #define DHTTYPE DHT11 // DHT 11

// DHT dht(DHTPIN, DHTTYPE);

// // JsonDocument jsonBuffer;

// /*Put your SSID & Password*/
// const char* ssid = "pi";  // Enter SSID here
// const char* password = "raspberry";  //Enter Password here

// ESP8266WebServer server(80);

// uint8_t LEDpin = 2;
// bool LEDstatus = LOW;

// void setup() {
//   Serial.begin(9600);
//   delay(100);
//   pinMode(LEDpin, OUTPUT);

//   Serial.println("Connecting to ");
//   Serial.println(ssid);

//   //connect to your local wi-fi network
//   WiFi.begin(ssid, password);

//   //check wi-fi is connected to wi-fi network
//   while (WiFi.status() != WL_CONNECTED) {
//   delay(1000);
//   Serial.print(".");
//   }
//   Serial.println("");
//   Serial.println("WiFi connected..!");
//   Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

//   server.on("/", handle_OnConnect);
//   server.on("/ledon", handle_ledon);
//   server.on("/ledoff", handle_ledoff);
//   // server.on("/temp", handle_temp);
//   // server.on("/humidity", handle_humdity);
//   server.onNotFound(handle_NotFound);

//   server.begin();
//   Serial.println("HTTP server started");
// }

// void loop() {
//   server.handleClient();
//   if(LEDstatus)
//   digitalWrite(LEDpin, HIGH);
//   else
//   digitalWrite(LEDpin, LOW);
// }

// // void handle_temp() {
// //   JsonObject root;
// //   root["temperature"] = dht2.readTemperature();
// //   server.send(200, "application/json", );
// // }

// void handle_OnConnect() {
//   LEDstatus = LOW;
//   server.send(200, "text/html", SendHTML(false)); 
// }

// void handle_ledon() {
//   LEDstatus = HIGH;
//   server.send(200, "text/html", SendHTML(true)); 
// }

// void handle_ledoff() {
//   LEDstatus = LOW;
//   server.send(200, "text/html", SendHTML(false)); 
// }

// void handle_NotFound(){
//   server.send(404, "text/plain", "Not found");
// }

// String SendHTML(uint8_t led){
//   String ptr = "<!DOCTYPE html>\n";
//   ptr +="<html>\n";
//   ptr +="<head>\n";
//   ptr +="<title>LED Control</title>\n";
//   ptr +="</head>\n";
//   ptr +="<body>\n";
//   ptr +="<h1>LED</h1>\n";
//   ptr +="<p>Click to switch LED on and off.</p>\n";
//   ptr +="<form method=\"get\">\n";
//   if(led)
//   ptr +="<input type=\"button\" value=\"LED ON\" onclick=\"window.location.href='/ledoff'\">\n";
//   else
//   ptr +="<input type=\"button\" value=\"LED OFF\" onclick=\"window.location.href='/ledon'\">\n";
//   ptr +="</form>\n";
//   ptr +="</body>\n";
//   ptr +="</html>\n";
//   return ptr;
// }



#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include <DHT.h>

#include <Wire.h>

#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F, 16, 2);

#define DHTPIN 14   // D5
#define DHTTYPE DHT11 // DHT 11

DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "pi";  // Enter SSID here
const char* password = "raspberry";  //Enter Password here

ESP8266WebServer server(80);

uint8_t LEDpin = 2;
bool LEDstatus = LOW;

void setup() {
  Serial.begin(9600);
  delay(100);
  pinMode(LEDpin, OUTPUT);
  Wire.begin(2,0);
  lcd.init();   // initializing the LCD
  lcd.backlight(); // Enable or Turn On the backlight 
  lcd.print(" Hello Makers "); // Start Printing

  // Initialize DHT sensor
  dht.begin();

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
  server.on("/temp", handle_temp);
  server.on("/humidity", handle_humidity);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  
  // Control LED based on LEDstatus
  digitalWrite(LEDpin, LEDstatus ? HIGH : LOW);
}

void handle_temp() {
  float temperature = dht.readTemperature();
  if (isnan(temperature)) {
    Serial.println("Failed to read temperature from DHT sensor!");
    server.send(500, "text/plain", "Failed to read temperature from DHT sensor!");
    return;
  }

  Serial.print("Temperature: ");
  Serial.println(temperature);
  
  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  
  String output;
  serializeJson(doc, output);
  server.send(200, "application/json", output);
}

void handle_humidity() {
  float humidity = dht.readHumidity();
  if (isnan(humidity)) {
    Serial.println("Failed to read humidity from DHT sensor!");
    server.send(500, "text/plain", "Failed to read humidity from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.println(humidity);
  
  StaticJsonDocument<200> doc;
  doc["humidity"] = humidity;
  
  String output;
  serializeJson(doc, output);
  server.send(200, "application/json", output);
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
