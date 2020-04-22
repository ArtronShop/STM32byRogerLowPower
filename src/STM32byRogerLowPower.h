#ifndef __STM32_BY_ROGER_LOW_POWER_H__
#define __STM32_BY_ROGER_LOW_POWER_H__

#include <Arduino.h>
#include <RTClock.h>

#include <libmaple/pwr.h> // PWR_BASE ref
#include <libmaple/scb.h> // SCB_BASE ref

extern RTClock rt;

enum LP_Mode : uint8_t {
	IDLE_MODE,
	SLEEP_MODE,
	DEEPSLEEP_MODE
};

typedef void (*voidFuncPtrVoid)(void) ;

class STM32byRogerLowPower {
	public:
		STM32byRogerLowPower();

		void idle(uint32_t millis = 0) ;
		void sleep(uint32_t millis = 0) ;
		void deepSleep(uint32_t millis = 0);

		void attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, ExtIntTriggerMode mode, LP_Mode LowPowerMode = DEEPSLEEP_MODE);

		// void enableWakeupFrom(HardwareSerial *serial, voidFuncPtrVoid callback);
		// void enableWakeupFrom(STM32RTC *rtc, voidFuncPtr callback, void *data = NULL);

  private:
    void programRtcWakeUp(uint32_t millis);
};

extern STM32byRogerLowPower LowPower;

#endif
