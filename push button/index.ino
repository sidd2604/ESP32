// Push Button Example
// This code turns on an LED when a push button is pressed.
// Connections:
// Push Button -> GPIO 4
// LED         -> GPIO 2 (built-in LED on many ESP32 boards)

// for circuit, you can refer to the corresponding schematic diagram.

#define BUTTON_PIN 4
#define LED_PIN 2

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (digitalRead(BUTTON_PIN) == LOW) {
    digitalWrite(LED_PIN, HIGH);  // LED ON
  } else {
    digitalWrite(LED_PIN, LOW);   // LED OFF
  }
}
