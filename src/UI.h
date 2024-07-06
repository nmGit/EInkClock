#pragma once
#include "Display.h"

enum class day_t : uint8_t
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};

enum class month_t : uint8_t
{
	JANUARY   = 0,
	FEBRUARY,
	MARCH,
	APRIL,
	MAY,
	JUNE,
	JULY,
	AUGUST,
	SEPTEMBER,
	NOVEMBER,
	DECEMBER
};

struct time_and_date_t
{
	uint32_t year;
	month_t month;
	uint8_t day_of_month;	
	day_t day;
	uint8_t hours = 30;
	uint8_t minutes = 90;
	uint8_t seconds;
	
};
void draw_calendar(time_and_date_t& time);
void draw_rect(int pos_x, int pos_y, int width, int height, color fill_c, color fill_c_2, int fill_density, int border_width, color border_c);
void draw_invert_rect(int pos_x, int pos_y, int width, int height);
void draw_string(int x_pos, int y_pos, char* string, color c, font_size s);
void draw_time(int x_pos, int y_pos, int hour, int min);
void clear_screen();