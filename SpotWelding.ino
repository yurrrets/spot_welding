#include <SevSeg.h>
#include "Button.h"

#define BUTTON_PIN 0        // RX PIN
#define RELAY_PIN  1        // TX PIN
#define INPUT_ANALOG_PIN A0 // Analog pin

#define NEXT_MIN_TIMEOUT_MS 2000 // min amount of time between two spottings


SevSeg sevseg; //Initiate a seven segment controller object
Button btn(BUTTON_PIN);
unsigned long prevClickTime;


// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  
  byte numDigits = 4;
  byte digitPins[] = {2, 3, 4, 5};
  byte segmentPins[] = {6, 7, 8, 9, 10, 11, 12, 13};
  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins);
  sevseg.setBrightness(90);

  btn.setup();
  prevClickTime = -NEXT_MIN_TIMEOUT_MS;
}

// the loop function runs over and over again forever
void loop() {
  int val = analogRead(INPUT_ANALOG_PIN);
  val = map(val, 0, 1023, 0, 50);
  sevseg.setNumber(val, -1);
  sevseg.refreshDisplay(); // Must run repeatedly
  
  btn.loop();
  if (btn.getVal()==CLICK && (millis() - prevClickTime > NEXT_MIN_TIMEOUT_MS))
  {
    prevClickTime = millis();
    digitalWrite(RELAY_PIN, HIGH);
    delay(val);
    digitalWrite(RELAY_PIN, LOW);
  }
}
