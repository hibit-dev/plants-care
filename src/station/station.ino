// -------------------------------------------------
// Copyright (c) 2024 HiBit <https://www.hibit.dev>
// -------------------------------------------------

#include "virtuabotixRTC.h"

#define MORNING_WATERING false
#define EVENING_WATERING true

#define MORNING_WATERING_HOUR 8
#define EVENING_WATERING_HOUR 20

#define LED_RED_PIN 7
#define LED_GREEN_PIN 8

#define BUTTON_PUSH_PIN 10
#define BUTTON_TOGGLE_PIN 2

#define POTENTIOMETER_PIN A0
#define POTENTIOMETER_MIN_SECONDS 0
#define POTENTIOMETER_MAX_SECONDS 10

#define PUMP_BASE_PIN 11

#define DS1302_CLK_PIN A5
#define DS1302_DAT_PIN A4
#define DS1302_RST_PIN 13

bool morningWatered = false;
bool eveningWatered = false;

struct button {
  byte pressed = 0;
};

struct toggle {
  byte on = 0;
};

struct potentiometer {
  byte level = 0;
};

button button;
toggle toggle;

potentiometer potentiometer;

virtuabotixRTC RTC(DS1302_CLK_PIN, DS1302_DAT_PIN, DS1302_RST_PIN);

void setup()
{
  // Set pin mode for LEDs
  pinMode(LED_RED_PIN, OUTPUT);
  pinMode(LED_GREEN_PIN, OUTPUT);

  // Turn red LED ON (setup in progress...)
  digitalWrite(LED_RED_PIN, HIGH);

  delay(3000);

  // Set pin mode for buttons
  pinMode(BUTTON_TOGGLE_PIN, INPUT_PULLUP);
  pinMode(BUTTON_PUSH_PIN, INPUT_PULLUP);

  // Set pin mode for potentiometer
  pinMode(POTENTIOMETER_PIN, INPUT);

  // Set pin mode for water pump
  pinMode(PUMP_BASE_PIN, OUTPUT);

  // Set sketch compiling time
  setDateTime(RTC, __DATE__, __TIME__);

  // Turn red LED OFF and green LED ON
  digitalWrite(LED_RED_PIN, LOW);
  digitalWrite(LED_GREEN_PIN, HIGH);

  delay(1500);

  // Turn green LED OFF
  digitalWrite(LED_GREEN_PIN, LOW);
}

void loop()
{
  // Allow updates of variables
  RTC.updateTime();

  // Read input values
  button.pressed = isButtonPressed(BUTTON_PUSH_PIN);
  potentiometer.level = readPotentiometerLevelMapped(POTENTIOMETER_PIN);
  toggle.on = isToggleOn(BUTTON_TOGGLE_PIN);

  // Turn ON morning watering
  if (MORNING_WATERING && RTC.hours == MORNING_WATERING_HOUR) {
    if (morningWatered == false) {
      morningWatered = true;

      int wateringMilliseconds = getMillisecondsByPotentiometerLevel(potentiometer.level);

      turnPumpTemporaryOn(wateringMilliseconds);
    }
  } else {
    morningWatered = false;
  }

  // Turn ON evening watering
  if (EVENING_WATERING && RTC.hours == EVENING_WATERING_HOUR) {
    if (eveningWatered == false) {
      eveningWatered = true;

      int wateringMilliseconds = getMillisecondsByPotentiometerLevel(potentiometer.level);

      turnPumpTemporaryOn(wateringMilliseconds);
    }
  } else {
    eveningWatered = false;
  }

  // Turn ON manual watering
  if (button.pressed) {
    turnPumpOn();

    // Wait while the button is ON
    do {
      button.pressed = isButtonPressed(BUTTON_PUSH_PIN);

      delay(100);
    } while (button.pressed);

    turnPumpOff();
  }

  delay(5000); // Iterate every 5 seconds
}
