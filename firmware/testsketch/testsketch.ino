void setup() {}

void loop() {
  int reading = analogRead(11);
  Keyboard.println(reading);
  delay(100);
}

