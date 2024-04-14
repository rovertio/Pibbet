#include <Adafruit_NeoPixel.h>
#define PIN 4
#define N_LEDS 12
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define button 3

//1st
#define D 1000.0  // Resistor to plus
#define Y 1500.0  // Resistor to yellow button
#define R 2300.0 // Resistor to red button
#define B 400.0  // Resistor to blue button

#define ORA 900  
#define PUR 200
#define GRE 100

//#define D 1000.0  // Resistor to plus
//#define Y 1000.0  // Resistor to yellow button
//#define R 1500.0  // Resistor to red button
//#define B 330.0  // Resistor to blue button

// define voltage drop inputs with tolerance
#define Y_d int(((Y / (Y + D)) * 1024))
#define R_d int(((R / (R + D)) * 1024))
#define B_d int(((B / (B + D)) * 1024))

#define ORA_d int(((ORA / (ORA + D)) * 1024))
#define PUR_d int(((PUR / (PUR + D)) * 1024))
#define GRE_d int(((PUR / (PUR + D)) * 1024))

#define tol 100

int r = 0;
int g = 0;
int b = 0;

int b4b_read;

void setup() {
  pinMode(button, INPUT);
  pixels.begin();
}

void loop() {
  // put your main code here, to run repeatedly:
  int b_read = analogRead(button);
  
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
    
    } else if (b_read <= ORA_d + tol && b_read >= ORA_d - tol) {
      //colorset(0, 0, 0);
      r = 125;
      g = 60;
      b = 0;
    
    } else if (b_read <= PUR_d + tol && b_read >= PUR_d - tol) {
      //colorset(0, 0, 0);
      r = 125;
      g = 0;
      b = 125;
    
    } else if (b_read <= GRE_d + tol && b_read >= GRE_d - tol) {
      //colorset(0, 0, 0);
      r = 0;
      g = 125;
      b = 0;
    
    } 
    else if (b_read >= 900) {
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