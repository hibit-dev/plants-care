void setDateTime(virtuabotixRTC RTC, const char* date, const char* time)
{
  uint16_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;

  year = conv2d(date + 9);

  switch (date[0])
  {
    case 'J': month = date[1] == 'a' ? 1 : month = date[2] == 'n' ? 6 : 7; break;
    case 'F': month = 2; break;
    case 'A': month = date[2] == 'r' ? 4 : 8; break;
    case 'M': month = date[2] == 'r' ? 3 : 5; break;
    case 'S': month = 9; break;
    case 'O': month = 10; break;
    case 'N': month = 11; break;
    case 'D': month = 12; break;
  }

  day = conv2d(date + 4);
  hour = conv2d(time);
  minute = conv2d(time + 3);
  second = conv2d(time + 6);

  RTC.setDS1302Time(
    second,
    minute,
    hour,
    dayOfTheWeek(year + 2000, month, day),
    day,
    month,
    year + 2000
  );
}

uint8_t conv2d(const char* p) {
  uint8_t v = 0;
  if ('0' <= *p && *p <= '9')
    v = *p - '0';
  return 10 * v + *++p - '0';
}

/*
    To calculate the day of the week in Arduino,
    we use the Zeller's Congruence algorithm
*/
int dayOfTheWeek(int year, int month, int day) {
  if (month < 3) {
    month += 12;
    year--;
  }

  int k = year % 100;
  int j = year / 100;

  int dayOfWeek = (day + ((13 * (month + 1)) / 5) + k + (k / 4) + (j / 4) - (2 * j)) % 7;

  // Convert Zeller's result to match Arduino's day constants
  // Sunday=1, Monday=2, ..., Saturday=7
  return (dayOfWeek + 5) % 7 + 1;
}
