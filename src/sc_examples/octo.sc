import memset
save_reg
external CRGB *leds;
external void show();
external CRGB hsv(int h,int s,int v);
external uint8_t sin8(uint8_t a);
external float hypot(float x,float y);
external float atan2(float x,float y);
external void resetStat();
define LED_COLS 32
define LED_ROWS 32
//do not forget to udate the line below !!!!it should be LED_COLS * LED_ROWS
define NUM_LEDS 1024 
define PI 3.14529
define panel_width 128
define speed 1
uint8_t C_X ;
uint8_t C_Y;
uint8_t mapp;
uint8_t rMapRadius[NUM_LEDS];
uint8_t rMapAngle[NUM_LEDS];


void init()
{
  C_X = LED_COLS / 2;
 C_Y = LED_ROWS / 2;
 mapp = 255 / LED_COLS;
for (int x = -C_X; x < C_X + (LED_COLS % 2); x++) {
      for (int y = -C_Y; y < C_Y + (LED_ROWS % 2); y++) {

          float h=128*(atan2(y, x)/PI);
        rMapAngle[(x + C_X) *LED_ROWS+y + C_Y]= (int)(h);
       h=hypot(x,y)*mapp;
         rMapRadius[(x + C_X)*LED_ROWS +y + C_Y] = (int)(h); //thanks Sutaburosu
      }
    }
}


void main() {

resetStat();
  init();

   uint32_t t;
  //t = speed;
  while(2>1)
  {
  
 // memset(leds,0,4096*3);
  for (uint8_t x = 0; x < LED_COLS; x++) {
    for (uint8_t y = 0; y < LED_ROWS; y++) {
      uint8_t angle = rMapAngle[x*LED_ROWS+y];
      uint8_t radius = rMapRadius[x*LED_ROWS+y];
      int h=sin8(t*4+sin8(t * 4 - radius)+angle*5);
      //h=sin8(h);
 
      leds[y*panel_width+x] = hsv(t + radius, 255, h); //here in know I need to fix a bug in the compiler
    }
  }
  show();
  t=t+speed;
  }
  //delay(16);
}