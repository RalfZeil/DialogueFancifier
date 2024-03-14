#pragma once

// ImGui includes
#include "imgui.h"
#include "imgui_internal.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

// Command related includes
#include "../Command/CommandManager.h"
#include "../Command/InsertTextCommand.h"

// Other includes
#include <string>

class Window
{
public:
	bool show = true;
	virtual void OnUpdate();
};

