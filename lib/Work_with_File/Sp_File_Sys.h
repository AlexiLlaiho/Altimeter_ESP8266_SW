/*************************************************** 
  A little descrition:

  Written by Alexandr Gorbunov.  
  BSD license, all text above must be included in any redistribution
 ****************************************************/

#ifndef SP_FILE_SYS_H
#define SP_FILE_SYS_H

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


