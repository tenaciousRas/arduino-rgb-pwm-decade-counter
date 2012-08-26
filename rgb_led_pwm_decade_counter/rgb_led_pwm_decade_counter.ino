// Arudino RGB LEDs w/PWM Decade Counter by Free Beachler
// 
// Demonstrates control of 1+ RGB LEDs (light emitting diodes)
// using an Arduino PWM pin and a decade counter.
// The RGB LEDs can be set to any color, and the 
// counter permits control of up to 10 LEDs.
// 
// Arudino RGB LEDs w/PWM Decade Counter by Free Beachler 
// is licensed under a Creative Commons Attribution 3.0 
// Unported License.
// Copies of the license are available at 
// http://creativecommons.org/licenses/by/3.0/
// 
// This software is provided as-is.  No warranty or guarantee
// is provided.  You assume all responsibility from its use.
#define RGB_LED_PIN_R 3  // needs to be a PWM pin
#define RGB_LED_PIN_G 5  // needs to be a PWM pin
#define RGB_LED_PIN_B 9  // needs to be a PWM pin
#define RGB_LED_COUNTER_CK 2
#define RGB_LED_COUNTER_RESET 4
#define NUMBER_OF_LEDS  4  // number of LEDs attached to decade ic

int ledRGBPins[3] = {RGB_LED_PIN_R, RGB_LED_PIN_G, RGB_LED_PIN_B};
byte ledState[NUMBER_OF_LEDS] = {1, 1, 1, 1};
unsigned long ledColor[NUMBER_OF_LEDS] = {0xFF3300, 0xBB00BB, 0x0000FF, 0xFFFFFF};
byte ledStateIndex;

void setup()  {
  pinMode(RGB_LED_PIN_R, OUTPUT);
  pinMode(RGB_LED_PIN_G, OUTPUT);
  pinMode(RGB_LED_PIN_B, OUTPUT);
  pinMode(RGB_LED_COUNTER_CK, OUTPUT);
  digitalWrite(RGB_LED_COUNTER_CK,LOW);
  pinMode(RGB_LED_COUNTER_RESET, OUTPUT);
  digitalWrite(RGB_LED_COUNTER_RESET,LOW);
  ledStateIndex = 0;
  reset(RGB_LED_COUNTER_RESET);
}

/*
* We break RGB colors into 3 duty cycles
* white = 0xFFFFFF - meaning each color
* gets 100% brightness during its 1/3 of
* the duty cycle.
*/
void loop() {
  ledColor[3] = valAsHexColorStep(analogRead(A2));
  boolean isLEDOff = (ledState[ledStateIndex] == 0 ? true : false);
  byte brightnessR = 0;
  byte brightnessG = 0;
  byte brightnessB = 0;
  unsigned long color = ledColor[ledStateIndex];
  if (!isLEDOff) {
      brightnessR = ((long) (color & 0xFF0000)) >> 15;
      brightnessG = ((long) (color & 0xFF00)) >> 8;
      brightnessB = ((long) (color & 0xFF));
  }
  if (0 < ledStateIndex) {
    analogWrite(ledRGBPins[0], 0);
    analogWrite(ledRGBPins[1], 0);
    analogWrite(ledRGBPins[2], 0);
    delayMicroseconds(1);
  }
  clock(RGB_LED_COUNTER_CK);
  ledStateIndex++;  
  analogWrite(ledRGBPins[0], brightnessR);
  analogWrite(ledRGBPins[1], brightnessG);
  analogWrite(ledRGBPins[2], brightnessB);
  delayMicroseconds(400);
  // cycle to next led
  if (NUMBER_OF_LEDS <= ledStateIndex) {
    ledStateIndex = 0;
    analogWrite(ledRGBPins[0], 0);
    analogWrite(ledRGBPins[1], 0);
    analogWrite(ledRGBPins[2], 0);
    delayMicroseconds(1);
    reset(RGB_LED_COUNTER_RESET);
  }
  /*
  analogWrite(9, 255);
  clock(RGB_LED_COUNTER_CK);
  clock(RGB_LED_COUNTER_CK);
  clock(RGB_LED_COUNTER_CK);
  clock(RGB_LED_COUNTER_CK);
    reset(RGB_LED_COUNTER_RESET);
  */
}

/*
 * Sends a clock pulse to the counter making it advance.
 */
void clock(int pin) {
  digitalWrite(pin,HIGH);
  delayMicroseconds(20);
  digitalWrite(pin,LOW);
}
 
/*
 * Resets the counter making it start counting from zero.
 */
void reset(int pin) {
  digitalWrite(pin,HIGH);
  delayMicroseconds(20);
  digitalWrite(pin,LOW);
}

long valAsHexColorStep(int val) {
  long ret = 0xFF0000;
  if (val < 338) {
    ret = 0x0000FF;
  } else if (val < 676) {
    ret = 0x00FF00;
  }
  return ret;
}

long valAsHexColorSmooth(int val) {
  long ret = (long) val * 0x4000;
  if (ret > 0xFFFFFF) {
    ret = 0xFFFFFF;
  }
  return ret;
}
