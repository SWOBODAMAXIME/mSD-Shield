/*
  RTCDemo (Display + RTC)
 */

#include <MI0283QT9.h> //include <MI0283QT2.h> or <MI0283QT9.h>
#include <Wire.h>
#include <DS1307.h>

MI0283QT9 lcd; //declare MI0283QT2 or MI0283QT9
DS1307 rtc;


void setup()
{
  //init Serial port
  Serial.begin(9600); 
  while(!Serial); //wait for serial port to connect - needed for Leonardo only
  
  //init Display
  Serial.println("Init Display...");
  lcd.init(4); //spi-clk = Fcpu/4

  //clear Screen
  lcd.clear(COLOR_WHITE);
  lcd.printOptions(1, COLOR_BLACK, COLOR_WHITE);
  lcd.printClear();

  //init RTC
  Serial.println("Init RTC...");
  //only set the date+time one time
  //  rtc.set(0, 0, 8, 24, 12, 2013); //08:00:00 24.12.2013 //sec, min, hour, day, month, year
  rtc.start();
}


void loop()
{
  uint8_t sec, min, hour, day, month;
  uint16_t year;
  char buf[16];
  
  //get time from RTC
  rtc.get(&sec, &min, &hour, &day, &month, &year);

  //serial output
  Serial.print("\nTime: ");
  Serial.print(hour, DEC);
  Serial.print(":");
  Serial.print(min, DEC);
  Serial.print(":");
  Serial.print(sec, DEC);

  Serial.print("\nDate: ");
  Serial.print(day, DEC);
  Serial.print(".");
  Serial.print(month, DEC);
  Serial.print(".");
  Serial.print(year, DEC);

  //display output
  sprintf(buf, "%02i : %02i : %02i", hour, min, sec);
  lcd.drawText(10, 5, buf, 1, COLOR_BLACK, COLOR_WHITE);

  sprintf(buf, "%02i . %02i . %04i", day, month, year);
  lcd.drawText(10, 20, buf, 1, COLOR_BLACK, COLOR_WHITE);

  //wait a second
  delay(1000);
}
