#include <Adafruit_NeoPixel.h>
#define PIN A2
#define N_LEDS 8
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define Rbutton 0
#define Mbutton 1
#define Lbutton A1
#define dial A3


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
  // put your main code here, to run repeatedly:
  if (digitalRead(dial) == buttonState) {
    colorset(0, 0, 0);
  } 
  else if (digitalRead(dial) != buttonState && digitalRead(Rbutton) != buttonState) {
    r = 125;
    g = 0;
    b = 0;
    colorset(r, g, b);
  }
  else if (digitalRead(dial) != buttonState && digitalRead(Mbutton) != buttonState) {
    r = 125;
    g = 125;
    b = 0;
    colorset(r, g, b);
  }
  else if (digitalRead(dial) != buttonState && digitalRead(Lbutton) != buttonState) {
    r = 0;
    g = 0;
    b = 125;
    colorset(r, g, b);
  }
  else {
    colorset(r, g, b);
  }

}

void colorset(int r, int g, int b) {
  for (int i = 0; i < N_LEDS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b));  // Moderately bright green color.

    pixels.show();  // This sends the updated pixel color to the hardware.

    delay(10);  // Delay for a period of time (in milliseconds).
  }
}

