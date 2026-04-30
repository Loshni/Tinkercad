#include "DHT22.h"

#define DHTPIN 10     

DHT22 dht(DHTPIN);

float temperature; 
float totalTemperature = 0;
float minTemp;
float maxTemp;
float avg;
float stddev;
int count = 0;
float tempReadings[10]; // Store last 10 readings for stddev
int readingIndex = 0;
unsigned long lastAnalysis = 0;

void setup() {
  Serial.begin(115200);
  Serial.println(F("DHT22!"));
  delay(2000); // Let sensor stabilize
  temperature = dht.getTemperature();
  minTemp = temperature;
  maxTemp = temperature;
  totalTemperature = 0;
  count = 0;
  lastAnalysis = millis();
}

void loop() {
  temperature = dht.getTemperature();

  if (isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    delay(1000);
    return;
  }

  // Store reading for stddev
  tempReadings[readingIndex % 10] = temperature;
  readingIndex++;

  // Update min/max
  if (temperature < minTemp) minTemp = temperature;
  if (temperature > maxTemp) maxTemp = temperature;

  // Update total and count
  totalTemperature += temperature;
  count++;

  // Display temperature every second
  Serial.print(F("Temperature: "));
  Serial.print(temperature);
  Serial.println(F(" °C"));

  // Every 10 seconds, print analysis
  if (millis() - lastAnalysis >= 10000) {
    avg = totalTemperature / count;

    // Calculate standard deviation for last 10 readings
    float sum = 0, mean = 0, sd = 0;
    int n = (count < 10) ? count : 10;
    for (int i = 0; i < n; i++) {
      sum += tempReadings[i];
    }
    mean = sum / n;
    for (int i = 0; i < n; i++) {
      sd += pow(tempReadings[i] - mean, 2);
    }
    stddev = sqrt(sd / n);

    Serial.println("\n10-Second Analysis:");
    Serial.print("Min Temp: "); Serial.print(minTemp); Serial.println(" °C");
    Serial.print("Max Temp: "); Serial.print(maxTemp); Serial.println(" °C");
    Serial.print("Avg Temp: "); Serial.print(avg); Serial.println(" °C");
    Serial.print("Standard Deviation (last 10): "); Serial.print(stddev); Serial.println(" °C");
    Serial.println();

    // Reset for next 10 seconds
    totalTemperature = 0;
    count = 0;
    minTemp = temperature;
    maxTemp = temperature;
    lastAnalysis = millis();
  }

  delay(1000);
}