#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ESPAsyncWebServer.h>
#include <UniversalTelegramBot.h>
#include <CTBot.h>

const char* ssid = "Totalplay_2.4Gnormal";
const char* pssw = "x2BV4K2910";

const char* chat_id = "1994205600";
const int chat = 1994205600;
const char* token = "5624223237:AAGZ4pVhsqI-14F_taxVJhhJDLXCIn2B_Y0";

CTBot mybot;

AsyncWebServer server(8080);

#define LED 23
#define SENSOR 19


void encenderAlaramaMovimiento();
void enviarMensaje(char* mensaje);


void encenderAlaramaMovimiento(){
  char* alarmaMovimientoMsj = "Movimiento detectado";
  digitalWrite(LED, HIGH);
  enviarMensaje(alarmaMovimientoMsj);    
}

void enviarMensaje(char* mensaje){
  mybot.sendMessage(chat,mensaje);
}


void setup() {
  Serial.begin(9600);
  pinMode(SENSOR,INPUT);
  pinMode(LED,OUTPUT);
  WiFi.begin(ssid,pssw);
  while(WiFi.status()!= WL_CONNECTED){
    delay(1000);
    Serial.print("Conectando ....");
  }
  Serial.print("Conextion Wifi iniciado");

  mybot.wifiConnect(ssid,pssw);
  mybot.setTelegramToken(token);


  server.on("/apagarMovimiento", HTTP_GET,[](AsyncWebServerRequest *request){
    digitalWrite(LED,LOW);
    mybot.sendMessage(chat, "Alarama apagada");
    request->send(200,"text/plain","alarma apagada");
  });

  server.begin();
  Serial.print("Servidor iniciado en:");
  IPAddress ip = WiFi.localIP();
  Serial.print(ip);
}

void loop() {
  int estado = digitalRead(SENSOR);

  if(estado == HIGH){
    encenderAlaramaMovimiento();
  }
}


