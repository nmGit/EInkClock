#include "Power.h"
#include "stm32f1xx_hal_pwr.h"
namespace Power
{
	void GoToSleep()
	{
		PWR->CR |= PWR_CR_CWUF;
		HAL_PWR_EnterSTANDBYMode();
	}
	
	void EnableWakeupPin()
	{
		PWR->CSR |= PWR_CSR_EWUP;
	}
}
; 