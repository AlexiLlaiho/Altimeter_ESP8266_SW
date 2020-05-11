#include "Calculate_Alt.h"

#ifdef bSensor
Adafruit_BMP085 bmp;
#endif
MS5611 smp;
extern uint16_t Flight_Time[232];
extern double dPS;
uint16_t i = 0;
uint16_t yMax = 0;
extern float HL;

uint16_t fMax(uint16_t Value)
{
  if(yMax < Value) yMax = Value;
  return yMax;
}

double Altitude::Calculate_Altitude()
{
  if (!smp.begin(MS5611_ULTRA_HIGH_RES))
  {
    Serial.println("Could not find a valid MS5611 sensor, check wiring!");
    while (1)
    {
      Serial.println("Waiting a sensor..");
    }
  } 
Temp = smp.readTemperature(true);  
mPressure = smp.readPressure(true);
Hight = smp.getAltitude(mPressure, dPS);
  #ifdef vDEBUG
    Serial.print("mPres: ");
    Serial.print(mPressure);
    Serial.print(" Pa; ");
    Serial.print(" Temp: ");
    Serial.print(Temp);
    Serial.print(";");
    Serial.print(" Hight: ");
    Serial.print(Hight*10); 
    Serial.print("; ");
    Serial.print(" PresStP: ");
    Serial.print(dPS); 
    Serial.print("; ");
  #endif  
return Hight*10;
}

bool Altitude::Write_Data_to_Massive()
{  
#ifdef vDEBUG
  Serial.print("Mas[i]: ");
  Serial.print(i);
  Serial.print("; ");
#endif
  double tAV = Calculate_Altitude(); //tAV - temporary Altitude Value
  if (tAV > 0)
  {
    Flight_Data_Massive[i] = (uint16_t)tAV;
  }
  else
  {
    Flight_Data_Massive[i] = 0;
  }
  HL = fMax(Flight_Data_Massive[i]) / 10.0;  
#ifdef vDEBUG
  Serial.print("cur_H: ");
  Serial.print(Flight_Data_Massive[i]);
  Serial.print("; ");
  Serial.print(" HL: ");
  Serial.print(HL);
  Serial.println(";");
#endif
  if (i < Quantity_of_data_points)
  {
    ++i;
    return false;
  }
  else if (i == Quantity_of_data_points)
  {
    i = 0;
    return true;
  }
}

double Altitude::Pressure_in_Start()
{
  #ifdef mSensor
   if (!smp.begin(MS5611_ULTRA_HIGH_RES))
  {   
    while (1)
    {
      Serial.println("Waiting a sensor..");
    }
  } 
  #endif
  Serial.println("Pressure_in_Start: ");
  rP = smp.readPressure(true);
  dPS = rP; 
  return rP;
}

void Altitude::Test_Massive()
{  
  for(uint16_t j = 0; j < 721; j++)
  {
    // INT_Data_Massiv[j] = Test_Data_Massiv[j] * 100; 
    // Serial.println( INT_Data_Massiv[j] );
  }  
}

