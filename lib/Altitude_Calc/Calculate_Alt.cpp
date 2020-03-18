#include "Calculate_Alt.h"

Adafruit_BMP085 bmp;
MS5611 smp;
extern uint16 Flight_Time[10000];
uint16_t i = 0;

float Altitude::Calculate_Altitude()
{
#ifdef bSensor
  if (!bmp.begin())
  {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1)
    {
      Serial.println("Waiting a sensor..");
    }
  }
#endif

// Serial.print("Temperature = ");
#ifdef vDEBUG
  Serial.print("Temp is: ");
#ifdef bSensor
  Serial.print(bmp.readTemperature());
#else
  Serial.print(smp.readTemperature());
#endif
  Serial.print(";");
#endif

 //Serial.println(" *C");
#ifdef vDEBUG
  Serial.print("  Pressure = ");
#ifdef bSensor
  Serial.print(bmp.readPressure());
#else
  Serial.print(smp.readPressure());
#endif
  Serial.print(" Pa; ");
#endif

mPressure = smp.readPressure();

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
  Serial.print(" Hight is: ");
#ifdef bSensor
  Serial.print(bmp.readAltitude(102276));
#else
  Serial.print(smp.getAltitude(mPressure, mSeaLevelPressure));
#endif
  Serial.print("; ");
#endif

#ifdef bSensor
  Hight = (bmp.readAltitude(102276));
  #else
  Hight = (smp.getAltitude(mPressure, mSeaLevelPressure));
#endif
  delay(100);
  return Hight;
}

void Altitude::Write_Data_to_Massive()
{
#ifdef vDEBUG
    Serial.print("Massive[i]: ");
    Serial.print(i);
    Serial.print("; ");
#endif

  Flight_Data_Massive[i] =(uint16_t)Calculate_Altitude();
  Flight_Time[i] = i;
  
#ifdef vDEBUG
  Serial.print("current hight is: ");
  Serial.print(Flight_Data_Massive[i]);
  Serial.print(";");
#endif

  if (i < Quantity_of_data_points)
  {
    #ifdef vDEBUG
      Serial.print(" i < 1000: ");
      Serial.print(i);
      Serial.println(";");
    #endif
    ++i;
  }
  else if (i == Quantity_of_data_points)
  {
    i = 0;
  }
}

float Altitude::Pressure_in_Start()
{
  int32_t PrS[250], PrS_old;
  for (uint8_t j = 0; j < 250; j++)
  {
#ifdef bSensor
    PrS[j] = bmp.readPressure();
#else
    PrS[j] = smp.readPressure();
#endif
  }
  for (uint8_t k = 0; k < 80; k++)
  {
    PrS_old = PrS[k + 3];
  }
}