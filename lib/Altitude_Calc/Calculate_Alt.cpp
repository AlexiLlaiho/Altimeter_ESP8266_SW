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
#ifdef vDEBUG
  Serial.print("Temp is: ");
#ifdef bSensor
  Serial.print(bmp.readTemperature());
#else
  Serial.print(smp.readTemperature());
#endif
  Serial.print(";");
#endif

#ifdef vDEBUG
  Serial.print("  Pressure = ");
#ifdef bSensor
  Serial.print(bmp.readPressure());
#else
  Serial.print(smp.readPressure(true));
#endif
  Serial.print(" Pa; ");
#endif

mPressure = smp.readPressure(true);

#ifdef vDEBUG
  Serial.print(" Hight is: ");
#ifdef bSensor
  Serial.print(bmp.readAltitude(102276));
#else
  Serial.print(smp.getAltitude(mPressure, SPP));
#endif
  Serial.print("; ");
#endif

#ifdef bSensor
  Hight = (bmp.readAltitude(102276));
  #else
  Hight = (smp.getAltitude(mPressure, SPP));
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

void Altitude::Pressure_in_Start()
{  
  MS5611 dmp;
    
  Serial.println("Calling a Pressure_in_Start function");
  rP = dmp.readPressure(true);
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