#include <Crypto.h>
#include <SHA256.h>

void setup() {
  Serial.begin(9600);
  Serial.println("Enter a password to hash:");
}

void loop() {
  if (Serial.available() > 0) {
    String inputString = Serial.readStringUntil('\n');
    inputString.trim();

    if (inputString.length() > 0) {
      // Create SHA-256 hash
      SHA256 sha256;
      sha256.reset();
      sha256.update((uint8_t*)inputString.c_str(), inputString.length());

      byte hash[32]; // SHA-256 produces a 32-byte hash
      sha256.finalize(hash, sizeof(hash));

      // Display the input and hashed value
      Serial.print("Input: ");
      Serial.println(inputString);
      Serial.print("SHA-256 Hash: ");
      for (int i = 0; i < 32; i++) {
        if (hash[i] < 16) Serial.print("0");
        Serial.print(hash[i], HEX);
      }
      Serial.println();
      Serial.println("Enter another password to hash:");
    }
  }
}
