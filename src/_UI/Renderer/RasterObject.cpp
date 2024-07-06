#include "RasterObject.h"

const RasterObject::rasterGeometry &RasterObject::GetGeometry()
{
	return m_geometry;
}

void RasterObject::SetPos(UI::point &p)
{
	m_position = p;
}

const UI::point &RasterObject::Pos()
{
	return m_position;
}