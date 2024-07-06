#pragma once

#include "UI/Core/Core.h"

class RasterObject
{
  public:
	struct rasterGeometry
	{
		UI::point parent;
		UI::point offset;
	};
	
	void SetPos(UI::point &p);
	const UI::point &Pos();

	virtual void Rasterize() = 0;

	/*!
    	\brief Set absolute position
    	\param p Upper left corner
	*/

	
	virtual const UI::rect &Size() = 0;

	const rasterGeometry &GetGeometry();

  protected:
	rasterGeometry &Geometry();

  private:
	UI::point m_position = {0, 0};
	rasterGeometry m_geometry;
};