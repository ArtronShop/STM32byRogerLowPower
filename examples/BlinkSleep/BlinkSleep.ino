#include <STM32byRogerLowPower.h>
#include <RTClock.h>

RTClock rt(RTCSEL_LSI); // initialise

#define LED_PIN PC13

void setup() {
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  digitalWrite(LED_PIN, HIGH);
  LowPower.sleep(1000); // Sleep 1s
  digitalWrite(LED_PIN, LOW);
  LowPower.sleep(1000); // Sleep 1s
}
