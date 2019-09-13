/*
 * ESP8266 SPIFFS Basic Reading and Writing File 
 *
 */
 
#include <ESP8266WiFi.h>
#include <FS.h>   //Include File System Headers
#include <Wire.h>
#include <Adafruit_BMP085.h>

Adafruit_BMP085 bmp;
const char* filename = "/samplefile.txt";
int z = 251; 
  
void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();

  Wire.pins(4, 5); //sda scl
  Wire.begin(4, 5);
  if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  }
 
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
  for (z = 0; z < 100; z++)
  {
    File f = SPIFFS.open(filename, "a");

    if (!f)
    {
      Serial.println("file open failed");
    }
    else
    {
      //Write data to file
      Serial.println("Writing Data to File");
      // f.print("This is sample data which is written in file");

      f.println(z);
      // delay(100);

      f.close(); //Close file
    }
  }
  //Serial.println("prepare of test-file has complete");
}

void Calculate_Altitude()
{
  Serial.print("Temperature = ");
  Serial.print(bmp.readTemperature());
  //Serial.println(" *C");

  Serial.print("  Pressure = ");
  Serial.print(bmp.readPressure());
  //Serial.println(" Pa");

  // Calculate altitude assuming 'standard' barometric
  // pressure of 1013.25 millibar = 101325 Pascal
  Serial.print("  Altitude = ");
  Serial.print(bmp.readAltitude());
  //Serial.println(" meters");

  Serial.print("  Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  //Serial.print(" Pa");

  // you can get a more precise measurement of altitude
  // if you know the current sea level pressure which will
  // vary with weather and such. If it is 1015 millibars
  // that is equal to 101500 Pascals.
  Serial.print("  Real altitude = ");
  Serial.print(bmp.readAltitude(102276));
  Serial.println(" meters");

  Serial.println();
  delay(500);
}

void loop() {
  int i;
  
  //Read File data
  File f = SPIFFS.open(filename, "r");
  
  if (!f) {
    Serial.println("file open failed");
  }
  else
  {
      Serial.println("Reading Data from File:");
      //Data from file
      for(i=0;i<f.size();i++) //Read upto complete file size
      {
        Serial.print((char)f.read());
      }
      f.close();  //Close file
      Serial.println("File Closed");
  }
  delay(2000);
}