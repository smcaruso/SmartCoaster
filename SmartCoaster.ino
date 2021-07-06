#include <Adafruit_NeoPixel.h>

#define PIN           6
#define NUMPIXELS     4
#define BRIGHTNESS   50
#define BUTTON        2

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int red = 255;
int green = 255;
int blue = 255;

int counter = 0;
int buttonValue = 0;

bool buttonDown = false;

void setup() {

Serial.begin(9600);
pixels.begin();
pinMode(BUTTON, INPUT_PULLUP);

}

void loop() {
  
  buttonValue = digitalRead(BUTTON);

  if (buttonValue == LOW && buttonDown == false) {
    counter = 0;
    buttonDown = true;
    counter++;
  } else if (buttonValue == LOW && buttonDown == true) {
    counter ++;
  } else if (buttonValue == HIGH && buttonDown == true) {
    counter = 0;
    buttonDown = false;
  } else if (buttonValue == HIGH && buttonDown == false) {
    counter++;
  }

  Serial.print("Button ");
  Serial.print(buttonDown);
  Serial.print(", Counter ");
  Serial.println(counter);

  evaluateColors();
  printColorValues();
  updatePixels();

  delay(100);

}

void printColorValues() {
  
  Serial.print("R: ");
  Serial.print(red);
  Serial.print(" G: ");
  Serial.print(green);
  Serial.print(" B: ");
  Serial.println(blue);
  
}

void updatePixels() {
  
  pixels.clear();

  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(red, green, blue));
    pixels.show();
  }

}

void evaluateColors() {

if (buttonDown == true && counter >= 0 && counter <= 510) {
  red = counter * 0.5;
  green = counter * 0.5;
  blue = counter * 0.5;
} else if (buttonDown == true && counter > 510 && counter <= 1020) {
  red = 255 - (counter * 0.25);
  green = 255 - (counter * 0.25);
  blue = 255;
} else if (buttonDown == true && counter > 1020) {
  red = 0;
  green = 120 * (counter % 2);
  blue = 255 * (counter % 2);
}

if (buttonDown == false && counter >= 0 && counter <= 255) {
  red = counter;
  green = 0;
  blue = counter * 0.25;
} else if (buttonDown == false && counter >= 256 && counter <= 510) {
  red = 255 - (counter - 255);
  green = 0;
  blue = (255 - (counter - 255)) * 0.25;
} else if (buttonDown == false && counter > 510) {
  red = 255 * (counter % 2);
  green = 0;
  blue = 50 * (counter % 2);
}

  // if (buttonDown == false && counter % 10 == 0) {
  //   red = 0;
  //   green = 0;
  //   blue = 0;
  // } else {
  //   red = 255;
  //   green = 255;
  //   blue = 255;
  // }

}