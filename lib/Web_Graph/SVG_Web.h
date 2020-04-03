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

class Web_Graph
{
public:    
    
    void Check_Connection();
    void Num_of_Elements();
    void main_web_cycle();
    void WiFi_Start();

    float Hight;
    const char *ssid = "dlink";
    const char *password = "AuroraSky1819";
    float fData_Mass[3] = {2.34, 2.89, 5.62};
};

void handleNotFound();
void handleRoot();
void Polyline();
void SVG_Graph();
void HTTP_Start();

#endif //  SVG_WEB_H





