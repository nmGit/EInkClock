#pragma once
#include "UI.h"
#include "Widget.h"
#include "Renderer/RasterObject.h"
#include "Renderer/Text.h"
#include <string>

class Label : public Widget
{
  public:
	Label(Widget *parent, std::string lbl = "");
	virtual void Redraw() override;
	virtual void Create() override;

  protected:
	RasterObject *GetRasterObject() override;

  private:
	std::string text;
	Text m_rasterizer;
};