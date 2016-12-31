const int analog_pin = 11;

const int modifiers = MODIFIERKEY_SHIFT | MODIFIERKEY_ALT;

static const struct {
  int adc;
  int key;
} key_table[] = {
  { 70,  KEY_O },
  { 119, KEY_N },
  { 176, KEY_M },
  { 231, KEY_J },
  { 284, KEY_K },
  { 338, KEY_L },
  { 391, KEY_I },
  { 446, KEY_H },
  { 502, KEY_G },
  { 564, KEY_D },
  { 624, KEY_E },
  { 691, KEY_F },
  { 762, KEY_C },
  { 839, KEY_B },
  { 927, KEY_A },
  { 0, 0 }
};

void setup()
{}

void loop()
{
  // Look for a stable voltage plateau

  int saved_reading = 0;
  int consecutive = 0;
  while (consecutive < 3) {
    delay(1);
    int reading = analogRead(analog_pin);
    if (reading == saved_reading) {
      consecutive++;
    } else {
      consecutive = 1;
      saved_reading = reading;
    }
  }
  
  // Find closest key in the lookup table

  int i = 0;
  int key = key_table[i].key;
  int closest = abs(key_table[i].adc - saved_reading);
  do {
    i++;
    int dist = abs(key_table[i].adc - saved_reading);
    if (dist < closest) {
      key = key_table[i].key;
      closest = dist;
    }
  } while (key_table[i].key);
  if (key == 0) {
    // Idle
    return;
  }

  // Press key

  Keyboard.set_modifier(modifiers);
  Keyboard.set_key1(key);
  Keyboard.send_now();

  // Wait for release, including the long capacitor discharge tail

  while (analogRead(analog_pin) > 15) {
    delay(1);
  }
  
  Keyboard.releaseAll();
  Keyboard.send_now();
}

