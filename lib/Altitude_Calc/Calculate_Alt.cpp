#include "Calculate_Alt.h"

#ifdef bSensor
Adafruit_BMP085 bmp;
#endif
MS5611 smp;
extern uint16 Flight_Time[10000];
uint16_t i = 0;


float Altitude::Calculate_Altitude()
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
Hight = smp.getAltitude(mPressure);
#ifdef vDEBUG
  Serial.print("mPressure is: ");
  Serial.print(mPressure);
  Serial.print(" Pa; ");
  Serial.print(" Temp is: ");
  Serial.print(Temp);
  Serial.print(";");
  Serial.print(" Hight is: ");
  Serial.print(Hight); 
  Serial.print("; ");
  Serial.print(" Pressure_in_Start point is: ");
  Serial.print(rP); 
  Serial.print("; ");
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
  return rP;
}

void smooth(double *input, double *output, int n, int window)
{
  int i, j, z, k1, k2, hw;
  double tmp;
  if (fmod(window, 2) == 0)
  {
    window++;
  }
  hw = (window - 1) / 2;
  output[0] = input[0];

  for (i = 1; i < n; i++)
  {
    tmp = 0;
    if (i < hw)
    {
      k1 = 0;
      k2 = 2 * i;
      z = k2 + 1;
    }
    else if ((i + hw) > (n - 1))
    {
      k1 = i - n + i + 1;
      k2 = n - 1;
      z = k2 - k1 + 1;
    }
    else
    {
      k1 = i - hw;
      k2 = i + hw;
      z = window;
    }

    for (j = k1; j <= k2; j++)
    {
      tmp = tmp + input[j];
    }
    output[i] = tmp / z;
  }
}