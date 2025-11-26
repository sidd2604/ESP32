// ESP32 Joystick Reader
// This code reads the X and Y axis values from a joystick connected to an ESP32
// and prints the values to the Serial Monitor.
// The joystick's switch state is also read and displayed.
// Connections:
// VRX (X-axis) -> GPIO 34
// VRY (Y-axis) -> GPIO 35
// SW (Switch)  -> GPIO 4

// for circuit, you can refer to the corresponding schematic diagram.

// Joystick pins
#define VRX_PIN 34
#define VRY_PIN 35
#define SW_PIN  4

void setup() {
  Serial.begin(115200);

  pinMode(VRX_PIN, INPUT);
  pinMode(VRY_PIN, INPUT);
  pinMode(SW_PIN, INPUT_PULLUP); // Switch is active LOW
}

void loop() {
  int xValue = analogRead(VRX_PIN);
  int yValue = analogRead(VRY_PIN);
  int swValue = digitalRead(SW_PIN);

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.print(yValue);
  Serial.print(" | SW: ");
  Serial.println(swValue == 0 ? "Pressed" : "Released");

  delay(200);
}
