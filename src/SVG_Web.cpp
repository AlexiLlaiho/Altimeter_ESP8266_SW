#include "SVG_Web.h"

Adafruit_BMP085 bmp;

float Altitude::Calculate_Altitude()
{
  if (!bmp.begin()) 
  {
  	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) 
    {

    }
  }

  return Hight;
}

/******************************************************************************/

const char *ssid = "dlink";
const char *password = "AuroraSky1819";
float fData_Mass[] = {
                        0,2.34000000000000,2.89000000000000,5.62000000000000,7.24000000000000,8.54000000000000,
                        10.5800000000000,12.6000000000000,15.3600000000000,16.9000000000000,17.4500000000000,
                        20.5500000000000,21.6500000000000,23.2000000000000,25.2100000000000,26.7200000000000,
                        28.5300000000000,30.8000000000000,32.5700000000000,34.3500000000000,35.9200000000000,
                        37.1400000000000,39.5000000000000,41.5600000000000,43,44.9500000000000,46.6500000000000,
                        48.1200000000000,50.0900000000000,51.5500000000000,53.8400000000000,55.0100000000000,
                        56.8200000000000,58.6900000000000,59.8300000000000,62.9300000000000,64.3800000000000,
                        65.8400000000000,68.2700000000000,69.1300000000000,71.4000000000000,73.1400000000000,
                        75.1000000000000,76.8800000000000,78.3100000000000,80.3500000000000,82.0900000000000,
                        84.1200000000000,86.0400000000000,87.8300000000000,89.0300000000000,91.0900000000000,
                        92.4900000000000,94.3100000000000,96.4300000000000,98.6700000000000,99.7700000000000,
                        99.6900000000000,99.1000000000000,99.0900000000000,98.0100000000000,97.9300000000000,
                        97.6700000000000,97.4100000000000,97.1300000000000,96.2800000000000,95.3900000000000,
                        95.1900000000000,94.6800000000000,95.2900000000000,95.9700000000000,96.2600000000000,
                        95.8500000000000,96.0500000000000,95.4300000000000,95.1100000000000,94.9800000000000,
                        95.4300000000000,95.1000000000000,94.9700000000000,95.3300000000000,94.8700000000000,
                        94.7200000000000,95.0100000000000,94.1700000000000,94.4900000000000,94.4100000000000,
                        93.9600000000000,93.9700000000000,93.4300000000000,93.3100000000000,93.5600000000000,
                        93.6200000000000,94.0600000000000,92.9600000000000,93.0900000000000,92.8800000000000,
                        92.2000000000000,92.5300000000000,91.9900000000000,92.6600000000000,92.0200000000000,
                        92.1900000000000,91.8700000000000,92,91.6000000000000,91.8000000000000,91.7500000000000,
                        91.9200000000000,91.2200000000000,90.5200000000000,90.7800000000000,91.3100000000000,
                        90.4600000000000,90.9500000000000,90.5700000000000,90.8400000000000,89.6900000000000,
                        90.1000000000000,89.6700000000000,90.7800000000000,90.0300000000000,90.0700000000000,
                        89.2200000000000,89.2700000000000,89.2000000000000,89.4900000000000,88.9500000000000,
                        89.1200000000000,88.1700000000000,88.5500000000000,88.2900000000000,87.9300000000000,
                        88.4400000000000,88.2400000000000,88.0400000000000,87.5100000000000,88.1200000000000,
                        87.7600000000000,87.4400000000000,87.4100000000000,87.2000000000000,86.6300000000000,
                        86.9500000000000,86.6600000000000,86.4900000000000,86.3100000000000,86.3700000000000,
                        85.8100000000000,86.5700000000000,86.3100000000000,86.0300000000000,85.9000000000000,
                        85.5400000000000,85.9600000000000,85.4900000000000,85.1900000000000,85.6900000000000,
                        85.0900000000000,84.8600000000000,84.8200000000000,84.5300000000000,84.3200000000000,
                        85.2900000000000,84.9000000000000,84.3800000000000,83.7800000000000,83.7700000000000,
                        83.8600000000000,84.0200000000000,83.2600000000000,82.8300000000000,82.9700000000000,
                        83.3800000000000,83.2800000000000,83.1700000000000,82.8700000000000,82.8400000000000,
                        82.5200000000000,82.7900000000000,82,82.4200000000000,81.9000000000000,81.9300000000000,
                        82.0700000000000,82.0900000000000,81.3200000000000,81.9100000000000,81.6100000000000,
                        81.2600000000000,81.1000000000000,80.9700000000000,80.8200000000000,80.7900000000000,
                        80.6700000000000,80.7800000000000,80.8700000000000,80.4200000000000,80.1000000000000,
                        80.2200000000000,79.9600000000000,79.4700000000000,79.9400000000000,79.6300000000000,
                        79.4500000000000,79.4400000000000,79.2400000000000,78.7500000000000,78.8600000000000,
                        78.7400000000000,78.5000000000000,79.0400000000000,78.1500000000000,78.1400000000000,
                        77.9400000000000,77.6800000000000,77.8500000000000,77.7000000000000,78.1200000000000,
                        77.4600000000000,77.0900000000000,77.760000000000
                     };
uint16 Data_Mass[126];
uint16 Quantity_of_elements;
uint16 Flight_Time[126];

#define PC_resolution 1 //Phone 1

MDNSResponder mdns;
ESP8266WebServer server(80);
#ifdef PC_resolution
  String out_b = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"1900\" height=\"1000\">\n";
  uint16 hightM = 1000;
  #else
  String out_b = "<svg xmlns=\"http://www.w3.org/2000/svg\" version=\"1.1\" width=\"900\" height=\"1400\">\n";
  uint16 hightM = 1400;
#endif

void setup() {
  Serial.begin(9600);
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

  if (mdns.begin("esp8266", WiFi.localIP()))
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

void main_web_cycle() 
{
  mdns.update();
  server.handleClient();
}

void Polyline()
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

void Num_of_Elements()
{
  Quantity_of_elements = sizeof(Data_Mass)/sizeof(float);
  Serial.println(Quantity_of_elements);
  if (Quantity_of_elements != 0)
  {
    uint16 Past_Flight_Time = 0;
    for(uint16 i = 0; i < Quantity_of_elements; i++)
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
  