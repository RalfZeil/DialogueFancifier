#pragma once
#include "Window.h"
#include "WDTextEdit.h"

class WDTools : public Window
{
private:
	WDTextEdit& wdTextEdit; // Reference to text box
	std::string ColorToHex(const ImVec4& color);


public:
	WDTools(WDTextEdit& wdTextEdit);
	void OnUpdate();
};

