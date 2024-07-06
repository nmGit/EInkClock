#pragma once

#include "Display.h"
#include "RasterObject.h"
#include "UI.h"
#include <string>

class Text : public RasterObject
{
  public:
	Text();
	Text(std::string s);

	virtual void Rasterize() override;

	const UI::rect &Size() override;

  protected:
  private:
	std::string m_str = "";
	font_size m_font_size = font_size::SMALL;
	color m_color = color::BLACK;
	UI::rect m_size;
};