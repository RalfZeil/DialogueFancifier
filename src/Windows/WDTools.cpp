#include "WDTools.h"

WDTools::WDTools(WDTextEdit& wdTextEdit) : wdTextEdit(wdTextEdit) {}

void WDTools::OnUpdate()
{
    if (show)
    {
        ImGui::Begin("Sample Window");
        ImGui::Text("Hi");
        ImGui::SetItemTooltip("Hello");

        static ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Initial color value (white)
        ImGui::ColorEdit3("Color", (float*)&color); // Color picker
        ImGui::SameLine();
        if (ImGui::Button("Add Color"))
        {
            // Convert color to hexadecimal format
            std::string hexColor = ColorToHex(color);

            // Construct insert text command with color
            std::string commandText = "<color=" + hexColor + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }
        ImGui::SetItemTooltip("Adds a color attribute");


        static float sizeValue = 12.0f; // Initial value
        ImGui::SliderFloat("Size", &sizeValue, 6.0f, 36.0f);
        ImGui::SameLine();
        if (ImGui::Button("Add Size"))
        {
            std::string commandText = "<size=" + std::to_string(sizeValue) + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }


        static const char* alignments[] = { "Left", "Center", "Right" };
        static int alignmentIndex = 0; // Initial alignment index
        ImGui::Combo("Alignment", &alignmentIndex, alignments, IM_ARRAYSIZE(alignments));
        ImGui::SameLine();
        if (ImGui::Button("Add Alignment"))
        {
            std::string alignmentString = alignments[alignmentIndex];
            // Construct insert text command with alignment
            std::string commandText = "<align=" + alignmentString + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }

        // End the window
        ImGui::End();
    }
}


std::string WDTools::ColorToHex(const ImVec4& color)
{
    int r = static_cast<int>(color.x * 255.0f);
    int g = static_cast<int>(color.y * 255.0f);
    int b = static_cast<int>(color.z * 255.0f);

    char hexColor[8];
    sprintf_s(hexColor, "#%02X%02X%02X", r, g, b);

    return std::string(hexColor);
}

