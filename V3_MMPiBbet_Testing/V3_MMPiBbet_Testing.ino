#include <Adafruit_NeoPixel.h>
#define PIN A2
#define N_LEDS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define Rbutton 0
#define Mbutton 1
#define Lbutton A1
#define dial A3

#define max_brightness 125
int push = 0;
int r = 0;
int g = 0;
int b = 0;

bool buttonState = HIGH;

void setup() {
  pinMode(Rbutton, INPUT);
  pinMode(Mbutton, INPUT);
  pinMode(Lbutton, INPUT);
  pinMode(dial, INPUT);
  pixels.begin();
}

void loop() {

  // Standby code
  int j = 0;
  while (digitalRead(dial) == buttonState) {
    b = abs(map(j, 0, 2 * max_brightness, -max_brightness, max_brightness));
    colorset(0, 0, b);
    delay(8);
    if (j == 2 * max_brightness) {
      j = 0;
    } else {
      j = j + 5;
    }
  }
  fade(r, g, b);
  r, g, b = 0;


  while (digitalRead(dial) != buttonState) {
    r, g, b = 0;
    // Press right button
    if (digitalRead(Rbutton) != buttonState) {
      int k = 0;
      int gf;
      while (push == 0 && digitalRead(dial) != buttonState) {
        // Fire lighting
        // Check if other buttons pressed
        if (digitalRead(Mbutton) != buttonState || digitalRead(Lbutton) != buttonState) {
          push = 1;
        }
        r = abs(map(k, 0, 2 * max_brightness, -max_brightness, max_brightness)) + 20;
        for (int i = 0; i < N_LEDS; i++) {
          if ((k / 10) % 2 == 0) {
            gf = 1;
          } else {
            gf = 0;
          }
          pixels.setPixelColor(i, pixels.Color(r, 20 * ((i + gf) % 2), 0));
          pixels.show();
          delay(5);
        }
        if (k == 2 * max_brightness) {
          k = 0;
        } else {
          k++;
        }
      }
      push = 0;
    }

    // Press middle button
    else if (digitalRead(Mbutton) != buttonState) {
      r = 0;
      g = 125;
      b = 0;
      colorset(r, g, b);
      while (push == 0 && digitalRead(dial) != buttonState) {
        // Lightning lighting
        // Check if other buttons pressed
        if (digitalRead(Rbutton) != buttonState || digitalRead(Lbutton) != buttonState) {
          push = 1;
        }
      }
      push = 0;
    }

    // Press left button
    else if (digitalRead(Lbutton) != buttonState) {
      r = 0;
      g = 0;
      b = 125;
      colorset(r, g, b);
      while (push == 0 && digitalRead(dial) != buttonState) {
        // Lightning lighting
        // Check if other buttons pressed
        if (digitalRead(Mbutton) != buttonState || digitalRead(Rbutton) != buttonState) {
          push = 1;
        }
      }
      push = 0;
    } else {
      //fade(r, g, b);
      r, g, b = 0;
      colorset(r, g, b);
    }
    fade(r, g, b);
    r, g, b = 0;
    colorset(r, g, b);
  }
}


void fade(int r, int g, int b) {
  int max_color = max(r, max(g, b));
  for (int m = max_color; m > 0; m = m - 3) {
    int rm = map(m, max_color, 0, r, 0);
    int gm = map(m, max_color, 0, g, 0);
    int bm = map(m, max_color, 0, b, 0);
    colorset(rm, gm, bm);
  }
  colorset(0, 0, 0);
}

void colorset(int r, int g, int b) {
  for (int i = 0; i < N_LEDS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b));  // Moderately bright green color.

    pixels.show();  // This sends the updated pixel color to the hardware.

    delay(10);  // Delay for a period of time (in milliseconds).
  }
}
