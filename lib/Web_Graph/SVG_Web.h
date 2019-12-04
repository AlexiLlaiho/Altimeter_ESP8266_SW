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
#define PC_resolution 1 //Phone 1

#include <Wire.h>
#include <Adafruit_BMP085.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

class Web_Graph
{
public:    
    
    void Check_Connection();
    void Num_of_Elements();
    void main_web_cycle();
    
    float Hight;
    const char *ssid = "dlink";
    const char *password = "AuroraSky1819";
    float fData_Mass[3] = {2.34, 2.89, 5.62};
};

void handleNotFound();
void handleRoot();
void Polyline();
void SVG_Graph_Run();

uint16 Flight_Time[126];
uint16 Data_Mass[126];
uint16 Quantity_of_elements;

#endif //  SVG_WEB_H





