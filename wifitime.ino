#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const char *ssid     = "PASHA 2.0";
const char *password = "090078601Aa";
const long utcOffsetInSeconds = 20500; 

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
// Define NTP Client to get time
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", utcOffsetInSeconds);
void setup(){
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
  timeClient.begin();
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address for a 128x32 pixel display
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed if it failed
  }
}
void loop() {
timeClient.update();
display.clearDisplay();
display.setTextSize(2); // Set text size to be smaller
display.setTextColor(WHITE);
int16_t x1,y1;
uint16_t w,h;
String timeText = String(timeClient.getHours()) + ":" + String(timeClient.getMinutes()) + ":" + String(timeClient.getSeconds());
display.getTextBounds(timeText.c_str(),0 ,0 ,&x1,&y1,&w,&h);
display.setCursor((SCREEN_WIDTH-w)/2,(SCREEN_HEIGHT-h)/2-h/2);
display.println(timeText);
String dayText = daysOfTheWeek[timeClient.getDay()];
display.getTextBounds(dayText.c_str(),0 ,0 ,&x1,&y1,&w,&h);
display.setCursor((SCREEN_WIDTH-w)/2,(SCREEN_HEIGHT-h)/2+h/2);
display.setTextSize(2);
display.println(dayText);
//Serial.println(timeClient.getFormattedTime());
display.display();
delay(1000);
}
