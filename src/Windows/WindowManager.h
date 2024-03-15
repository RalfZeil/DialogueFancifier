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
    std::vector<Window*> windows;

public:
    WindowManager() {
        // Construct WDTextEdit first
        WDTextEdit* textEditWindow = new WDTextEdit();
        windows.push_back(textEditWindow);

        // Construct WDTools with WDTextEdit as argument
        WDTools* toolsWindow = new WDTools(*textEditWindow);
        windows.push_back(toolsWindow);

        WDMenuBar* menuBar = new WDMenuBar(*textEditWindow);
        windows.push_back(menuBar);

        // Add other windows
        //windows.push_back(new WDOptions()); Removed for now since its not needed
        
    }

    ~WindowManager() {
        // Clean up dynamically allocated memory
        for (Window* window : windows) {
            delete window;
        }
    }

    void OnUpdate();
};