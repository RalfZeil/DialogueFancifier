#pragma once
#include "Window.h"

class WDOptions : public Window
{
private:
	bool showDemoWindow = false;

public:
	void OnUpdate();
};

