#include "WDTextEdit.h"

void WDTextEdit::OnUpdate()
{
	if (show)
	{


		ImGui::Begin("Text");

		//ImGui::InputTextMultiline("Input Text");
		ImGui::Text("Input Text");

		static char text[1024 * 16] =
			"/*\n"
			" The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
			" the hexadecimal encoding of one offending instruction,\n"
			" more formally, the invalid operand with locked CMPXCHG8B\n"
			" instruction bug, is a design flaw in the majority of\n"
			" Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
			" processors (all in the P5 microarchitecture).\n"
			"*/\n\n"
			"label:\n"
			"\tlock cmpxchg8b eax\n";

		static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput;
		ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);

		// Add a button
		if (ImGui::Button("Click Me!"))
		{

		}
		ImGui::SetItemTooltip("This is a button");

		ImGui::End();
	}
}
