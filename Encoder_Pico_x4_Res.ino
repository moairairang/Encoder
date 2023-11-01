#define CLK_PIN 21 // Connect CLK to GPIO2
#define DT_PIN 22  // Connect DT to GPIO3

volatile int counter = 0;
int encoderState = 0;

void setup() {
  pinMode(CLK_PIN, INPUT_PULLUP);
  pinMode(DT_PIN, INPUT_PULLUP);
  
  // Get initial state
  encoderState = (digitalRead(DT_PIN) << 1) | digitalRead(CLK_PIN);

  // Attach interrupts
  attachInterrupt(digitalPinToInterrupt(CLK_PIN), readEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(DT_PIN), readEncoder, CHANGE);

  Serial.begin(9600);
}

void loop() {
  // Print counter value to the serial monitor
  Serial.println(counter);
  delay(100);
}

void readEncoder() {
  int newState = (digitalRead(DT_PIN) << 1) | digitalRead(CLK_PIN);

  // Determine direction of rotation
  if ((encoderState == 0 && newState == 1) || (encoderState == 1 && newState == 3) || (encoderState == 3 && newState == 2) || (encoderState == 2 && newState == 0)) {
    counter++;
} else if ((encoderState == 0 && newState == 2) || (encoderState == 2 && newState == 3) || (encoderState == 3 && newState == 1) || (encoderState == 1 && newState == 0)) {
    counter--;
}


  encoderState = newState;
}
