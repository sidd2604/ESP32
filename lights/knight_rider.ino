// you can change the pin numbers to match your wiring
// this example uses 4 relays connected to pins 16, 17, 18, and 19

// for the circuit, you can refer to the corresponding wiring diagram available in the documentation

int relays[] = {16, 17, 18, 19};
int count = 4;

void setup() {
  for(int i=0; i<count; i++){
    pinMode(relays[i], OUTPUT);
  }
}

void loop() {
  // Forward
  for(int i=0; i<count; i++){
    digitalWrite(relays[i], HIGH);
    delay(200);
    digitalWrite(relays[i], LOW);
  }

  // Backward
  for(int i=count-1; i>=0; i--){
    digitalWrite(relays[i], HIGH);
    delay(200);
    digitalWrite(relays[i], LOW);
  }
}
