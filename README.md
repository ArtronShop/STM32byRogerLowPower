# STM32LowPower
Arduino library to support STM32 Low Power.

## Requirement
 * [Arduino_Core_STM32](https://github.com/stm32duino/Arduino_Core_STM32) version >= 1.3.0

## API

* **`void idle(uint32_t millis)`**: enter in idle mode  
**param** millis (optional): number of milliseconds before to exit the mode. At least 1000 ms. The RTC is used in alarm mode to wakeup the chip in millis milliseconds.

* **`void sleep(uint32_t millis)`**: enter in sleep mode  
**param** millis (optional): number of milliseconds before to exit the mode. At least 1000 ms. The RTC is used in alarm mode to wakeup the chip in millis milliseconds.

* **`void deepSleep(uint32_t millis)`**: enter in deepSleep mode  
**param** millis (optional): number of milliseconds before to exit the mode. At least 1000 ms. The RTC is used in alarm mode to wakeup the chip in millis milliseconds.

* **`void attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, uint32_t mode)`**: Enable GPIO pin in interrupt mode. If the pin is a wakeup pin, it is configured as wakeup source (see board documentation).  
**param** pin: pin number  
**param** callback: pointer to callback  
**param** mode: interrupt mode (HIGH, LOW, RISING, FALLING or CHANGE)  

The board will restart when exit the deepSleep mode.  

## Hardware state

* **Idle mode**: low wake-up latency (µs range) (e.g. ARM WFI). Memories and
voltage supplies are retained. Minimal power saving mainly on the core itself.

* **sleep mode**: low wake-up latency (µs range) (e.g. ARM WFI), Memories and
voltage supplies are retained. Minimal power saving mainly on the core itself but
higher than idle mode.

* **deep sleep mode**: medium latency (ms range), clocks are gated to reduced. Memories
and voltage supplies are retained. If supported, Peripherals wake-up is possible

## Source

You can find the source files at  
https://github.com/ioxhop/STM32byRogerLowPower
