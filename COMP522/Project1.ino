const int ledPin = 3;
const int potPin = A5;
int value;
void setup() {
pinMode(ledPin,OUTPUT);
pinMode(potPin,INPUT);
}

void loop() {
  value = analogRead(potPin);
  value = map(value,0,1023,0,255);
  analogWrite(ledPin, value);
  delay(100);
}
