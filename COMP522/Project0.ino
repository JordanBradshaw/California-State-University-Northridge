const int buttonPin =2;
int buttonState = 0;
int clicks = 0;
int loopFrequency;

void setup() {
  pinMode(13, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  loopCalc();
  digitalWrite(13, HIGH); // sets the digital pin 13 on
  delay(loopFrequency);            // waits for a second
  loopCalc();
  digitalWrite(13, LOW);  // sets the digital pin 13 off
  delay(loopFrequency);  
}

void loopCalc(){
buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    clicks++;
    clicks %= 4;
  }
switch (clicks){
  case 0:
loopFrequency = 1000;
    break;
  case 1:
loopFrequency = 500;
    break;
  case 2:
loopFrequency = 250;
    break;
  case 3:
loopFrequency = 125;
    break;
  }
}
