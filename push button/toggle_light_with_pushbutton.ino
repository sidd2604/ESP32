// Toggle a light on and off with a push button
// When the button is pressed, the light changes state (on to off, or off to on)
// The button uses the internal pull-up resistor


// for circuit, you can refer to: index.png in the same folder

#define BUTTON_PIN 4
#define LED_PIN 2

bool ledState = false;
bool lastButton = HIGH;

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  bool currentButton = digitalRead(BUTTON_PIN);

  if (currentButton == LOW && lastButton == HIGH) {
    ledState = !ledState;        // toggle
    digitalWrite(LED_PIN, ledState);
    delay(200);                  // debounce
  }

  lastButton = currentButton;
}
