#include "WDTools.h"

void WDTools::OnUpdate()
{
	if (show)
	{
		ImGui::Begin("Sample Window");
		ImGui::Text("Hi");
		ImGui::SetItemTooltip("Hello");


		if (ImGui::Button("Click Me!"))
		{
			//Action
		}
		ImGui::SetItemTooltip("This is a button");

		ImGui::SameLine();

		if (ImGui::Button("Click Me2!"))
		{
			//Action
		}


		// End the window
		ImGui::End();
	}
}
