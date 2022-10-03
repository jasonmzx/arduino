// defines pins numbers
const int stepPin = 4; 
const int dirPin = 5; 
const int buttonPin = 7;
 
void setup() {
 
  // Sets the two pins as Outputs
  Serial.begin(9600);
  pinMode(stepPin,OUTPUT); 
  pinMode(dirPin,OUTPUT);
 
  // Button pin as input
  pinMode(buttonPin, INPUT);
}
void loop() {
  byte buttonState = digitalRead(buttonPin);
 
  int microDelay;
 
  if (buttonState == HIGH) {
    microDelay = 500;
  }
  else {
    microDelay = 1000;
  }
 
  for(int x = 0; x < 200; x++) {
    digitalWrite(stepPin,HIGH); 
    delayMicroseconds(microDelay); 
    digitalWrite(stepPin,LOW); 
    delayMicroseconds(microDelay); 
  }
  delay(100); // One second delay
 
  /*digitalWrite(dirPin,LOW); //Changes the rotations direction
 
}
 