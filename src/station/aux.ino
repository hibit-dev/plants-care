bool blinkBothLeds(int blinks)
{
  for (int i = 0; i < blinks; i++) {
    digitalWrite(LED_GREEN_PIN, HIGH);
    digitalWrite(LED_RED_PIN, HIGH);
    delay(500);

    digitalWrite(LED_GREEN_PIN, LOW);
    digitalWrite(LED_RED_PIN, LOW);
    delay(500);
  }
}

bool blinkGreenLed(int blinks)
{
  for (int i = 0; i < blinks; i++) {
    digitalWrite(LED_GREEN_PIN, HIGH);
    delay(500);

    digitalWrite(LED_GREEN_PIN, LOW);
    delay(500);
  }
}

void blinkRedLed(int blinks)
{
  for (int i = 0; i < blinks; i++) {
    digitalWrite(LED_RED_PIN, HIGH);
    delay(500);

    digitalWrite(LED_RED_PIN, LOW);
    delay(500);
  }
}

bool isButtonPressed(int pin)
{
  return digitalRead(pin) == 0;
}

bool isToggleOn(int pin)
{
  return digitalRead(pin) == 0;
}

byte readPotentiometerLevelMapped(int pin)
{
  return map(analogRead(pin), 0, 1023, 0, 255);
}
