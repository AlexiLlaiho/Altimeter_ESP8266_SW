/*
 * ESP8266 ALTIMETER for aircraft models 
 *
 */
 
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <FS.h>   //Include File System Headers
#include "Calculate_Alt.h"
#include "Wire.h"
#include "Ticker.h"
#include "SVG_Web.h"
#include "Sp_File_Sys.h"
#include "Calculate_Alt.h"

#define ledPin 2
#define vDEBUG

Altitude fD;
Web_Graph wG;
const char* ssid = "bb-alex";
const char* password = "AuroraSky1819";
char ledState = 0;

void WiFi_Start(void);
void BMP_check_and_start(void);
void GPIO_TIM_setup(void);

void setup()
{
  delay(1000);
  Serial.begin(115200);
  BMP_check_and_start();
  Initialize_File_System();
  GPIO_TIM_setup();
  WiFi_Start();
}

void loop()
{  
  while (WiFi.status() != WL_CONNECTED)
  {
    fD.Write_Data_to_Massive();
  }
  Open_and_Write_File();
  wG.main_web_cycle();
}


void WiFi_Start()
{ 
  #ifdef vDEBUG
  Serial.println();   // подключаемся к WiFi-сети:
  Serial.print("Connecting to "); // "Подключаемся к "
  Serial.println(ssid);
  #endif 
  WiFi.begin(ssid, password);
}

void ICACHE_RAM_ATTR onTimerISR()
{
  if (ledState == 0)
  {
    digitalWrite(ledPin, HIGH);
    ledState = 1;
  }
  else 
  {
    digitalWrite(ledPin, LOW);
    ledState = 0;
  }    
}


void BMP_check_and_start()
{
  Adafruit_BMP085 t;

  Wire.begin(4, 5);
  if (!t.begin())
  {
    Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1)
    {
    }
  }
}

void GPIO_TIM_setup()
{
  pinMode(2, OUTPUT);
  pinMode(12, INPUT);
  // attachInterrupt(digitalPinToInterrupt(12), Run_Interrupt_func, RISING);
  timer1_attachInterrupt(onTimerISR);
  timer1_enable(TIM_DIV256, TIM_EDGE, TIM_LOOP);
  timer1_write(1500);
}