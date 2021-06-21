/* 
 *  DATA: 30 DE MAIO DE 2021
 *  VERSÃO: 1.7
 *  
 *  AUTOR: VÍTOR EDUARDO BRAGANÇA
 */

#include <ESP8266WiFi.h>   
#include "SinricPro.h"
#include "SinricProSwitch.h"
 
#define WIFI_SSID         "CasaDosHorrores"    
#define WIFI_PASS         "SENHA AQUI"
#define APP_KEY           "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"      // O seu App Key é algo como "de0bxxxx-1x3x-4x3x-ax2x-5dabxxxxxxxx"
#define APP_SECRET        "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3X"   // O seu App Secret é algo como "5f36xxxx-x3x7-4x3x-xexe-e86724a9xxxx-4c4axxxx-3x3x-x5xe-x9x3-333d65xxxxxx"
 
#define Luminaria_ID       "5dc1564130xxxxxxxxxxxxxx"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Luminaria_Pin 16  // O pino fisico onde está ligado
#define TV_ID       "5dc1564130xxxxxxxxxxxxxx"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define TV_Pin 4  // O pino fisico onde está ligado
//#define Ventilador_ID       "Copie e cole aqui"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
//#define Ventilador_Pin 0  // O pino fisico onde está ligado
//
#define Lampada_ID       "5dc1564130xxxxxxxxxxxxxx"    // Algo como "5dc1564130xxxxxxxxxxxxxx"
#define Lampada_Pin 5  // O pino fisico onde está ligado

#define BAUD_RATE         9600                // Se precisar, pode trocar o baud rate
 
 
void setupWiFi();
void setupSinricPro();
bool LuminariaState(const String &deviceId, bool &state);
bool LampadaState(const String &deviceId, bool &state);
bool TVState(const String &deviceId, bool &state);
//bool VentiladorState(const String &deviceId, bool &state);
 
 
// main setup function
void setup() {
  Serial.begin(BAUD_RATE); Serial.printf("\r\n\r\n");
  setupWiFi();
  setupSinricPro(); 
  pinMode(Luminaria_Pin, OUTPUT);
  pinMode(Lampada_Pin, OUTPUT);
  pinMode(TV_Pin, OUTPUT);
//  pinMode(Ventilador_Pin, OUTPUT);
}
 
void loop() {
  teste();
  SinricPro.handle();
 
}
 
 

 
bool LampadaState(const String &deviceId, bool &state) {
  Serial.printf("A lampada foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(Lampada_Pin, state);
  return true; // request handled properly
}
//
bool LuminariaState(const String &deviceId, bool &state) {
  Serial.printf("O Luminaria foi %s\r\n", state?"ligado":"desligado");
  digitalWrite(Luminaria_Pin, state);
  return true; // request handled properly
}
// 
bool TVState(const String &deviceId, bool &state) {
  Serial.printf("A TV de energia foi %s\r\n", state?"ligada":"desligada");
  digitalWrite(TV_Pin, state);
  return true; // request handled properly
}
// 
//bool VentiladorState(const String &deviceId, bool &state) {
//  Serial.printf("O ventilador foi %s\r\n", state?"ligado":"desligado");
//  digitalWrite(Ventilador_Pin, state);
//  return true; // request handled properly
//}
 
// setup das conexões Wifi
void setupWiFi() {
  Serial.printf("\r\n[Wifi]: Conectando...");
  WiFi.begin(WIFI_SSID, WIFI_PASS);
 
  while (WiFi.status() != WL_CONNECTED) {
    Serial.printf(".");
    delay(250);
    digitalWrite(2, HIGH);
  }

  digitalWrite(2, LOW);
 
  Serial.printf("Conectado!\r\n[WiFi]: Endereço de IP e %s\r\n", WiFi.localIP().toString().c_str());
}
 
// setup das funções para o SinricPro
void setupSinricPro() {
  // add devices and callbacks to SinricPro

  SinricProSwitch &mySwitch2 = SinricPro[Lampada_ID];
  mySwitch2.onPowerState(LampadaState);

  SinricProSwitch &mySwitch1 = SinricPro[Luminaria_ID];
  mySwitch1.onPowerState(LuminariaState);
// 
// 
  SinricProSwitch &mySwitch3 = SinricPro[TV_ID];
  mySwitch3.onPowerState(TVState);
// 
//  SinricProSwitch &mySwitch4 = SinricPro[Ventilador_ID];
//  mySwitch4.onPowerState(VentiladorState);

  Serial.printf("Conectando a nuvem SinricPro...");

 
  // setup SinricPro
  SinricPro.onConnected([](){ Serial.printf("Conectado a nuvem SinricPro\r\n"); }); 
  SinricPro.onDisconnected([](){ Serial.printf("Desconectado a nuvem SinricPro\r\n"); });
  SinricPro.begin(APP_KEY, APP_SECRET);
}

void teste() {
  digitalWrite(16, HIGH);
}
