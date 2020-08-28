/*************************************************** 
  A little descrition:

  Written by Alexandr Gorbunov.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Sp_File_Sys.h"

extern Altitude fD;

const char *filename = "/samplefile.txt";
int8_t dFile_recorded = 0x00;

void Initialize_File_System()
{  
  if(SPIFFS.begin())
  {
    Serial.println("SPIFFS Initialize....ok");
  }
  else
  {
    Serial.println("SPIFFS Initialization...failed");
  }
  
  if(SPIFFS.format())
  {
    Serial.println("File System Formated");
  }
  else
  {
    Serial.println("File System Formatting Error");
  }
}

void Open_and_Write_File()
{
   File f = SPIFFS.open(filename, "a");
    if (!f)
    {
      Serial.println("file open failed");
    }
    else
    {      
      #ifdef vDEBUG
        Serial.println("Saving data in process: ");
      #endif
      for (uint16 j = 0; j < Quantity_of_data_points; j++)
      {
        f.println(fD.Flight_Data_Massive[j]);
      }      
      dFile_recorded = 0x01;
      f.close();
      #ifdef vDEBUG
        Serial.println("Data were saved!");
      #endif
    }
}

void Read_Data()
{
  int xCnt = 0;
  File f = SPIFFS.open("/data.txt", "r");
  if (!f)
  {
    Serial.println("file open failed");
  }
  Serial.println("====== Reading from SPIFFS file =======");
  while (f.available())
  {
    //Lets read line by line from the file
    String line = f.readStringUntil('\n');
    Serial.print(xCnt);
    Serial.print("  ");
    Serial.println(line);
    xCnt++;
  }
  f.close();
}