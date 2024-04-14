#include <Adafruit_NeoPixel.h>
#define PIN A2
#define N_LEDS 12
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define button A1

#define D 1000.0  // Resistor to plus
#define Y 1000.0  // Resistor to yellow button
#define R 2000.0  // Resistor to red button
#define B 330.0  // Resistor to blue button
// #define B 5000.0  // Resistor to blue button
#define tol 10

// define voltage drop inputs with tolerance
#define Y_d int(((Y / (Y + D)) * 1024))
#define R_d int(((R / (R + D)) * 1024))
#define B_d int(((B / (B + D)) * 1024))

int r = 0;
int g = 0;
int b = 0;

int b4b_read;

void setup() {

  pinMode(button, INPUT);
  Serial.begin(9600);
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int b_read = analogRead(button);
  Serial.println(b4b_read);
  
  Serial.print(Y_d);
  Serial.print(", ");
  Serial.print(R_d);
  Serial.print(", ");
  Serial.println(B_d);

  Serial.println(b_read);
  

  if (b_read <= b4b_read + tol && b_read >= b4b_read - tol) {
    colorset(r, g, b);
  } else {
    if (b_read <= Y_d + tol && b_read >= Y_d - tol) {
      //colorset(0, 0, 0);
      r = 125;
      g = 125;
      b = 0;
    } else if (b_read <= R_d + tol && b_read >= R_d - tol) {
      //colorset(0, 0, 0);
      r = 125;
      g = 0;
      b = 0;
    } else if (b_read <= B_d + tol && b_read >= B_d - tol) {
      //colorset(0, 0, 0);
      r = 0;
      g = 0;
      b = 125;
    } else if (b_read >= 900) {
      colorset(r, g, b);
    }
    
    else {
      r = 0;
      g = 0;
      b = 0;
    }
    
  }
  b4b_read = b_read;

}

void colorset(int r, int g, int b) {
  for (int i = 0; i < N_LEDS; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(r, g, b));  // Moderately bright green color.

    pixels.show();  // This sends the updated pixel color to the hardware.

    delay(10);  // Delay for a period of time (in milliseconds).
  }
}

