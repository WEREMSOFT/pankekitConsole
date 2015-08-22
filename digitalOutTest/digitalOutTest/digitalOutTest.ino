void setup() {
  pinMode(3, OUTPUT);
  pinMode(8, INPUT);
}

void loop() {
  if (digitalRead(8) == HIGH)
  {
    digitalWrite(3, HIGH);
  }  else  {
    digitalWrite(3, LOW);
  }
}
