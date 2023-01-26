#include <Adafruit_NeoPixel.h>

#define PIXEL_PIN 7   // Data Pin of LED ring
#define PIXEL_PIN_2 8   // Data Pin of second LED ring 
#define PIXELS_NUM  12   // Number of LEDs in the strip
#define BRIGHTNESS   250   // use 96 for medium brightness

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXELS_NUM, PIXEL_PIN, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel strip2 = Adafruit_NeoPixel(PIXELS_NUM, PIXEL_PIN_2, NEO_GRB + NEO_KHZ800);

// colors
uint32_t light_off =  strip.Color(0, 0, 0);
uint32_t blue =  strip.Color(0, 0, 255);
uint32_t red =  strip.Color(255, 0, 0);
uint32_t green =  strip.Color(0, 255, 0);
uint32_t lightBlue =  strip.Color(0, 200, 255);
uint32_t purple =  strip.Color(255, 0, 150);
uint32_t orange = strip.Color(255, 100, 0);
uint32_t bright_blue = strip.Color(75, 75, 255);


void setup() {
  // LEDs initiation 
  strip.begin();
  strip.setBrightness(BRIGHTNESS);
  strip.show(); // Initialize all pixels to 'off'
  strip2.begin();
  strip2.setBrightness(BRIGHTNESS);
  strip2.show(); // Initialize all pixels to 'off'

}


void loop() {
  // put your main code here, to run repeatedly:
}


// ________ANIMATIONS CODE________
void solidStrip(uint32_t c) {
  /**
     Fill the whole strip in one color
  */
  for (uint16_t i = 0; i < strip.numPixels() / 2; i++) {
    strip.setPixelColor(i, c);
    strip.setPixelColor(strip.numPixels() - i - 1, c);
    strip2.setPixelColor(i, c);
    strip2.setPixelColor(strip.numPixels() - i - 1, c);
       
  }
  strip.show();
  strip2.show();
}

// Fade
void blue_fade(int speed, int del) {
  uint16_t i, j;
  for (j = 255; j > 1; j--) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, j);
      strip2.setPixelColor(i, 0, 0, j);
    }
    strip.show();
    strip2.show();
    delay(speed);
  }
  delay(del);

  for (j = 2; j < 255; j++) {
    for (i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, 0, 0, j);
      strip2.setPixelColor(i, 0, 0, j);
    }
    strip.show();
    strip2.show();
    delay(speed);
  }
}//Fade


// Chase
void chase(int speed, uint32_t color, int pixel_num) {
  /**
    This function creates given number of pixels that do a loop through the LED strip.
    @speed: the speed of the movement of the animation (sets the delay time)
    @color: color of the animation
    @pixel_num: how many pixels to be lighten up.
  */
  uint16_t i, j, k;  //ints for for loops
  k = 0;
  //  solidStrip((0, 0, 0)); // clear strip
  for (i = 0; i < pixel_num; i++) {
    strip.setPixelColor(i + j, color);
    strip2.setPixelColor(i + j, color);
  }
  for (j = 0; j < (strip.numPixels()); j++) { // go over all the pixels in the strip

    if (j > (strip.numPixels() - pixel_num)) { // reaching out of bounds
      strip.setPixelColor(k, color);
      strip2.setPixelColor(k, color);
      strip.setPixelColor(j - 1, (0, 0, 0));
      strip2.setPixelColor(j - 1, (0, 0, 0));
      k = k + 1;
    }

    else { //in bounds
      if (j != 0) {
        strip.setPixelColor(pixel_num + j - 1, color);
        strip2.setPixelColor(pixel_num + j - 1, color);
        strip.setPixelColor(j - 1, (0, 0, 0));
        strip2.setPixelColor(j - 1, (0, 0, 0));
      }
      else {
        strip.setPixelColor(strip.numPixels() - 1, (0, 0, 0));
        strip2.setPixelColor(strip.numPixels() - 1, (0, 0, 0));
      }
    }
    strip.show();
    strip2.show();
    delay(speed);
  }
}//Chase


void back_forth(int speed, uint32_t color, int pixel_num) {
  /**
    This function creates given number of pixels that do a back and forth through the LED strip.
    @speed: the speed of the movement of the animation (sets the delay time)
    @color: color of the animation
    @pixel_num: how many pixels to be lighten up.
  */
  uint16_t i, j;  //ints for for loops
  for (j = 0; j < (strip.numPixels() - pixel_num + 1); j++) { // forth
    solidStrip((0, 0, 0)); // clear strip
    for (i = 0; i < pixel_num; i++) {
      strip.setPixelColor(i + j, color);
      strip2.setPixelColor(i + j, color);
    }

    strip.show();
    strip2.show();
    delay(speed);
  }

  for (j = j - 1; j > 0; j--) { //back
    solidStrip((0, 0, 0)); // clear strip
    for (i = 0; i < pixel_num; i++) {
      strip.setPixelColor(i + j, color);
      strip2.setPixelColor(i + j, color);
    }
    strip.show();
    strip2.show();
    delay(speed);
  }
}// back forth


// Point
void point(int speed, uint32_t color, int pixel_num) {
  uint16_t i, j;  //ints for for loops
  // second color for middle point
  uint32_t p_color = strip.Color(255, 80, 0);
  solidStrip((0, 0, 0)); // clear strip

  // The point to place
  strip.setPixelColor(strip.numPixels() / 2, p_color);
  strip2.setPixelColor(strip.numPixels() / 2, p_color);
  strip.setPixelColor(strip.numPixels() / 2 - 1, p_color);
  strip2.setPixelColor(strip.numPixels() / 2 - 1, p_color);
  for (i = 0; i < (strip.numPixels() / 2); i++) {
    if (i < (strip.numPixels() / 2 - pixel_num)) {
      for (j = 0; j < pixel_num; j++) {

        strip.setPixelColor(i + j, color);
        strip2.setPixelColor(i + j, color);
        strip.setPixelColor(strip.numPixels() - 1 - i - j, color);
        strip2.setPixelColor(strip.numPixels() - 1 - i - j, color);

        if (i != 0 and j == 0) {
          strip.setPixelColor(i - 1, 0, 0, 0);
          strip2.setPixelColor(i - 1, 0, 0, 0);
          strip.setPixelColor(strip.numPixels() - i, 0, 0, 0);
          strip2.setPixelColor(strip.numPixels() - i, 0, 0, 0);
        }
      }
    }
    else {
      strip.setPixelColor(i - 1, 0, 0, 0);
      strip2.setPixelColor(i - 1, 0, 0, 0);
      strip.setPixelColor(strip.numPixels() - i, 0, 0, 0);
      strip2.setPixelColor(strip.numPixels() - i, 0, 0, 0);
    }
    strip.show();
    strip2.show();
    delay(speed);

  }

}//point


// Decent
void decent(int speed, uint32_t color) {
  uint16_t i;  //ints for for loops
  solidStrip(color);
  delay(speed * 2);
  for (i = 0; i < (strip.numPixels() / 2); i++) {
    strip.setPixelColor(i, 0, 0, 0);
    strip2.setPixelColor(i, 0, 0, 0);
    strip.setPixelColor(strip.numPixels() - 1 - i, 0, 0, 0);
    strip2.setPixelColor(strip.numPixels() - 1 - i, 0, 0, 0);
    strip.show();
    strip2.show();
    delay(speed);
  }
} // decent


void blink_(int speed, uint32_t color) {
  solidStrip(color);
  delay(speed);
  blue_fade(0.5, 60);
} //blink


// Eyes
void eyes(uint32_t color) {
  int i, j;
  j = 22;
  for (i = 0; i < 5; i++) {
    strip.setPixelColor(i + 7, color);
    strip.setPixelColor(j, color);
    j = j - 1;
  }
  strip.show();
  delay(100);
} //eyes


void spotlight(uint32_t color_p, uint32_t color, int w_time,int show_time) {
  /**
   * 
   * @color_p: the color of the added light
   * @color: main color 
   * @w_time: time between spotlights (in miliseconds)
   * @show_time: time of spotlight (in miliseconds)
   */
  solidStrip(strip.Color(0,0,0));
  uint32_t p_color = color_p;
  int i, j;
  j = 22;
  for (i = 0; i < 5; i++) {
    strip.setPixelColor(7 + i, color);
    strip.setPixelColor(j, color);
    j = j - 1;
  }

  strip.show();
  delay(w_time);

  strip.setPixelColor(4, p_color);
  strip.setPixelColor(5, p_color);
  strip.setPixelColor(6, p_color);
  
  strip.setPixelColor(12, p_color);
  strip.setPixelColor(13, p_color);

  strip.setPixelColor(16, p_color);
  strip.setPixelColor(17, p_color);
  
  strip.setPixelColor(23, p_color);
  strip.setPixelColor(24, p_color);
  strip.setPixelColor(25, p_color);

  strip.show();
  delay(show_time);
}//spotlight


// Mores
void morse(int speed, uint32_t color) {
  uint32_t off, on;
  off = strip.Color(0, 0, 0);
  on = color;
  int i;
  for (i = 0; i < 4; i++) {
    solidStrip(on);
    delay(speed);
    solidStrip(off);
    delay(speed);
  }

  delay(speed * 2);
  for (i = 0; i < 2; i++) {
    solidStrip(on);
    delay(speed);
    solidStrip(off);
    delay(speed);
  }

  delay(speed * 12);
}//morse


// Slowdown
void slow_down(int speed, uint32_t color) {
  int i;
  uint32_t off, on;
  off = strip.Color(0, 0, 0);
  on = color;
  for (i = 0; i < 36; i++) {
    if (i == 21) {
      speed = speed * 2.5;
    }

    if (i == 31) {
      speed = speed * 2;
    }

    solidStrip(on);
    delay(speed);
    solidStrip(off);
    delay(speed);
  }
}//slowdown


//Switch
void switch(int speed, uint32_t color, int pixel_num) {
  int j, i;
  solidStrip((0, 0, 0));
  for (j = 0; j < 3; j++) {
    for (i = 0; i < strip.numPixels() / 6; i++) {
      strip.setPixelColor(i + (strip.numPixels() / 3) * j, color);
      strip2.setPixelColor(i + (strip.numPixels() / 3) * j, color);
    }
  }
  strip.show();
  strip2.show();
  delay(speed);
  solidStrip((0, 0, 0));
  for (j = 0; j < 3; j++) {
    for (i = 0; i < strip.numPixels() / 6; i++) {
      strip.setPixelColor((strip.numPixels() / 6) + i + (strip.numPixels() / 3) * j, color);
      strip2.setPixelColor(i + (strip.numPixels() / 3) * j, color);
    }
  }
  strip.show();
  strip2.show();
  delay(speed);
}//switch


// ProgressBar
void progress_bar(int speed, uint32_t color) {
  int i;
  solidStrip((0, 0, 0));
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
    strip.show();
    delay(speed);
  }
  delay(2 * speed);
}// ProgressBar 
