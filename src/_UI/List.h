#pragma once

#include "Widget.h"

class List : public Widget
{
  public:
	List(Widget *parent);
	virtual void Redraw() override;
	void AddWidget(Widget *w);
	virtual void Create() override;

  protected:
	RasterObject *GetRasterObject() override;

  private:
};