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

        // Add other windows as needed
        windows.push_back(new WDOptions());
        windows.push_back(new WDMenuBar());
    }

    ~WindowManager() {
        // Clean up dynamically allocated memory
        for (Window* window : windows) {
            delete window;
        }
    }

    void OnUpdate();
};