#include "Widget.h"

Widget::Widget(Widget *parent)
{
	m_parent = parent;
}

void Widget::Redraw()
{
}

void Widget::Create()
{
}

void Widget::Destroy()
{
}

const UI::rect &Widget::MinimumSize()
{
	return m_minimum_geometry;
}

const UI::point &Widget::Pos()
{
	return m_position;
}

void Widget::AddChild(Widget *child)
{
}

void Widget::SetMinimumHeight(int height)
{
	m_minimum_height = height;
}

void Widget::SetMinimumWidth(int width)
{
	m_minimum_width = width;
}

void Widget::SetPos(UI::point p)
{
	m_position = p;
}

void Widget::RedrawInternal()
{
	for (Widget *w : m_children)
	{
		RedrawInternal();
	}
	Redraw();
}

void Widget::CreateInternal()
{
	Create();
	for (Widget *w : m_children)
	{
		CreateInternal();
	}
}

RasterObject *Widget::GetRasterObject()
{
	return nullptr;
}