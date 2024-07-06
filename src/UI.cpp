#include "UI.h"
#include "Display.h"
#include <math.h>
#include <string>
#include <cstring>

#ifdef NAM
void draw_line(int x_start, int y_start, int x_end, int y_end, int width, color c)
{
	int x_start_thousandths = x_start * 1000;
	int y_start_thousandths = y_start * 1000;
	int x_end_thousandths = x_end * 1000;
	int y_end_thousandths = y_end * 1000;

	int x_step_thousandths = std::abs(x_end_thousandths - x_start_thousandths) / display_width;
	int y_step_thousandths = std::abs(y_end_thousandths - y_start_thousandths) / display_height;

	int x_pos_thousandths = x_start_thousandths;
	int y_pos_thousandths = y_start_thousandths;


	for (int x = 0; x < display_width; x++)
	{

		x_pos_thousandths += x_step_thousandths;
		y_pos_thousandths += y_step_thousandths;

		for (int i = -width / 2; i < width / 2 + 1; i++)
		{
			write_buf(x_pos_thousandths / 1000 + i, y_pos_thousandths / 1000 + i, c);
			write_buf(x_pos_thousandths / 1000 + i, y_pos_thousandths / 1000, c);
			write_buf(x_pos_thousandths / 1000, y_pos_thousandths / 1000 + i, c);
		}
	}
}

void draw_grid(int pos_x, int pos_y, int width, int height, int num_rows, int num_cols)
{

	int cell_width = width / num_cols;
	int cell_height = height / num_rows;

	int shade_width = width / num_cols;
	// Vertical Shading
	for (int i = 0; i < num_cols; i++)
	{
		if (i % 2 == 0)
		{
			
			draw_rect(pos_x + i * shade_width, pos_y, shade_width, height, BLACK, WHITE, 2, 0, NONE);
		}
		else
		{
			draw_rect(pos_x + i * shade_width, pos_y, shade_width, height, WHITE, WHITE, 1, 0, NONE);
			
		}
	}
	
	// Horizontal lines
	for (int i = 0; i < num_rows + 1; i++)
	{
		draw_line(pos_x, pos_y + i * cell_height, pos_x + width, pos_y + i * cell_height, 1, BLACK);
	}

	// Vertical lines
	for (int i = 0; i < num_cols + 1; i++)
	{
		draw_line(pos_x + i * cell_width, pos_y, pos_x + i * cell_width, pos_y + height, 1, BLACK);
	}
}
void draw_invert_rect(int pos_x, int pos_y, int width, int height)
{
	for (int x = pos_x; x < pos_x + width; x++)
	{
		for (int y = pos_y; y < pos_y + height; y++)
		{
			
			invert_buf(x, y);
		}
	}
}

void draw_rect(int pos_x, int pos_y, int width, int height, color fill_c, color fill_c_2, int fill_density, int border_width, color border_c)
{
	// Draw fill

	for (int x = pos_x; x < pos_x + width; x++)
	{
		for (int y = pos_y; y < pos_y + height; y++)
		{
			if ((y % fill_density) == 0 && (x % fill_density) == 0)
			{
				if (fill_c != NONE)
				{
					write_buf(x, y, fill_c);
				}
			}
			else
			{
				if (fill_c_2 != NONE)
				{
					write_buf(x, y, fill_c_2);
				}
			}
		}
	}

	// Draw Borders
	if (border_c != NONE)
	{
		// Top
		draw_line(pos_x, pos_y, pos_x + width, pos_y, border_width, border_c);
		// Bottom
		draw_line(pos_x, pos_y + height, pos_x + width, pos_y + height, border_width, border_c);
		// Left
		draw_line(pos_x, pos_y, pos_x, pos_y + height, border_width, border_c);
		// Right
		draw_line(pos_x + width, pos_y, pos_x + width, pos_y + height, border_width, border_c);

	}
}


void draw_string(int x_pos, int y_pos, char* string, color c, font_size s)
{
	int strlen = (int)std::strlen(string);
	color bg = NONE;
	uint8_t font_width = 0;
	uint8_t font_height = 0;
	uint16_t x_position = 0;
	uint16_t kerning = 0;
	bool there_was_a_pixel = false;
	for (int i = 0; i < strlen; i++)
	{
		uint8_t* letter = nullptr;
		if (s == font_size::MEDIUM)
		{
			letter = get_letter_24x24(string[i]);
			font_width = 24;
			font_height = 24;
			
		}
		else if (s == font_size::SMALL)
		{
			letter = get_letter_8x8(string[i]);
			font_width = 8;
			font_height = 8;
		}
		else if (s == LARGE)
		{
			letter = get_letter_48x55(string[i]);
			font_width = 48;
			font_height = 60;
		}
		uint16_t char_width = 0;
		for (uint16_t x = 0; x < font_width; x++)
		{
			for (uint16_t y = 0; y < font_height; y++)
			{

				uint16_t x_offset = font_width - (x + 1);
				uint16_t y_offset = y * font_width;
				uint16_t index = x_offset + y_offset;
				uint8_t font_byte = letter[index / 8];

				uint8_t bit_val = 0x1 & (font_byte >> (x % 8));
				//bit_val = 0x1 &(font_byte >> (x%8));
				if (bit_val)
				{
					there_was_a_pixel = true;
					//write_buf(x_pos + x - font_width * i, y_pos + y, c);
					write_buf(x_pos + x - x_position, y_pos + y, c);
				}
			}
			if (there_was_a_pixel)
			{
				
				char_width++;
			}
			there_was_a_pixel = false;
		}
		x_position += char_width + kerning;
	}
}

void draw_time(int x_pos, int y_pos, int hour, int min)
{
	
	char day_buf[8];

	snprintf(day_buf, 8, "%2d:%02d", hour, min);

	draw_string(x_pos, y_pos, day_buf, BLACK, LARGE);

}

constexpr uint8_t spacing = 2;
void draw_calendar(time_and_date_t& time)
{

	for (int x = 0; x < display_width; x++)
	{
		for (int y = 0; y < display_height; y++)
		{
			write_buf(x, y, WHITE);
		}

	}
	int cal_x = 5;
	int cal_y = 5;

	// Background
	draw_rect(0, 0, 152, 152, WHITE, NONE, 1, 0, BLACK);
	
	// Text

	int cell_width = 140 / 7;

	char day_buf[3];

	draw_grid(5, 36, 140, 72, 5, 7);
	draw_rect(5, 5, 140, 102, NONE, NONE, 2, 2, BLACK);
	draw_rect(5, 5, 140, 30, BLACK, NONE, 1, 2, BLACK);
	draw_string(10, 10, "JANUARY", BLACK, SMALL);
	draw_string(10 + 0 * cell_width, 25, "S", BLACK, SMALL);
	draw_string(10 + 1 * cell_width, 25, "M", BLACK, SMALL);
	draw_string(10 + 2 * cell_width, 25, "T", BLACK, SMALL);
	draw_string(10 + 3 * cell_width, 25, "W", BLACK, SMALL);
	draw_string(10 + 4 * cell_width, 25, "R", BLACK, SMALL);
	draw_string(10 + 5 * cell_width, 25, "F", BLACK, SMALL);
	draw_string(10 + 6 * cell_width, 25, "S", BLACK, SMALL);
	
	int week = 0;
	int weekday = 0;
	for (int day = 0; day < 31; day++)
	{
		weekday = day % 7;
		week = day / 7;
	
		snprintf(day_buf, 3, "%d", day + 1);
	
		draw_string(8 + weekday * cell_width, week * 14 + 40, day_buf, BLACK, SMALL);
	}
	//draw_time(time.hours, time.minutes);
}
#endif // NAM