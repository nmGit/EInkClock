#pragma once
#include <stdint.h>
enum color : uint8_t
{
	WHITE = 0x00,
	BLACK = 0x01,

	NONE
};

enum font_size : uint8_t
{
	SMALL,
	MEDIUM,
	LARGE
};

constexpr unsigned display_width = 212;
constexpr unsigned display_height = 104;
void do_display();

void display_reset();
void write_buf(int x, int y, color c);
void invert_buf(int x, int y);
void refresh_display();
void clear_screen();
