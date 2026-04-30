#include <LowPower.h>  // Use the LowPower library

const int buttonPin = 2;           // Push-button on digital pin 2
const int ledPin = LED_BUILTIN;    // Built-in LED

volatile bool wakeFlag = false;    // Set by ISR
bool firstBoot = true;

void wakeUpISR() {
  wakeFlag = true;
}

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);  // Button as input with internal pull-up
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  if (firstBoot) {
    Serial.println("System Initialized. Going to sleep...");
    Serial.flush();
    firstBoot = false;
  }
}

void loop() {
  wakeFlag = false;
  digitalWrite(ledPin, LOW);

  // Attach interrupt before sleeping
  attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUpISR, FALLING);

  // Go to deep sleep until button interrupt occurs
  LowPower.powerDown(SLEEP_FOREVER, ADC_OFF, BOD_OFF);

  // Woke up!
  detachInterrupt(digitalPinToInterrupt(buttonPin));

  if (wakeFlag) {
    delay(50); // Debounce

    unsigned long startTime = millis();
    bool longPress = false;

    // Check if button is held down
    while (digitalRead(buttonPin) == LOW) {
      if (millis() - startTime >= 1500) {
        longPress = true;
        break;
      }
    }

    if (longPress) {
      Serial.println("Interrupt handler: touch and hold detected.");
    } else {
      Serial.println("Button pressed! Woke up from sleep...");
    }

    digitalWrite(ledPin, HIGH); // Feedback
    delay(1000);                // Wait 1 second
    digitalWrite(ledPin, LOW);

    Serial.println("Returning to sleep mode...");
    Serial.flush();

    // Wait until button is released before going back to sleep
    while (digitalRead(buttonPin) == LOW);
  }
}
