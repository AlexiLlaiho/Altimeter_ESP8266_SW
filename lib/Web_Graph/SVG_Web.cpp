#include "SVG_Web.h"

extern uint16 Flight_Time[750];
uint16 Data_Mass[750];
uint16 Quantity_of_elements;

MDNSResponder mdns;
ESP8266WebServer server(80);
Web_Graph meOWN_func;

#ifdef PC_resolution
  String out_b = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"1900\" height=\"1000\">\n";
  uint16 hightM = 1000;
  #else
  String out_b = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"900\" height=\"1400\">\n";
  uint16 hightM = 1400;
#endif


void Web_Graph::WiFi_Start()
{
#ifdef vDEBUG
  Serial.println();               // подключаемся к WiFi-сети:
  Serial.print("Connecting to "); // "Подключаемся к "
  Serial.println(ssid);
#endif
  WiFi.begin(ssid, password);
}

void Web_Graph::main_web_cycle() 
{
#ifdef vDEBUG
  Altitude aA;
  for (uint16_t k = 0; k < Quantity_of_data_points; k++)
  {
    Serial.print("X: ");
    Serial.print(k);
    Serial.print(" Y: ");
    Serial.println(aA.Flight_Data_Massive[k]);
  }
#endif
  //mdns.update();
  //server.handleClient();
}

void Polyline()
{ // This routine set up the Polygon SVG string for parsing to w3.org
  Altitude aA;
  String out = "";
  uint16_t *p_xM;
  uint16_t *p_yM;
  p_xM = Flight_Time;
  p_yM = aA.Flight_Data_Massive;
  char temp[120];
  out += out_b;
  out += "<g >\n"; // Start our data string
                   // As we are including some variables into the Polygon code we need to lay it into a temporary buffer ( temp ), be sure that you make it big enough.
                   // polygon =                      the command for polygons (this is different to line plotting)
                   // points=\"200,20,80,396         Plot points x,y to x1,y1 etcetcetc
                   // stroke=\"black\"               Draw outline of Polygon in black
                   // stroke-width=\"10\"            Draw outline with thickness of 10
                   // fill=\"Aqua\"                  Fill the inside with Aqua --- if you omit this the its filled with black by default!
                   //
  for (uint16 i = 0; i < Quantity_of_elements; i++)
  {
    sprintf(temp, "<polyline points =\" %u, %u  %u, %u \" stroke=\"blue\" stroke-width =\"3\" /> \n", *(p_xM + i), *(p_yM + i), *(p_xM + (i + 1)), *(p_yM + (i + 1)));
    out += temp;
    // Debug Serial.println(out);
  }
  out += "</g>\n</svg>\n";                // close the SVG wrapper
  server.send(200, "image/svg+xml", out); /* and send it to http://www.w3.org/2000/svg */

  delay(500); /*If you have a Sizable graphic then allow time for the response from w3.org before polling the site again (else things will break) */
}

void handleRoot()
{
  char temp[400];
  int sec = millis() / 1000;
  int min = sec / 60;
  int hr = min / 60;
  snprintf(temp, 400,
           "<html>\
  <head>\
    <meta http-equiv='refresh' content='1'/>\
    <title>ESP8266 SVG Polyline </title>\
    <style>\
      body { background-color: #cccccc; font-family: Arial, Helvetica, Sans-Serif; Color: #000088; }\
    </style>\
  </head>\
  <body>\
    <h1>   ESP8266 SVG Polyline </h1>\
    <img src=\"/test.svg\" />\
  </body>\
</html>",
           hr, min % 60, sec % 60);
  server.send(200, "text/html", temp);
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";

  for (uint8_t i = 0; i < server.args(); i++)
  {
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  }
  server.send(404, "text/plain", message);
}

void Web_Graph::Check_Connection()
{
  WiFi.begin(ssid, password);
  Serial.println("");
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (mdns.begin("esp8266", WiFi.localIP() ) )
  {
    Serial.println("MDNS responder started");
  }
  server.on("/", handleRoot);
  server.on("/test.svg", Polyline);
  server.on("/inline", []() { server.send(200, "text/plain", "this works as well"); });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void Web_Graph::Num_of_Elements()
{
  Altitude aA;

  Quantity_of_elements = sizeof(aA.Flight_Data_Massive) / sizeof(uint16_t);
  Serial.println(Quantity_of_elements);
  if (Quantity_of_elements != 0)
  {
    uint16_t Past_Flight_Time = 0;
    for(uint16_t i = 0; i < Quantity_of_elements; i++)
    {
      Data_Mass[i] = hightM - ( fData_Mass[i] * 10 );
      Flight_Time[i] = 12 + Past_Flight_Time;
      Past_Flight_Time = Flight_Time[i];
      Serial.print(Data_Mass[i]);
      Serial.print("         ");
      Serial.println(Flight_Time[i]);
      delay(350);
    }
  }
}

void HTTP_Start()
{
  if (mdns.begin("esp8266", WiFi.localIP()))
  {
    Serial.println("MDNS responder started");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  server.on("/", handleRoot);
  server.on("/test.svg", Polyline);
  server.on("/inline", []() { server.send(200, "text/plain", "this works as well"); });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

void SVG_Graph_Run()
{
  // Serial.println("WiFi connected");                                // "Подключение к WiFi выполнено"
  // server.begin();                                                  // запускаем веб-сервер:
  // Serial.println("Web server running. Waiting for the ESP IP..."); // "Веб-сервер запущен. Ожидание IP-адреса ESP..."
  // delay(10000);
  // Serial.println(WiFi.status());
  // Serial.println(WiFi.localIP()); // печатаем IP-адрес ESP:

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
  // WiFiClient client = server.available();

  // if (client)
  // {
  //   Serial.println("New client"); //  "Новый клиент"
  //   // создаем переменную типа «boolean»,
  //   // чтобы определить конец HTTP-запроса:
  //   boolean blank_line = true;
  //   while (client.connected())
  //   {
  //     if (client.available())
  //     {
  //       char c = client.read();

  //       if (c == '\n' && blank_line)
  //       {
  //         //  getTemperature();
  //         client.println("HTTP/1.1 200 OK");
  //         client.println("Content-Type: text/html");
  //         client.println("Connection: close");
  //         client.println();
  //         // веб-страница с данными о температуре:
  //         client.println("<!DOCTYPE HTML>");
  //         client.println("<html>");
  //         client.println("<head></head><body><h1>Altimeter - Hight</h1><h3>Hight in Meters: ");
  //         client.println(A_p.Calculate_Altitude());
  //         break;
  //       }
  //       if (c == '\n')
  //       {
  //         // если обнаружен переход на новую строку:
  //         blank_line = true;
  //       }
  //       else if (c != '\r')
  //       {
  //         // если в текущей строчке найден символ:
  //         blank_line = false;
  //       }
  //     }
  //   }
  //   delay(1);
  //   client.stop();
  //   Serial.println("Client disconnected.");
  // }
}