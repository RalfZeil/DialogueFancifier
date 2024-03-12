#include "WDOptions.h"

void WDOptions::OnUpdate()
{
	if (show)
	{
		ImGui::Begin("Options");

		if (ImGui::Button("Toggle Demo Window"))
		{
			showDemoWindow = !showDemoWindow;
		}
		ImGui::SetItemTooltip("Shows the demo window from ImGui for documentation and debug.");


		if (ImGui::Button("Open Popup"))
		{
			ImGui::OpenPopup("Delete?");
		}
		if (ImGui::BeginPopupModal("Delete?", NULL, ImGuiWindowFlags_AlwaysAutoResize))
		{
			ImGui::Text("All those beautiful files will be deleted.\nThis operation cannot be undone!");
			ImGui::Separator();

			//static int unused_i = 0;
			//ImGui::Combo("Combo", &unused_i, "Delete\0Delete harder\0");

			static bool dont_ask_me_next_time = false;
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
			ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
			ImGui::PopStyleVar();

			if (ImGui::Button("OK", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::SetItemDefaultFocus();
			ImGui::SameLine();
			if (ImGui::Button("Cancel", ImVec2(120, 0))) { ImGui::CloseCurrentPopup(); }
			ImGui::EndPopup();
		}

		ImGui::End();
	}
}
