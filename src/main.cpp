/*
 * ESP8266 SPIFFS Basic Reading and Writing File 
 *
 */
 
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <FS.h>   //Include File System Headers
#include "Calculate_Alt.h"
#include "Wire.h"
#include "Ticker.h"

// вписываем здесь SSID и пароль для вашей WiFi-сети:
const char* ssid = "bb-alex";
const char* password = "AuroraSky1819";
char State = 0;

int z = 251;
int ledPin = 2;
int Quantity_of_Pressing = 0;
char ledState = 0;
int y = 0;



Adafruit_BMP085 t;


void setup() 
{
  delay(1000);
  Serial.begin(115200);
  


}

void loop()
{
  while (WiFi.status() != WL_CONNECTED)
  {
   
  }


}


void WiFi_Start()
{  
  Serial.println();   // подключаемся к WiFi-сети:
  Serial.print("Connecting to "); // "Подключаемся к "
  Serial.println(ssid);
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
  Wire.begin(4, 5);
  // if (!t.begin()) {
	// Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	// while (1) {}
  // }
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