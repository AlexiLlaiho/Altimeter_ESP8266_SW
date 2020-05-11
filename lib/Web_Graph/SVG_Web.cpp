#include "SVG_Web.h"

extern double dPS;
extern uint16_t Flight_Time[232];
uint16 Data_Mass[750];
uint16 Quantity_of_elements;
uint8_t GrPart = 0; //Вывод нужной части графика
extern Altitude fD;

MDNSResponder mdns;
ESP8266WebServer server(80);
Web_Graph meOWN_func;
extern float HL;

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
  mdns.update();
  server.handleClient();  
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
    <meta http-equiv='refresh' content='10'/>\
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
      // delay(350);
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
  char temp[200]; 
  uint16_t i, a;
  Web_Graph dA;
  switch(GrPart)
    {
      case 0: a = 0;  ++GrPart; break;
      case 1: a = 240; ++GrPart; break;
      case 2: a = 480; ++GrPart; break;
      case 3: a = 700;  ++GrPart; break;
      case 4: a = 940; ++GrPart; break; 
      // case 5: a = 600;  ++GrPart; break;   
    }
  out += " <svg width=\"1000\" height=\"1440\" xmlns=\"http://www.w3.org/2000/svg\">\n"; 
  out += " <g>\n";
    out += " <title>background</title>\n";
    out += " <rect fill=\"#fff\" id=\"canvas_background\" height=\"1442\" width=\"1002\" y=\"-1\" x=\"-1\"/>\n";
      out += " <g display=\"none\" overflow=\"visible\" y=\"0\" x=\"0\" height=\"100%\" width=\"100%\" id=\"canvasGrid\">\n";
      out += " <rect fill=\"url(#gridpattern)\" stroke-width=\"0\" y=\"0\" x=\"0\" height=\"100%\" width=\"100%\"/>\n";
    out += " </g>\n";
  out += " </g>\n";
  out += " <g>\n";
    out += " <title>Layer 1</title>\n";
    out += " <line stroke-linecap=\"null\" stroke-linejoin=\"null\" id=\"svg_38\" y2=\"1280\" x2=\"60\" y1=\"30\" x1=\"60\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1.8\" stroke=\"#000\" fill=\"none\"/>\n";
    out += " <line stroke-linecap=\"null\" stroke-linejoin=\"null\" id=\"svg_39\" y2=\"1280\" x2=\"980\" y1=\"1280\" x1=\"60\" fill-opacity=\"null\" stroke-opacity=\"null\" stroke-width=\"1.8\" stroke=\"#000\" fill=\"none\"/>\n";
    out += " <text font-size=\"36\" id=\"svg_33\" y=\"1200\" x=\"10\">0</text>\n";
    out += " <text font-size=\"36\" id=\"svg_34\" y=\"1100\" x=\"10\">10</text>\n";
    out += " <text font-size=\"36\" id=\"svg_35\" y=\"1000\" x=\"10\">20</text>\n";
    out += " <text font-size=\"36\" id=\"svg_41\" y=\"900\" x=\"10\" >30</text>\n";
    out += " <text font-size=\"36\" id=\"svg_51\" y=\"800\" x=\"10\" >40</text>\n";
    out += " <text font-size=\"36\" id=\"svg_52\" y=\"700\" x=\"10\" >50</text>\n";
    out += " <text font-size=\"36\" id=\"svg_53\" y=\"600\" x=\"10\" >60</text>\n";
    out += " <text font-size=\"36\" id=\"svg_54\" y=\"500\" x=\"10\" >70</text>\n";
    out += " <text font-size=\"36\" id=\"svg_55\" y=\"400\" x=\"10\" >80</text>\n";
    out += " <text font-size=\"36\" id=\"svg_56\" y=\"300\" x=\"10\" >90</text>\n";
    out += " <text font-size=\"36\" id=\"svg_57\" y=\"200\" x=\"1\" >100</text>\n";
    out += " <text font-size=\"36\" id=\"svg_58\" y=\"100\" x=\"1\" >110</text>\n"; 
      out += " <text font-size=\"36\" id=\"svg_59\" y=\"1387\" x=\"30\">\n ";
          sprintf(temp, "Давление в точке старта (Па): %d", int(dPS) );  
          out += temp;
      out += " </text>\n";    
      out += " <text font-size=\"36\" id=\"svg_61\" y=\"1330\" x=\"30\">\n ";
          sprintf(temp, "Максимальная высота (м): %f", HL);
          out += temp;
      out += " </text>\n";     
      out += " <text font-size=\"36\" id=\"svg_62\" y=\"1387\" x=\"712\">\n ";
          sprintf(temp, "Страница: %d", GrPart);  
          out += temp;
      out += " </text>\n";     
     out += " </g>\n ";
  out += "<g stroke=\"black\">\n";
      String outT = "";      
      for (i = 0; i < 229; i++) //we decrease a number of polyline points for improve graphics 
      {              
        sprintf(temp, "<polyline points=\"%u,%u  %u,%u \" stroke-width=\"1.4\" />\n", 60 + *(p_xM + i), 1200 - *(p_yM + (i + a)), 60 + *(p_xM + (i + 1)), 1200 - *(p_yM + (i + a + 1)) );
        out += temp; 
        if (i==228)
        {
          outT += temp;
          Serial.println(outT);
        }                                        
      }      
      if (GrPart == 4) GrPart = 0;          
  out += "</g>\n";

out += "</svg>\n";   
server.send(200, "image/svg+xml", out);
}

void SVG_Polyline()
{ 

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