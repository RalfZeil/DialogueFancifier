#include "WDMenuBar.h"

WDMenuBar::WDMenuBar(WDTextEdit& wdTextEdit) : wdTextEdit(wdTextEdit) {}

void WDMenuBar::OnUpdate()
{
	if (show) 
	{
		ImGui::BeginMainMenuBar();
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("New")) 
			{

			}
			if (ImGui::MenuItem("Save"))
			{
				// Save text to XML using SaveManager
				SaveManager::GetInstance(wdTextEdit).SaveToXML();
			}
			if (ImGui::MenuItem("Load"))
			{

			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}
