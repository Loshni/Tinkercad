// Define pin connections
const int potPin = A0;      // Potentiometer connected to A0

const int ledPin = 9;       // LED connected to digital pin 9
 
void setup() {
  // Initialize serial communication at 9600 bps
  Serial.begin(9600);
}
 
void loop() {
  // Read the potentiometer value (0-1023)
  int potValue = analogRead(potPin);
 
  // Map the potentiometer value to a PWM duty cycle (0-255)
  int ledBrightness = map(potValue, 0, 1023, 0, 255);
 
  // Set the LED brightness
  analogWrite(ledPin, ledBrightness);
 
  // Calculate the duty cycle percentage (0-100)
  float dutyCycle = (ledBrightness / 255.0) * 100;
 
  // Display the analog reading and duty cycle on the Serial Plotter
  Serial.print("Analog Reading: ");
  Serial.print(potValue);
  Serial.print("\tDuty Cycle: ");
  Serial.println(dutyCycle);
 
  // Small delay to stabilize readings
  delay(100);
}