#include "SVG_Web.h"

#ifdef PC_resolution
  String out_b = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"1900\" height=\"1000\">\n";
  uint16 hightM = 1000;
  #else
  String out_b = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"900\" height=\"1400\">\n";
  uint16 hightM = 1400;
#endif

MDNSResponder mdns;
ESP8266WebServer server(80);
Web_Graph meOWN_func;

void main_web_cycle() 
{
  mdns.update();
  server.handleClient();
}

void Web_Graph::Polyline()
{ // This routine set up the Polygon SVG string for parsing to w3.org
  String out = "";
  uint16 *p_xM;
  uint16 *p_yM;
  p_xM = Data_Mass;
  p_yM = Flight_Time;
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
    sprintf(temp, "<polyline points =\" %u, %u  %u, %u \" stroke=\"blue\" stroke-width =\"3\" /> \n", *(p_xM + i), *(p_yM + i), *(p_xM + (i + 1)), *(p_yM + (i + 1)) );
    out += temp;
    // Debug Serial.println(out);
  }
  out += "</g>\n</svg>\n";                // close the SVG wrapper
  server.send(200, "image/svg+xml", out); /* and send it to http://www.w3.org/2000/svg */

  delay(500);                             /*If you have a Sizable graphic then allow time for the response from w3.org before polling the site again (else things will break) */
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
  server.on("/test.svg", meOWN_func.Polyline());
  server.on("/inline", []() { server.send(200, "text/plain", "this works as well"); });
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");
}

// void Web_Graph::Num_of_Elements()
// {
//   Quantity_of_elements = sizeof(Data_Mass)/sizeof(float);
//   Serial.println(Quantity_of_elements);
//   if (Quantity_of_elements != 0)
//   {
//     uint16 Past_Flight_Time = 0;
//     for(uint16 i = 0; i < Quantity_of_elements; i++)
//     {
//       Data_Mass[i] = hightM - ( fData_Mass[i] * 10 );
//       Flight_Time[i] = 12 + Past_Flight_Time;
//       Past_Flight_Time = Flight_Time[i];
//       Serial.print(Data_Mass[i]);
//       Serial.print("         ");
//       Serial.println(Flight_Time[i]);
//       delay(350);
//     }
//   }
// }