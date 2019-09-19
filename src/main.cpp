/*
 * ESP8266 SPIFFS Basic Reading and Writing File 
 *
 */
 
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <FS.h>   //Include File System Headers
#include "Calculate_Alt.h"
#include "Wire.h"


const char* filename = "/samplefile.txt";
int z = 251;
Altitude A_p;
Adafruit_BMP085 t;
int Quantity_of_Pressing = 0;

// void Run_Interrupt_func();
void ICACHE_RAM_ATTR Run_Interrupt_func();
void setup() {
  delay(1000);
  Serial.begin(115200);
  // Serial.println();
  pinMode(12, INPUT);
  attachInterrupt(digitalPinToInterrupt(12), Run_Interrupt_func, RISING);

  Wire.begin(4, 5);
  // if (!t.begin()) {
	// Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	// while (1) {}
  // }
 
  //Initialize File System
  if(SPIFFS.begin())
  {
    Serial.println("SPIFFS Initialize....ok");
  }
  else
  {
    Serial.println("SPIFFS Initialization...failed");
  }
 
  //Format File System
  if(SPIFFS.format())
  {
    Serial.println("File System Formated");
  }
  else
  {
    Serial.println("File System Formatting Error");
  }
 
  //Create New File And Write Data to It
  //w=Write Open file for writing
  
  for (z = 0; z < 65; z++)
  {    
    File f = SPIFFS.open(filename, "a");

    if (!f)
    {
      Serial.println("file open failed");
    }
    else
    {      
      //Serial.println("Writing Data to File"); //Write data to file
      
      // A_p.Calculate_Altitude();

      f.println( A_p.Calculate_Altitude() );
      
      f.close(); //Close file
    }
  }
 
}

void Run_Interrupt_func() {

  Quantity_of_Pressing = Quantity_of_Pressing + 1;
  if (Quantity_of_Pressing == 4) { 
    Quantity_of_Pressing = 0; 
    Serial.println("The control button was pressed by 4 times");
  }
  Serial.println("The control button was pressed!");
}


void loop() {
  int i;
  
  // File f = SPIFFS.open(filename, "r"); //Read File data
  
  // if (!f) {
  //   Serial.println("file open failed");
  // }
  // else
  // {
  //     Serial.println("Reading Data from File:");
  //     for(i = 0; i < f.size(); i++) //Read upto complete file size
  //     {
  //       Serial.print((char)f.read());
  //     }
  //     f.close();  //Close file
  //     Serial.println("File Closed");
  // }
  // delay(5000);
 
}