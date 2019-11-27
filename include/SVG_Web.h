/*************************************************** 
  A little descrition:

  Written by Alexandr Gorbunov.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef SVG_WEB_H
#define SVG_WEB_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"
#include <Adafruit_BMP085.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

class Web_Graph
{
public:
    float Calculate_Altitude();
    void Polyline();
    void handleRoot();
    void handleNotFound();

    float Hight;
};

#endif //  SVG_WEB_H
