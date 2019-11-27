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
const char* filename = "/samplefile.txt";
int z = 251;
int ledPin = 2;
int Quantity_of_Pressing = 0;
char ledState = 0;
int y = 0;


Altitude A_p;
Adafruit_BMP085 t;
WiFiServer server(80);

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

void SVG_Graph_Run()
{
  Serial.println("WiFi connected");                                // "Подключение к WiFi выполнено"
  server.begin();                                                  // запускаем веб-сервер:
  Serial.println("Web server running. Waiting for the ESP IP..."); // "Веб-сервер запущен. Ожидание IP-адреса ESP..."
  delay(10000);
  Serial.println(WiFi.status());
  Serial.println(WiFi.localIP()); // печатаем IP-адрес ESP:

  //  else if (Quantity_of_Pressing == 2)
  //  {
  //    Serial.println("Mode_2");
  //    timer1_write(900000);
  //    File f = SPIFFS.open(filename, "r"); //Read File data
  //    if (!f)
  //    {
  //      Serial.println("file open failed");
  //    }
  //    else
  //    {
  //      for (int i = 0; i < f.size(); i++) //Read upto complete file size
  //      {
  //        Serial.print((char)f.read());
  //      }
  //      f.close(); //Close file
  //      Serial.println("File Closed");
  //      Quantity_of_Pressing = 0;
  //    }
  //  }

  //  else if (Quantity_of_Pressing == 3)
  //  {
  // начинаем прослушку входящих клиентов:
  WiFiClient client = server.available();

  if (client)
  {
    Serial.println("New client"); //  "Новый клиент"
    // создаем переменную типа «boolean»,
    // чтобы определить конец HTTP-запроса:
    boolean blank_line = true;
    while (client.connected())
    {
      if (client.available())
      {
        char c = client.read();

        if (c == '\n' && blank_line)
        {
          //  getTemperature();
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");
          client.println();
          // веб-страница с данными о температуре:
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");
          client.println("<head></head><body><h1>Altimeter - Hight</h1><h3>Hight in Meters: ");
          client.println(A_p.Calculate_Altitude());
          break;
        }
        if (c == '\n')
        {
          // если обнаружен переход на новую строку:
          blank_line = true;
        }
        else if (c != '\r')
        {
          // если в текущей строчке найден символ:
          blank_line = false;
        }
      }
    }    
    delay(1);
    client.stop();
    Serial.println("Client disconnected.");    
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