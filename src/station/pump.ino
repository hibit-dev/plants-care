void turnPumpTemporaryOn(int delayMilliseconds)
{
  turnPumpOn();

  delay(delayMilliseconds);

  turnPumpOff();
}

void turnPumpOn()
{
  digitalWrite(LED_GREEN_PIN, HIGH);
  digitalWrite(PUMP_BASE_PIN, HIGH);
}

void turnPumpOff()
{
  digitalWrite(LED_GREEN_PIN, LOW);
  digitalWrite(PUMP_BASE_PIN, LOW);
}

int getMillisecondsByPotentiometerLevel(byte level)
{
  return map(level, 0, 255, POTENTIOMETER_MIN_SECONDS * 1000, POTENTIOMETER_MAX_SECONDS * 1000);
}
