#include "List.h"

List::List(Widget *parent) : Widget(parent)
{
}

void List::AddWidget(Widget *w)
{
	AddChild(w);
}

void List::Redraw()
{
}

void List::Create()
{
	
}

RasterObject *List::GetRasterObject()
{
	return nullptr;
}