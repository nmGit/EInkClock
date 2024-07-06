#include "ClockMain.h"
#include "main.h"
#include "Display.h"
#include "UI.h"
#include "RTC.h"
#include "Power.h"
#include "ClockScreen.h"
#include "SettingsScreen.h"
#include "Input.h"
#include "main.h"

#include "SettingsScreen.h"

extern RTC_HandleTypeDef hrtc;
extern "C" void SystemClock_Config(void);

RealTimeClock rtc(hrtc);

SettingScreen setting_screen(nullptr);

volatile int test = 0;
void delay()
{
	for (int i = 0; i < 500000; i++)
	{
		test++;
	}
	
}
time_and_date_t current_displayed_time;
bool do_i_update(time_and_date_t& time)
{
	bool true_if_time_to_update = true;
		
	if (
		time.minutes == current_displayed_time.minutes &&
		time.hours == current_displayed_time.hours &&
		time.day == current_displayed_time.day &&
		time.day_of_month == current_displayed_time.day_of_month &&
		time.month == current_displayed_time.month &&
		time.year == current_displayed_time.year)
	{
		true_if_time_to_update = false;
		
	}
	else
	{
		current_displayed_time = time;
	}
	
	return true_if_time_to_update;
}

void ClockMain()
{
	current_displayed_time = { 0 };
	

	// Initialize Display
	do_display();
	
		
	rtc.Start();
	// Mux set button as GPIO
	
	Input::EnableButtons();
	
	// Check if set button is pressed
	if (HAL_GPIO_ReadPin(WAKEUP_GPIO_Port, WAKEUP_Pin) == GPIO_PIN_SET)
	{

		//Screens::DoSettingsScreen();
		setting_screen.Create();
	}
	else
	{
		Screens::DoClockScreen(rtc);
			
	}
	while (1)
	{
		
		
	}
	// Enable wakeup pin
//	Power::EnableWakeupPin();
	
	// Start real time clock
	
	
	
	
	
}