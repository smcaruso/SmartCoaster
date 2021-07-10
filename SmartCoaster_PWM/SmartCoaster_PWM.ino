#define RPIN 9
#define GPIN 10
#define BPIN 11
#define BUTTON 5
#define ADJUSTMENT A5

int counter = 0;

int red = 255;
int green =  255;
int blue = 255;

int adjustmentValue = 0;
int buttonValue = 0;
bool buttonDown = false;


void setup() {

  Serial.begin(9600);

  pinMode(RPIN, OUTPUT);
  pinMode(GPIN, OUTPUT);
  pinMode(BPIN, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

}

void loop() {

  buttonValue = digitalRead(BUTTON);
  adjustmentValue = analogRead(ADJUSTMENT);
  int adjustmentRange = map(adjustmentValue, 0, 1024, 1, 25);

  Serial.print(adjustmentValue);
  Serial.print(", ");
  Serial.println(adjustmentRange);

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

  evaluateColors();
  updateLights();
  delay(100* adjustmentRange);

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

}

void updateLights() {
  
    analogWrite(RPIN, red);
    analogWrite(GPIN, green);
    analogWrite(BPIN, blue);

}
