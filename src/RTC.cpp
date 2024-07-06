#include "RTC.h"

RealTimeClock::RealTimeClock(RTC_HandleTypeDef& rtc)
	: m_rtc_handle(rtc)
{
	
}

void alarm_handler(RTC_HandleTypeDef* hrtc)
{
	RTC_AlarmTypeDef alarm;
	RTC_TimeTypeDef time;
	
	HAL_RTC_GetTime(hrtc, &time, RTC_FORMAT_BIN);
	
	alarm.AlarmTime = time;
	if (time.Minutes == 59)
	{
		alarm.AlarmTime.Minutes = 0;
	}
	else
	{
		
		alarm.AlarmTime.Minutes += 1;
	}
	
	//HAL_RTC_SetAlarm_IT(hrtc, &alarm, RTC_FORMAT_BIN);
}

int RealTimeClock::Start()
{
	HAL_RTC_RegisterCallback(&m_rtc_handle, HAL_RTC_ALARM_A_EVENT_CB_ID, alarm_handler);
	HAL_RTC_GetTime(&m_rtc_handle, &m_time, RTC_FORMAT_BIN);

	RCC->BDCR |= RCC_BDCR_RTCEN;

	m_alarm.AlarmTime = m_time;
	m_alarm.AlarmTime.Minutes += 1;
	
	HAL_RTC_SetAlarm_IT(&m_rtc_handle, &m_alarm, RTC_FORMAT_BIN);
	
	return 0;
}

int RealTimeClock::GetDate(time_t& date)
{
	HAL_StatusTypeDef stat = HAL_OK;
	stat = HAL_RTC_GetTime(&m_rtc_handle, &m_time, RTC_FORMAT_BIN);
	
	
	date.second = m_time.Seconds;
	date.minute = m_time.Minutes;
	date.hour = m_time.Hours;
	
	if (stat != HAL_OK)
	{
		
		return -1;
	}
	return 0;
}

int RealTimeClock::SetDate(time_t & date)
{
	HAL_StatusTypeDef stat = HAL_OK;
	
	m_time.Minutes = date.minute;
	m_time.Hours = date.hour;
	
	stat = HAL_RTC_SetTime(&m_rtc_handle, &m_time, RTC_FORMAT_BIN);
	
	if (stat != HAL_OK)
	{
		
		return -1;
	}
	return 0;
}