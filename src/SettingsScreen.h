#pragma once
#include "NGL/Label.h"
#include "NGL/List.h"
#include "NGL/Screen.h"

class SettingScreen : public Screen
{
  public:
	SettingScreen(Widget *parent);
	virtual void Create() override;

  protected:

  private:
	List m_main_list{this};
	Label m_label_1{
		&m_main_list, "Label 1"};
};