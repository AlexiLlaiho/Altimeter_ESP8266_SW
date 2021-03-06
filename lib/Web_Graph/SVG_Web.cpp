#include "SVG_Web.h"

extern double dPS;
extern uint16_t Flight_Time[232];
extern float HL;
extern Altitude fD;

uint16 Quantity_of_elements;
uint8_t GrPart = 0; //Вывод нужной части графика

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
  mdns.update();
  server.handleClient();  
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


void SVG_Graph()
{
  String out = "";  
  uint16_t *p_xM;
  uint16_t *p_yM;
  p_xM = Flight_Time;
  p_yM = fD.Flight_Data_Massive;
  char temp[200]; 
  uint16_t i;
  uint16_t a;   
  switch(GrPart)
    {
      case 0: a = 0;  ++GrPart; break;
      case 1: a = 240; ++GrPart; break;
      case 2: a = 480; ++GrPart; break;
      case 3: a = 700;  ++GrPart; break;
      case 4: a = 940; ++GrPart; break; 
      case 5: a = 1180;  ++GrPart; break;  
      case 6: a = 1420;  ++GrPart; break;
      case 7: a = 1660;  ++GrPart; break;
      case 8: a = 1900;  ++GrPart; break;
      case 9: a = 2140; ++GrPart; break;
      case 10: a = 2380; ++GrPart; break;
      case 11: a = 2620; ++GrPart; break;
      case 12: a = 2860; ++GrPart; break;
      case 13: a = 3100; ++GrPart; break;
      case 14: a = 3340; ++GrPart; break;
    }
out += "<html lang=\"en\">\n";
  out += "<head> <meta charset=\"UTF-8\"> <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"> \n";
  out += "<style> body {color: black;  margin: 2% auto;} @media screen and (max-width: 1085px) {body{width: 18%; }} @media screen and (max-width: 642px) {body{width: 45%; }}\n";
    out += ".button {border:none; color:white; border-radius:4px; padding:6px 20px; text-align:center; font-size:11px; margin:20px 60px;}\n";
    out += ".button1 {background-color: #ff0000;}\n";  
  out += " </style> </head>\n";  
    out += "<body> \n";    
    out += " <svg xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 980 2750\" preserveAspectRatio=\"xMidYMid meet\">\n";
    out += " <g>\n";
      out += " <title>background</title>\n";
        out += " <rect fill=\"#fff\" id=\"canvas_background\" height=\"2752\" width=\"982\" y=\"-1\" x=\"-1\"/>\n";
          out += " <g display=\"none\" overflow=\"visible\" y=\"0\" x=\"0\" height=\"100%\" width=\"100%\" id=\"canvasGrid\">\n";
            out += " <rect fill=\"url(#gridpattern)\" stroke-width=\"0\" y=\"0\" x=\"0\" height=\"100%\" width=\"100%\"/>\n";
        out += " </g>\n";
    out += " </g>\n";
    out += " <g>\n";
        out += " <title>Layer 1</title>\n";
        out += " <line stroke-linecap=\"undefined\" stroke-linejoin=\"undefined\" id=\"svg_1\" y2=\"2630\" x2=\"80\" y1=\"30\" x1=\"80\" stroke-width=\"1\" stroke=\"#000\" fill=\"none\"/>\n";
        out += " <line stroke-linecap=\"undefined\" stroke-linejoin=\"undefined\" id=\"svg_2\" y2=\"2630\" x2=\"950\" y1=\"2630\" x1=\"60\" stroke-width=\"1\" stroke=\"#000\" fill=\"none\"/>\n";
        out += " <text font-size=\"36\" y=\"2630\" x=\"5\" stroke-width=\"2\">0</text>\n";
        out += " <text font-size=\"36\" y=\"2530\" x=\"5\" stroke-width=\"2\">10</text>\n";
        out += " <line stroke-dasharray=\"2,2\" y2=\"2530\" x2=\"950\" y1=\"2530\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += " <text font-size=\"36\" y=\"2330\" x=\"5\"  stroke-width=\"3\">30</text>\n";
        out += " <line stroke-dasharray=\"2,2\" y2=\"2330\" x2=\"950\" y1=\"2330\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += " <text font-size=\"36\" y=\"2130\" x=\"15\"  stroke-width=\"3\">50</text>\n";
        out += " <line stroke-dasharray=\"2,2\" y2=\"2130\" x2=\"950\" y1=\"2130\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += " <text font-size=\"36\" y=\"1930\" x=\"15\" stroke-width=\"3\">70</text>\n";
        out += " <line stroke-dasharray=\"2,2\" y2=\"1930\" x2=\"950\" y1=\"1930\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += " <text font-size=\"36\" y=\"1730\" x=\"15\"  stroke-width=\"3\">90</text>\n";
        out += " <line stroke-dasharray=\"2,2\" y2=\"1730\" x2=\"950\" y1=\"1730\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += " <text font-size=\"36\" y=\"1530\" x=\"5\"  stroke-width=\"3\">110</text>\n";
        out += " <line stroke-dasharray=\"2,2\" y2=\"1530\" x2=\"950\" y1=\"1530\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += "<text font-size=\"36\" y=\"1330\" x=\"5\" stroke-width=\"3\">130</text>\n";
        out += "<line stroke-dasharray=\"2,2\" y2=\"1330\" x2=\"950\" y1=\"1330\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += "<text font-size=\"36\" y=\"1130\" x=\"5\" stroke-width=\"3\">150</text>\n";
        out += "<line stroke-dasharray=\"2,2\" y2=\"1130\" x2=\"950\" y1=\"1130\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += "<text font-size=\"36\" y=\"930\" x=\"5\" stroke-width=\"3\">170</text>\n";
        out += "<line stroke-dasharray=\"2,2\" y2=\"930\" x2=\"950\" y1=\"930\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += "<text font-size=\"36\" y=\"730\" x=\"5\" stroke-width=\"3\">190</text>\n";
        out += "<line stroke-dasharray=\"2,2\" y2=\"730\" x2=\"950\" y1=\"730\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += "<text font-size=\"36\" y=\"530\" x=\"5\" stroke-width=\"3\">210</text>\n";
        out += "<line stroke-dasharray=\"2,2\" y2=\"530\" x2=\"950\" y1=\"530\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += "<text font-size=\"36\" y=\"330\" x=\"5\" stroke-width=\"3\">230</text>\n";
        out += "<line stroke-dasharray=\"2,2\" y2=\"330\" x2=\"950\" y1=\"330\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";
        out += "<text font-size=\"36\" y=\"130\" x=\"5\" stroke-width=\"3\">250</text>\n";
        out += "<line stroke-dasharray=\"2,2\" y2=\"130\" x2=\"950\" y1=\"130\" x1=\"80\" stroke-width=\"2\" stroke=\"#000\" fill=\"none\"/>\n";

        out += " <text font-size=\"36\" id=\"svg_59\" y=\"2690\" x=\"30\">\n ";
          sprintf(temp, "Давление в точке старта (Па): %d", int(dPS));
          out += temp;
        out += " </text>\n";
        out += " <text font-size=\"36\" id=\"svg_61\" y=\"2730\" x=\"30\">\n ";
          sprintf(temp, "Максимальная высота (м): %f", HL);
          out += temp;
        out += " </text>\n";
        out += " <text font-size=\"36\" id=\"svg_62\" y=\"2730\" x=\"712\">\n ";
          sprintf(temp, "Страница: %d", GrPart);
          out += temp;
        out += " </text>\n";
    out += " </g>\n ";    
    out += "<g stroke=\"black\">\n";
    String outT = "";
    for (i = 0; i < 229; i++) //we decrease a number of polyline points for improve graphics
    {
      sprintf(temp, "<polyline points=\"%u,%u  %u,%u \" stroke-width=\"2.1\" />\n",
              80 + *(p_xM + i),
              2630 - *(p_yM + (i + a)),
              80 + *(p_xM + (i + 1)),
              2630 - *(p_yM + (i + a + 1)));
      out += temp;
      if (i == 228)
      {
        outT += temp;
        Serial.println(outT);
      }
    }
    if (GrPart == 15) GrPart = 0;
    out += "</g>\n";
    out += "</svg>\n";
    out += "<a href=\"/TurnOFF\"> <button class=\"button button1\">OFF</button> </a>\n ";
  out += "</body> \n";
  out += "</html>\n";
  server.send(200, "html", out); //image/svg+xml
}

void fTurnOFF()
{  
  digitalWrite(12, LOW); //switch off power supply
}

void fEspRestart()
{
  ESP.restart();
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
  server.on("/", SVG_Graph);
  server.on("/TurnOFF", fTurnOFF);
  // server.on("/NewFlight", fEspRestart);
  server.on("/inline", []() { server.send(200, "text/plain", "this works as well"); });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}