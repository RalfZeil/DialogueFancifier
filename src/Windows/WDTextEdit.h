#pragma once
#include "Window.h"

#include "../Command/CommandManager.h"
#include <imgui.h>

class WDTextEdit : public Window
{
private:
	char text[1024 * 16]; // Make text a member variable
	int cursorPos; // Make cursorPos a member variable

public:
	WDTextEdit(); 
	~WDTextEdit(); 

	void OnUpdate();
	const char* GetTextBuffer() const; // Getter method for text buffer
	int GetCursorPos() const; // Getter method for cursor position
};

