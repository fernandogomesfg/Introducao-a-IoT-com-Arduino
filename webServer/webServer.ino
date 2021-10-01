#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <FS.h>
#include <Wire.h>

const char* ssid = "Fernando WiFi";
const char* password = "fernando1610";

const int ledPin = 0;

String ledState;
AsyncWebServer server(80);

String processor(const String& var){
  if(var == "resultado"){
    if(digitalRead(ledPin)){
      ledState = "Ligada";
      digitalWrite(LED_BUILTIN, LOW); 
    }
    else{
      ledState = "Deslidaga";
      digitalWrite(LED_BUILTIN, HIGH);
    }
    Serial.print(ledState);
    return ledState;
  }
}
 
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ledPin, OUTPUT);
  if(!SPIFFS.begin()){
    return;
  }
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
  }
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/pagina.html", String(), false, processor);
  });
  
  server.on("/estilo.css", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/estilo.css", "text/css");
  });

  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);    
    request->send(SPIFFS, "/pagina.html", String(), false, processor);
  });
  
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);    
    request->send(SPIFFS, "/pagina.html", String(), false, processor);
  });
  server.begin();
}
void loop(){
}
