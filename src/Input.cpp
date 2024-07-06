#include "Input.h"

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus
#include "stm32f103xb.h"
#include "stm32f1xx_hal_gpio.h"
#include "stm32f1xx_hal_exti.h"
#include "stm32f1xx_hal_cortex.h"
#ifdef __cplusplus
}
#endif // __cplusplus


namespace Input
{
	EXTI_ConfigTypeDef btn_up_cfg = { 
		.Line = EXTI_LINE_12,
		.Mode = EXTI_MODE_INTERRUPT,
		.Trigger = EXTI_TRIGGER_FALLING,
		.GPIOSel = EXTI_GPIOB
	};
	EXTI_ConfigTypeDef btn_down_cfg = { 
		.Line = EXTI_LINE_1,
		.Mode = EXTI_MODE_INTERRUPT,
		.Trigger = EXTI_TRIGGER_FALLING,
		.GPIOSel = EXTI_GPIOA
	};
	
	EXTI_HandleTypeDef btn_up_handle;
	EXTI_HandleTypeDef btn_down_handle;
	
	struct ButtonEvents
	{
		volatile unsigned up_count = 0;
		volatile unsigned down_count = 0;
	};
	
	ButtonEvents btn_events;
	void DownButtonCb()
	{
		btn_events.down_count++;
	}
	
	void UpButtonCb()
	{
		btn_events.up_count++;
	}
	
	void EnableButtons()
	{
		HAL_EXTI_SetConfigLine(&btn_up_handle, &btn_up_cfg);
		HAL_EXTI_RegisterCallback(&btn_up_handle, HAL_EXTI_COMMON_CB_ID, Input::UpButtonCb);

		HAL_EXTI_SetConfigLine(&btn_down_handle, &btn_down_cfg);
		HAL_EXTI_RegisterCallback(&btn_down_handle, HAL_EXTI_COMMON_CB_ID, Input::DownButtonCb);
		
		//NVIC_SetPriorityGrouping(0);
		HAL_NVIC_SetPriority(EXTI1_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(EXTI1_IRQn);
		
		HAL_NVIC_SetPriority(EXTI15_10_IRQn, 5, 0);
		HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);
	}
	
	bool PopPress(ButtonPress& press)
	{
		if (btn_events.up_count)
		{
			btn_events.up_count--;
			press = Input::ButtonPress::kUp;
			return true;
		}
		else if (btn_events.down_count)
		{
			btn_events.down_count--;
			press = Input::ButtonPress::kDown;
			return true;
		}
		return false;
	}
	extern "C" void EXTI1_IRQHandler()
	{
		HAL_EXTI_IRQHandler(&btn_down_handle);
	}
	extern "C" void EXTI15_10_IRQHandler()
	{
		HAL_EXTI_IRQHandler(&btn_up_handle);
		
	}
}