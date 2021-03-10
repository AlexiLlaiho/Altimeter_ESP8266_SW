/*************************************************** 
  A little descrition:

  Written by Alexandr Gorbunov.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef SVG_WEB_H
#define SVG_WEB_H

#if (ARDUINO >= 100)
 #include <Arduino.h>
#else
 #include <WProgram.h>
#endif

#include "system_status.h"
#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include "Calculate_Alt.h"
// #include "ESPAsyncWebServer.h"

class Web_Graph
{
public:    
    
    void main_web_cycle();
    void WiFi_Start();    

    float Hight;    
    const char *ssid = "rrocketsnet";
    const char *password = "rrockets2021";
    float fData_Mass[3] = {2.34, 2.89, 5.62};    
    
};

void handleNotFound();
void handleRoot();
void SVG_Graph();
void static_ip_setup();
void HTTP_Start();
void fTurnOFF();
void fEspRestart();
#endif //  SVG_WEB_H





