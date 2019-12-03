/*************************************************** 
  A little descrition:

  Written by Alexandr Gorbunov.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef SPIFFS_FILE_SYSTEM_H
#define SPIFFS_FILE_SYSTEM_H

#if (ARDUINO >= 100)
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <FS.h>   //Include File System Headers
#include "Calculate_Alt.h"

class Work_with_file
{
public:    
    

};

void Initialize_File_System();
void Open_and_Write_File();

#endif //  FILE_SYSTEM_H


