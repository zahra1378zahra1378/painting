/*
This code is TFTLCD Library Example
*/
#include <Adafruit_GFX.h>        
#include <Adafruit_TFTLCD.h>  
#include <TouchScreen.h>
#if defined(__SAM3X8E__)
   #undef __FlashStringHelper::F(string_literal)
   #define F(string_literal) string_literal
#endif
#define YP A3  
#define XM A2  
#define YM 9   
#define XP 8   
#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940
TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4


#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

#define BOXSIZE 40
#define PENRADIUS 3
int oldcolor, currentcolor;
void setup(void) {
 Serial.begin(9600);
 Serial.println(F("Paint!"));
 tft.reset();
 uint16_t identifier = tft.readID();
 if(identifier == 0x9325) {
   Serial.println(F("Found ILI9325 LCD driver"));
 } else if(identifier == 0x9328) {
   Serial.println(F("Found ILI9328 LCD driver"));
 } else if(identifier == 0x7575) {
   Serial.println(F("Found HX8347G LCD driver"));
 } else if(identifier == 0x9341) {
   Serial.println(F("Found ILI9341 LCD driver"));
 } else if(identifier == 0x8357) {
  
   Serial.println(F("Found HX8357D LCD driver"));
 } else {
   Serial.print(F("Unknown LCD driver chip: "));
   Serial.println(identifier, HEX);
   Serial.println(F("If using the Adafruit 2.4\" TFT Arduino shield, the line:"));
   Serial.println(F("  #define USE_ADAFRUIT_SHIELD_PINOUT"));
   Serial.println(F("should appear in the library header (Adafruit_TFT.h)."));
   Serial.println(F("If using the breakout board, it should NOT be #defined!"));
   Serial.println(F("Also if using the breakout, double-check that all wiring"));
   Serial.println(F("matches the tutorial."));
   return;
 }
 tft.begin(identifier);
 tft.fillScreen(BLACK);
 tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED);
 tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);
 tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN);
 tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN);
 tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE,  ORANGE );
 tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA);
 tft.fillRect(BOXSIZE*2, 1, BOXSIZE, BOXSIZE, PINK);
 tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
 currentcolor = RED;
 pinMode(13, OUTPUT);
}
#define MINPRESSURE 10
#define MAXPRESSURE 1000
void loop()
{
 digitalWrite(13, HIGH);
 TSPoint p = ts.getPoint();
 digitalWrite(13, LOW);
 pinMode(XM, OUTPUT);
 pinMode(YP, OUTPUT);
 if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
   if (p.y < (TS_MINY-5)) {
     Serial.println("erase");
     tft.fillRect(0, BOXSIZE, tft.width(), tft.height()-BOXSIZE, BLACK);
   }
   p.x = map(p.x, TS_MINX, TS_MAXX, tft.width(), 0);
   p.y = map(p.y, TS_MINY, TS_MAXY, tft.height(), 0);
   if (p.y < BOXSIZE) {
      oldcolor = currentcolor;
      if (p.x < BOXSIZE) { 
        currentcolor = RED; 
        tft.drawRect(0, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE*2) {
        currentcolor = YELLOW;
        tft.drawRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE*3) {
        currentcolor = GREEN;
        tft.drawRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE*4) {
        currentcolor = CYAN;
        tft.drawRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, WHITE);
      } else if (p.x < BOXSIZE*5) {
        currentcolor = ORANGE;
        tft.drawRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, WHITE);

      }else if (p.x < BOXSIZE*5) {
        currentcolor = PINK;
        tft.drawRect(BOXSIZE*2, 1, BOXSIZE, BOXSIZE, WHITE);

      } else if (p.x < BOXSIZE*6) { currentcolor = MAGENTA; tft.drawRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, WHITE); } if (oldcolor != currentcolor) { if (oldcolor == RED) tft.fillRect(0, 0, BOXSIZE, BOXSIZE, RED); if (oldcolor == YELLOW) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, YELLOW);if (oldcolor == PINK) tft.fillRect(BOXSIZE, 0, BOXSIZE, BOXSIZE, PINK); if (oldcolor == GREEN) tft.fillRect(BOXSIZE*2, 0, BOXSIZE, BOXSIZE, GREEN); if (oldcolor == CYAN) tft.fillRect(BOXSIZE*3, 0, BOXSIZE, BOXSIZE, CYAN); if (oldcolor == ORANGE) tft.fillRect(BOXSIZE*4, 0, BOXSIZE, BOXSIZE, ORANGE); if (oldcolor == MAGENTA) tft.fillRect(BOXSIZE*5, 0, BOXSIZE, BOXSIZE, MAGENTA); } } if (((p.y-PENRADIUS) > BOXSIZE) && ((p.y+PENRADIUS) < tft.height())) {
     tft.fillCircle(p.x, p.y, PENRADIUS, currentcolor);
   }
 }
} 
