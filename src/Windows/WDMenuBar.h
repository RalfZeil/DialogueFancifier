#pragma once
#include "Window.h"

#include "../Saving/SaveManager.h"
#include "WDTextEdit.h"

class WDMenuBar : public Window
{
private:
	WDTextEdit& wdTextEdit; // Reference to text box
public:
	WDMenuBar(WDTextEdit& wdTextEdit);
	void OnUpdate();
};

