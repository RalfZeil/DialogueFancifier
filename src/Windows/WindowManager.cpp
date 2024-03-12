#include "WindowManager.h"

void WindowManager::OnUpdate()
{
	for(Window* win : windows)
	{
		if (win->show) 
		{
			win->OnUpdate();
		}
	}
}
