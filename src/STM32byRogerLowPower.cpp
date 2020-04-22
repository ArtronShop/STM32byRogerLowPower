#ifndef __STM32_BY_ROGER_LOW_POWER_CPP__
#define __STM32_BY_ROGER_LOW_POWER_CPP__

#include "STM32byRogerLowPower.h"

STM32byRogerLowPower::STM32byRogerLowPower() {

}

void STM32byRogerLowPower::idle(uint32_t millis) {
	uint32_t setTime = rt.getTime() + (millis / 1000);
	
	SCB_BASE->SCR &= ~(SCB_SCR_SLEEPDEEP); // Clear SLEEPDEEP bit
	SCB_BASE->SCR &= ~(SCB_SCR_SLEEPONEXIT); // Clear SLEEPONEXIT bit
	
	while(rt.getTime() < setTime) {
		asm("WFI"); // executing the WFI instructions
	}
}

void STM32byRogerLowPower::sleep(uint32_t millis) {
	if (millis > 0) {
		rt.createAlarm([]() {
			// Not thing
		}, rt.getTime() + (millis / 1000));
	}
  
	SCB_BASE->SCR |= SCB_SCR_SLEEPDEEP; // Set SLEEPDEEP bit
	PWR_BASE->CR &= ~(PWR_CR_PDDS); // Clear PDDS bit
	PWR_BASE->CR |= PWR_CR_LPDS; // Set LPDS bit for set voltage regulator to low-power mode
	// PWR_BASE->CR &= ~(PWR_CR_LPDS); // Clear LPDS bit

	asm("WFI"); // executing the WFI instructions

	// Reconfig clock
#if F_CPU == 8000000UL
	// nothing to do, using about 8 mA
#elif F_CPU == 16000000UL
	rcc_clk_init(RCC_CLKSRC_HSI, RCC_PLLSRC_HSE , RCC_PLLMUL_2);
#elif F_CPU == 48000000UL
	rcc_clk_init(RCC_CLKSRC_HSI, RCC_PLLSRC_HSE , RCC_PLLMUL_6);
#elif F_CPU == 72000000UL
	rcc_clk_init(RCC_CLKSRC_HSI, RCC_PLLSRC_HSE , RCC_PLLMUL_9);
#else
#error "Unknown F_CPU!?"
#endif
}

void STM32byRogerLowPower::deepSleep(uint32_t millis) {
	if (millis > 0) {
		rt.createAlarm([]() {
			// Not thing
		}, rt.getTime() + (millis / 1000));
	}
	
	SCB_BASE->SCR |= SCB_SCR_SLEEPDEEP; // Set SLEEPDEEP bit
	PWR_BASE->CR |= PWR_CR_PDDS; // Set PDDS bit
	PWR_BASE->CR |= PWR_CR_CWUF; // Clear WUF bit by Set CWUF bit
	  
	// PWR_BASE->CSR |= PWR_CSR_EWUP; // Enable WKUP pin for wakeup from Standby mode

	asm("WFI"); // executing the WFI instructions
}

void STM32byRogerLowPower::attachInterruptWakeup(uint32_t pin, voidFuncPtrVoid callback, ExtIntTriggerMode mode, LP_Mode LowPowerMode) {
	if ((LowPowerMode == IDLE_MODE) || (LowPowerMode == SLEEP_MODE)) {
		attachInterrupt(pin, callback, mode);
		if (LowPowerMode == IDLE_MODE) idle();
		if (LowPowerMode == SLEEP_MODE) sleep();
	} else if (DEEPSLEEP_MODE == DEEPSLEEP_MODE) {
		PWR_BASE->CSR |= PWR_CSR_EWUP; // Enable WKUP pin for wakeup from Standby mode
		deepSleep();
	}
}

STM32byRogerLowPower LowPower;

#endif
