// RGB LED Control
// This code controls an RGB LED connected to pins 15 (Red), 4 (Green), and 5 (Blue).
// It cycles through various colors with a 1-second delay between each color.
// this is a common cathode RGB LED setup


// for circuit, you can refer to: rbg.png in the root folder


int R = 15;
int G = 4;
int B = 5;

void setup() {
  pinMode(R, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(B, OUTPUT);
}

void setColor(int r, int g, int b) {
  analogWrite(R, r);
  analogWrite(G, g);
  analogWrite(B, b);
}

void loop() {
  setColor(255, 0, 0); // Red
  delay(1000);

  setColor(0, 255, 0); // Green
  delay(1000);

  setColor(0, 0, 255); // Blue
  delay(1000);

  setColor(255, 255, 0); // Yellow
  delay(1000);

  setColor(0, 255, 255); // Cyan
  delay(1000);

  setColor(255, 0, 255); // Magenta
  delay(1000);

  setColor(255, 255, 255); // White
  delay(1000);
}
