#include "Calculate_Alt.h"

Adafruit_BMP085 bmp;
extern uint16 Flight_Time[10000];
uint16_t i = 0;

float Altitude::Calculate_Altitude()
{
  if (!bmp.begin()) {
  	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  // Serial.print("Temperature = ");
  #ifdef vDEBUG
  Serial.print(bmp.readTemperature());
  #endif
  
//   //Serial.println(" *C");

//   Serial.print("  Pressure = ");
//   Serial.print(bmp.readPressure());
//   //Serial.println(" Pa");

//   // Calculate altitude assuming 'standard' barometric
//   // pressure of 1013.25 millibar = 101325 Pascal
//   Serial.print("  Altitude = ");
  // Serial.print(bmp.readAltitude());
//   //Serial.println(" meters");

//   Serial.print("  Pressure at sealevel (calculated) = ");
//   Serial.print(bmp.readSealevelPressure());
//   //Serial.print(" Pa");

//   // you can get a more precise measurement of altitude
//   // if you know the current sea level pressure which will
//   // vary with weather and such. If it is 1015 millibars
//   // that is equal to 101500 Pascals.
#ifdef vDEBUG
Serial.print("  ");
Serial.print(bmp.readAltitude(102276));
Serial.print("  ");  
#endif

//   Serial.println(" meters");
Hight = (bmp.readAltitude(102276));
//   Serial.println();
  delay(100);

  return Hight;
}

void Altitude::Write_Data_to_Massive()
{  
  Flight_Data_Massive[i] = Calculate_Altitude();
  Flight_Time[i] = i;
  #ifdef vDEBUG
  Serial.println(Flight_Data_Massive[i]);
  #endif
  
  if (i < 10000) 
  {
    #ifdef vDEBUG
    Serial.println(i);
    #endif
    ++i;
  }
  else if (i == 10000)
  {
    i = 0;
  }
}