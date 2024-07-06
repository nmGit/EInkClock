#pragma once

namespace Input
{
	enum class ButtonPress
	{
		kNone,
		kUp,
		kDown
	};
	void EnableButtons();
	bool PopPress(ButtonPress& btn);
}