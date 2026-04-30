// C++ code
//
const int ledPin = 10;
const int ldrPin = A0;

void setup()
{
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ldrPin, INPUT);
}

void loop()
{
  int ldrStatus = analogRead(ldrPin);
  
  if (ldrStatus <= 500)
  {
  	digitalWrite(ledPin, HIGH);
    Serial.print("Current Light Intensity is: ");
    Serial.println(ldrStatus);
  	delay(1000); // Wait for 1000 millisecond(s)
  }
  else
  {
    digitalWrite(ledPin, LOW);
    Serial.print("Current Light Intensity is: ");
    Serial.println(ldrStatus);
  	delay(1000); // Wait for 1000 millisecond(s)
  }
}