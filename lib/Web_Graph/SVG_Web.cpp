#include "SVG_Web.h"

extern uint16 Flight_Time[750];
uint16 Data_Mass[750];
uint16 Quantity_of_elements;
extern Altitude fD;

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
#ifdef outputDEBUG
  for (uint16_t k = 0; k < Quantity_of_data_points; k++)
  {
    Serial.print("X: ");
    Serial.print(k);
    Serial.print(" Y: ");
    Serial.println(fD.Flight_Data_Massive[k]);
  }
#endif
#ifndef outputDEBUG
  // mdns.update();
  server.handleClient();
#endif
  
}

void Polyline() // This routine set up the Polygon SVG string for parsing to w3.org
{ 
  String out = "";
  uint16_t *p_xM;
  uint16_t *p_yM;
  p_xM = Flight_Time;
  p_yM = fD.Flight_Data_Massive;
  char temp[2000];
  out += out_b;
  out += "<g >\n  <polyline points =\" "; // Start our data string
  #ifdef vDEBUG
    Serial.println("Pointers were created..");
    delay(2000);
  #endif
  for (uint16_t i = 0; i < Quantity_of_data_points; i++) //Quantity_of_data_points
  {
    sprintf(temp, "%u,%u  %u,%u ", *(p_xM + i), *(p_yM + i), *(p_xM + (i + 1)), *(p_yM + (i + 1)));
    out += temp;      
  }
  out += "\" stroke=\"blue\" stroke-width=\"3\" />\n</g>\n</svg>\n"; //close the SVG wrapper
#ifdef vDEBUG
      Serial.println(out);
    #endif
  server.send(200, "image/svg+xml", out); /* and send it to http://www.w3.org/2000/svg */
  delay(10000); /*If you have a Sizable graphic then allow time for the response from w3.org before polling the site again (else things will break) */
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

void SVG_Graph()
{
  String out = "";
  uint16_t *p_xM;
  uint16_t *p_yM;
  p_xM = Flight_Time;
  p_yM = fD.Flight_Data_Massive;
  char temp[2000];  
out += "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"580\" height=\"400\" >\n ";
    out += "<defs>\n";
      out += "<filter height=\"200%\" width=\"200%\" y=\"-50%\" x=\"-50%\" id=\"svg_2_blur\">\n";
        out += " <feGaussianBlur stdDeviation=\"3.5\" in=\"SourceGraphic\"/>\n";
      out += "</filter>\n";
    out += "</defs>\n";
  out += "<g>\n";
    out += " <title>background</title>\n";
    out += "<rect fill=\"#fcf5d9\" id=\"canvas_background\" height=\"402\" width=\"582\" y=\"-1\" x=\"-1\"/> \n";
      out += "<g display=\"none\" overflow=\"visible\" y=\"0\" x=\"0\" height=\"100%\" width=\"100%\" id=\"canvasGrid\">\n";
        out += " <rect fill=\"url(#gridpattern)\" stroke-width=\"0\" y=\"0\" x=\"0\" height=\"100%\" width=\"100%\"/>\n";
      out += "</g>  \n"; 
  out += " </g>   \n"; 
  out += "<g>  \n"; 
    out += " <title>Layer 1</title>\n";
    out += " <rect id=\"svg_1\" height=\"200\" width=\"400\" y=\"70\" x=\"65\" stroke-width=\"1.5\" stroke=\"#000\" fill=\"#BBBBBB\"/> \n";
    out += " <line filter=\"url(#svg_2_blur)\" stroke-linecap=\"null\" stroke-linejoin=\"null\" id=\"svg_2\" y2=\"205.450012\" x2=\"465.5\" y1=\"205.450012\" x1=\"65.5\" stroke-opacity=\"null\" stroke-width=\"1.5\" stroke=\"#000\" fill=\"none\"/>\n";
    out += " <text font-weight=\"bold\" font-style=\"italic\" xml:space=\"preserve\" text-anchor=\"start\" font-family=\"'Trebuchet MS', Gadget, sans-serif\" font-size=\"21\" id=\"svg_3\" y=\"58.450012\" x=\"79.5\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"0\" stroke=\"#000\" fill=\"#000000\">График изменения высоты полета</text>\n";
    out += " <text font-style=\"italic\" xml:space=\"preserve\" text-anchor=\"start\" font-family=\"'Times New Roman', Times, serif\" font-size=\"18\" id=\"svg_4\" y=\"290.450012\" x=\"312.5\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"0\" stroke=\"#000\" fill=\"#000000\">Время полета в сек.</text>\n";
    out += " <text font-weight=\"normal\" font-style=\"italic\" transform=\"rotate(-90, 48.9833, 141.45)\" xml:space=\"preserve\" text-anchor=\"start\" font-family=\"'Times New Roman', Times, serif\" font-size=\"18\" id=\"svg_5\" y=\"147.450012\" x=\"-19.5\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"0\" stroke=\"#000\" fill=\"#000000\">Высота в метрах</text>\n";
    out += " <text xml:space=\"preserve\" text-anchor=\"start\" font-family=\"'Times New Roman', Times, serif\" font-size=\"21\" id=\"svg_6\" y=\"327.450012\" x=\"67.5\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"0\" stroke=\"#000\" fill=\"#000000\"> \n"; 
        sprintf(temp, "Максимальная высота: %d", 125);
        out += temp;
    out += " </text>\n";     
    out += " <text xml:space=\"preserve\" text-anchor=\"start\" font-family=\"'Times New Roman', Times, serif\" font-size=\"21\" id=\"svg_7\" y=\"358.450012\" x=\"68.5\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"0\" stroke=\"#000\" fill=\"#000000\"> \n";
        sprintf(temp, "Атмосферное давление в точке старта: %d", 101123);
        out += temp;       
    out += " </text>\n";    
  out += "</g>\n";
  out += "<g stroke=\"black\">\n";
      for (uint16_t i = 0; i < 2; i++) //Quantity_of_data_points
      {        
        // sprintf(temp, "<polyline points=\"%u,%u  %u,%u \" stroke-width=\"1\" />\n", *(p_xM + i), *(p_yM + i), *(p_xM + (i + 1)), *(p_yM + (i + 1))); 
        sprintf(temp, "<polyline points=\"%u,%u  %u,%u \" stroke-width=\"1\" />\n", 200, 200, 450, 200);       
        out += temp;      
      }      
  out += "</g>\n";
out += "</svg>\n";
  
  server.send(200, "image/svg+xml", out);
}

void HTTP_Start()
{
  if (mdns.begin("esp8266", WiFi.localIP()))
  {
    Serial.println("MDNS responder started");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  Serial.println("MDNS is working");
  server.on("/", handleRoot);
  server.on("/test.svg", SVG_Graph);
  server.on("/inline", []() { server.send(200, "text/plain", "this works as well"); });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}