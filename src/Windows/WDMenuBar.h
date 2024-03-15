#pragma once
#define NOMINMAX
#include <windows.h>
#undef NOMINMAX
#include <commdlg.h>
#include <string>
#include <locale> 
#include <codecvt> 

#include "ImGuiFileDialog.h"

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
	std::wstring SelectFile();
};

