/*************************************************** 
  A little descrition:

  Written by Alexandr Gorbunov.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#include "Sp_File_Sys.h"

const char *filename = "/samplefile.txt";

Altitude A_p;

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
      Altitude dA;
      Serial.print("Saving data in process: ");
      for (uint16 j = 0; j < 10000; j++)
      {
        f.println( dA.Flight_Data_Massive[j] );
      }
      f.close();
    }
}