/*
 * ESP8266 SPIFFS Basic Reading and Writing File 
 *
 */
 
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <FS.h>   //Include File System Headers
#include "Calculate_Alt.h"
#include "Wire.h"

#define Button_pin 12

Altitude A_p;
Adafruit_BMP085 t;

const char* filename = "/samplefile.txt";
int z = 251;
int Quantity_of_Pressing = 0;
int val = 0;
int time_0 = 0, time_1 = 0;

void does_Button_pressed(void);

void setup() {
  Serial.begin(115200);
  pinMode(Button_pin, INPUT_PULLUP);
  Wire.begin(4, 5);
  // if (!t.begin()) {
	// Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	// while (1) {}
  // }
 
  // //Initialize File System
  // if( SPIFFS.begin() ) { Serial.println("SPIFFS Initialize....ok"); }
  // else { Serial.println("SPIFFS Initialization...failed"); }
  //  //Format File System
  // if( SPIFFS.format() ) { Serial.println("File System Formated"); }
  // else { Serial.println("File System Formatting Error"); }
  //  //Create New File And Write Data to It
  // //w=Write Open file for writing
  
  // for (z = 0; z < 65; z++)
  // {    
  //   File f = SPIFFS.open(filename, "a");
  //   if (!f)
  //   {
  //     Serial.println("file open failed");
  //   }
  //   else
  //   {      
  //     //Serial.println("Writing Data to File"); //Write data to file
  //     // A_p.Calculate_Altitude();
  //     f.println( A_p.Calculate_Altitude() );
  //     f.close(); //Close file
  //   }
  // }
}

void loop() {
  int i;
  does_Button_pressed();
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
  // Serial.println(" :___");
  // val = digitalRead(Button_pin);
  // Serial.println(" _-> ->_");
  // if (val == HIGH){ Serial.println("The control button was pressed!"); }
  // Serial.println(" __;");
  // delay(100);
}

void does_Button_pressed() {
  Serial.println(".......->");
  if (digitalRead(Button_pin) == HIGH){
    Serial.println("->_1");
    if (time_0 == 0) { Serial.println("->_2"); time_0 = millis(); Serial.print(time_0);}
    else if (time_0 != 0 && time_1 == 0) { 
      Serial.println("->_3");
      time_1 = millis();
      Serial.print("           ");
      Serial.print(time_1);
    }

    if ((time_1 - time_0) >= 500)
    {
      Serial.println("The control button was pressed!");
      Quantity_of_Pressing = Quantity_of_Pressing + 1;
      if (Quantity_of_Pressing == 4)
      {
        Quantity_of_Pressing = 0;
        Serial.println("The control button was pressed by 4 times");
      }
      time_0 = 0;
      time_1 = 0;
    }
  }
   //delay(100);
}