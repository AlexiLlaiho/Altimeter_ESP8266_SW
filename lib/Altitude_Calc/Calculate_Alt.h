/*************************************************** 
  This is a library for the Adafruit BMP085/BMP180 Barometric Pressure + Temp sensor

  Designed specifically to work with the Adafruit BMP085 or BMP180 Breakout 
  ----> http://www.adafruit.com/products/391
  ----> http://www.adafruit.com/products/1603

  These displays use I2C to communicate, 2 pins are required to  
  interface
  Adafruit invests time and resources providing this open source code, 
  please support Adafruit and open-source hardware by purchasing 
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef CALCULATE_APP_H
#define CALCULATE_APP_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif
#include "Wire.h"
#include "Adafruit_BMP085.h"

class Altitude
{
public:
    float Calculate_Altitude();
    void Write_Data_to_Massive();

    float Hight;
    uint16_t i = 0;
    uint16_t Flight_Data_Massive[10000];
};

#endif //  ADAFRUIT_BMP085_H