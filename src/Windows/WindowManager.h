#pragma once
#include "Window.h"
#include "WDTools.h"
#include "WDOptions.h"
#include "WDTextEdit.h"
#include "WDMenuBar.h"
#include <vector>

class WindowManager
{
private:
	std::vector<Window*> windows = {
		new WDTools(),
		new WDOptions(),
		new WDTextEdit(),
		new WDMenuBar()
	};
public:
	void OnUpdate();
};

