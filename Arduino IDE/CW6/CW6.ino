#define RED_PIN 9
#define GREEN_PIN 10
#define BLUE_PIN 11
#define PIR_PIN 2

volatile bool motionDetected = false;
unsigned long lastMotionTime = 0;
const unsigned long ledDuration = 10000; // 10 seconds

void setup() {
  Serial.begin(9600);
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(PIR_PIN, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIR_PIN), motionISR, RISING);
  Serial.println("System Initialized. Waiting for motion...");
}

void loop() {
  if (motionDetected) {
    motionDetected = false;
    Serial.println("Motion detected! Activating RGB LED.");

    int r = random(0, 256);
    int g = random(0, 256);
    int b = random(0, 256);

    analogWrite(RED_PIN, r);
    analogWrite(GREEN_PIN, g);
    analogWrite(BLUE_PIN, b);

    lastMotionTime = millis();

    while (millis() - lastMotionTime < ledDuration) {
      // LED remains on for 10 seconds
    }

    digitalWrite(RED_PIN, LOW);
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
    Serial.println("LED turned off. System is idle.");
  }
}

void motionISR() {
  motionDetected = true;
}
