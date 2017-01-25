#if defined(ESP8266)
#include <pgmspace.h>
#else
#include <avr/pgmspace.h>
#endif
#include <Wire.h>
#include <RtcDS3231.h>
RtcDS3231<TwoWire> Rtc(Wire);
void setup() {
  Serial.begin(9600);
  Serial.println("Initializing RTC3231...");
  Rtc.Begin();
  Serial.println("Initialization completed");
  /*  Serial.print("Current time: ");
    Serial.println(__TIME__);
    Serial.print("Current date: ");
    Serial.println(__DATE__);*/
  Serial.print("Current RTC Time: ");
  RtcDateTime current = RtcDateTime(Rtc.GetDateTime());
  formatprint(current);
  Serial.print("Current PC Time: ");
  RtcDateTime date_time = RtcDateTime(__DATE__, __TIME__);
  formatprint(date_time);
  if (abs(date_time - current) > 3) { // Allow 3 seconds' difference in time  
    Serial.println("Starting to write time...");
    RtcDateTime date_time = RtcDateTime(__DATE__, __TIME__); // Acquire twice to get a more accurate time
    Rtc.SetDateTime(date_time);
    Serial.print("RTC Time: ");
    formatprint(Rtc.GetDateTime());
    Serial.println("Finished writing, please close this console.");
  }
  else Serial.println("RTC on time, please close this console.");
}

void loop() {
}
void formatprint(RtcDateTime data) {
  Serial.print(data.Year());
  Serial.print(" ");
  Serial.print(data.Month());
  Serial.print(" ") ;
  Serial.print(data.Day());
  Serial.print("\t") ;
  Serial.print(data.Hour());
  Serial.print(" ") ;
  Serial.print(data.Minute());
  Serial.print(" ") ;
  Serial.println(data.Second());
}

