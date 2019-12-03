/*************************************************** 
  A little descrition:

  Written by Alexandr Gorbunov.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

 #include "Spiffs_File_System.h"

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
      Serial.print("Mode_1:  ");
      f.println(A_p.Calculate_Altitude());
      f.close();
    }
}