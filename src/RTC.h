#pragma once
#include "stm32f1xx_hal_conf.h"
#include "stm32f1xx_hal_rtc.h"

class RealTimeClock
{
public:
	struct time_t
	{
		int day;
		int hour;
		int minute;
		int second;
	};
	RealTimeClock(RTC_HandleTypeDef& rtc);
	int Start();
	int GetDate(time_t & date);
	int SetDate(time_t & date);
protected:
private:
	RTC_HandleTypeDef& m_rtc_handle;
	RTC_TimeTypeDef m_time;
	RTC_AlarmTypeDef m_alarm;
};
