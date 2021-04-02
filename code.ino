#include <Arduino.h>
#ifdef ARDUINO_ARCH_SAMD
#include <WiFi101.h>
#elif defined ARDUINO_ARCH_ESP8266
#include <ESP8266WiFi.h>
#elif defined ARDUINO_ARCH_ESP32
#include <WiFi.h>
#else
#endif
#include <WifiLocation.h>
#include <SPI.h>
#include <Wire.h>
#include<BlynkSimpleEsp8266.h>
char auth[]="CU9SX1X0dkbjDMvPSBw7roza9k2uK__R ";


WidgetMap mymap(V1);

int index1=1;


#include <Adafruit_GFX.h>

#include <Adafruit_SSD1306.h>

#define OLED_RESET LED_BUILTIN 

Adafruit_SSD1306 display(OLED_RESET);

#define NUMFLAKES 10

#define XPOS 0

#define YPOS 1

#define DELTAY 2

#define LOGO16_GLCD_HEIGHT 16

#define LOGO16_GLCD_WIDTH 16

const char* googleApiKey = "......................"; 
const char* ssid = "XYZ";
const char* pass = "12346789";
WifiLocation location(googleApiKey); 
static const unsigned char PROGMEM logo16_glcd_bmp[] = { B00000000, B11000000, B00000001, B11000000, B00000001, B11000000, B00000011, B11100000, B11110011, B11100000, B11111110, B11111000, B01111110, B11111111, B00110011, B10011111, B00011111, B11111100, B00001101, B01110000, B00011011, B10100000, B00111111, B11100000, B00111111, B11110000, B01111100, B11110000, B01110000, B01110000, B00000000, B00110000 };

#if (SSD1306_LCDHEIGHT != 64)

#error("Height incorrect, please fix Adafruit_SSD1306.h!");

#endif

void setup() {
Serial.begin(9600);
// Connect to WPA/WPA2 network 
#ifdef ARDUINO_ARCH_ESP32
WiFi.mode(WIFI_MODE_STA); 
#endif
#ifdef ARDUINO_ARCH_ESP8266
WiFi.mode(WIFI_STA);
#endif
 
WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED) 
{ Serial.print("Attempting to connect to WPA SSID: "); 
Serial.println(ssid);
// wait 5 seconds for connection: 
Serial.print("Status = "); 
Serial.println(WiFi.status()); 

delay(500);
}


location_t loc = location.getGeoFromWiFi(); 
Serial.println("Location request data"); 
Serial.println(location.getSurroundingWiFiJson()); 
Serial.println("Latitude: " + String(loc.lat, 7)); 
Serial.println("Longitude: " + String(loc.lon, 7)); 
Serial.println("Accuracy: " + String(loc.accuracy));
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3D (for the 128x64) // init done // Show image buffer on the display hardware.

display.display(); //delay(2000);

display.setTextSize(2);

display.setTextColor(WHITE);

display.setCursor(10, 0);

display.clearDisplay();

display.println("NODEMCU GEOLOCATION ");

// invert the display

display.invertDisplay(true);

display.invertDisplay(false);

display.display();

display.clearDisplay();
Blynk.begin(auth,ssid,pass);
}
void loop() 
{ WiFi.begin(ssid, pass);
while (WiFi.status() != WL_CONNECTED)
{ Serial.print("Attempting to connect to WPA SSID: "); Serial.println(ssid);
// wait 5 seconds for connection: 
Serial.print("Status = "); 
Serial.println(WiFi.status()); 
delay(500);
}
if (WiFi.status()==WL_CONNECTED)
{ Serial.println("Connected.  ");
Serial.print("Status = "); 
Serial.println(WiFi.status()); 
delay(500);
}
Blynk.run();
 
location_t loc = location.getGeoFromWiFi(); 
Serial.println("Location request data"); 
Serial.println(location.getSurroundingWiFiJson()); 
Serial.println("Latitude: " + String(loc.lat, 7)); 
Serial.println("Longitude: " + String(loc.lon, 7)); 
Serial.println("Accuracy: " + String(loc.accuracy));
Serial.println("http://maps.google.com/maps?q="+ String(loc.lat, 7)+"," + String(loc.lon, 7));
Blynk.email("xyz@gmail.com","Your location","http://maps.google.com/maps?q="+ String(loc.lat, 7)+"," + String(loc.lon, 7));
mymap.location(index1,loc.lat,loc.lon,"value");
//Blynk.notify("Latitude:"+String(loc.lat),"Longitude:"+String(loc.lon),"Accuracy:"+String(loc.accuracy));
display.setTextSize(1);

display.setTextColor(WHITE);

display.setCursor(10, 0);

display.clearDisplay();

display.println("input:");

printText("Latitude: " + String(loc.lat, 7)+"Longitude: " + String(loc.lon, 7)+ "Accuracy:" +String(loc.accuracy));

display.display();

}
void printText(String s) {





 //getting string input in variable "s"

display.println(s);

display.display();

display.println("\n");



delay(4000);

}
