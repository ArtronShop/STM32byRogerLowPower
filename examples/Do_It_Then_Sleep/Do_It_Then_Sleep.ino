#include <STM32byRogerLowPower.h>
#include <RTClock.h>

RTClock rt(RTCSEL_LSI); // initialise

#define LED_PIN PC13

void setup() {
  pinMode(LED_PIN, OUTPUT);
  
  for (int i=0;i<10;i++) {
    digitalWrite(LED_PIN, LOW);
    delay(500);
    digitalWrite(LED_PIN, HIGH);
    delay(500);
  }
  
  LowPower.deepSleep();
}

void loop() {
  delay(100);
}
