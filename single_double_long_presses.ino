// ESP32: Button - Debounced single / double / long press detector
// Wiring (recommended):
//  - Button one side -> GPIO4
//  - Button other side -> GND
//  - Use INPUT_PULLUP in software

// for circuit, you can refer to: index.html in the root of this repo

const int BUTTON_PIN = 4;
const int LED_PIN    = 2;   // optional demo LED

// timing constants (ms)
const unsigned long DEBOUNCE_MS     = 50;   // debounce interval
const unsigned long DOUBLE_CLICK_MS = 300;  // time window to capture double click
const unsigned long LONG_PRESS_MS   = 800;  // threshold for long press

// state variables
int lastStableState = HIGH;    // debounced stable state
int lastRawState    = HIGH;    // last read raw state
unsigned long lastDebounceTime = 0;

unsigned long pressStartTime = 0;   // when a stable press started
unsigned long lastReleaseTime = 0;  // when last stable release happened

int clickCount = 0;                 // number of short releases seen
bool longPressFired = false;        // whether long press has already been handled

// optional demo
bool ledState = false;

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
  Serial.println("--- Button demo: single/double/long (debounced) ---");
}

void loop() {
  unsigned long now = millis();
  int raw = digitalRead(BUTTON_PIN);

  // 1) Debounce: update stable state only if raw remains same for DEBOUNCE_MS
  if (raw != lastRawState) {
    // noise detected, reset debounce timer
    lastDebounceTime = now;
    lastRawState = raw;
  }

  if ((now - lastDebounceTime) > DEBOUNCE_MS) {
    // raw state has been stable for >= debounce time
    if (lastStableState != raw) {
      // stable state changed -> it's a real edge
      lastStableState = raw;

      if (lastStableState == LOW) {
        // --- stable press detected ---
        pressStartTime = now;
        longPressFired = false; // allow detection while held
        // NOTE: we DON'T increment clickCount here; count on release
      } else {
        // --- stable release detected ---
        unsigned long pressDuration = now - pressStartTime;

        if (longPressFired) {
          // it was a long press (already handled), ignore release for clicks
          // Reset click tracking to be safe
          clickCount = 0;
          // (Optionally: handle "long release" event here)
        } else {
          // it was NOT a long press -> treat as a short click
          clickCount++;
          lastReleaseTime = now;
          // We will wait DOUBLE_CLICK_MS to see if another click follows
        }
      }
    }
  }

  // 2) While button is held, check for long press (only once per hold)
  if (lastStableState == LOW && !longPressFired) {
    if ((now - pressStartTime) >= LONG_PRESS_MS) {
      // LONG PRESS detected
      longPressFired = true;
      clickCount = 0; // cancel any click accumulation
      handleLongPress();
      // After this, we will ignore clicks on release (see above)
    }
  }

  // 3) Resolve single / double clicks after timeout
  if (clickCount > 0 && (now - lastReleaseTime) >= DOUBLE_CLICK_MS) {
    if (clickCount == 1) {
      handleSingleClick();
    } else if (clickCount == 2) {
      handleDoubleClick();
    } else {
      // catch-all for >2 clicks (could be extended to multi-click)
      Serial.print("MULTI-CLICK (count=");
      Serial.print(clickCount);
      Serial.println(")");
    }
    clickCount = 0; // reset after handling
  }

  // small idle delay (not required, keeps serial readable)
  delay(5);
}


// ---------- Handlers ----------
void handleSingleClick() {
  Serial.println("SINGLE CLICK");
  // example action: toggle LED
  ledState = !ledState;
  digitalWrite(LED_PIN, ledState);
}

void handleDoubleClick() {
  Serial.println("DOUBLE CLICK");
  // example: blink LED twice
  for (int i = 0; i < 2; ++i) {
    digitalWrite(LED_PIN, HIGH);
    delay(100);
    digitalWrite(LED_PIN, LOW);
    delay(100);
  }
  digitalWrite(LED_PIN, ledState); // restore previous state
}

void handleLongPress() {
  Serial.println("LONG PRESS");
  // example: turn LED steady on while long pressed
  digitalWrite(LED_PIN, HIGH);
  ledState = true;
}
