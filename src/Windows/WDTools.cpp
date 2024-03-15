#include "WDTools.h"

WDTools::WDTools(WDTextEdit& wdTextEdit) : wdTextEdit(wdTextEdit) {}

void WDTools::OnUpdate()
{
    if (show)
    {
        ImGui::Begin("Tools");
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.8f, 1.0f), "Add Attributes at Cursor");
        ImGui::SetTooltip("Clicking on a button below adds corresponding attribute to the text at the cursor's position");

        ImGui::Separator();

        if (ImGui::Button("Undo"))
        {
            CommandManager::GetInstance().Undo();
        }

        ImGui::Separator();

        // Color picker with label and tooltip
        static ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Initial color value (white)
        ImGui::ColorEdit3("Color", (float*)&color);
        ImGui::SameLine();
        if (ImGui::Button("Add Color"))
        {
            std::string hexColor = ColorToHex(color);
            std::string commandText = "<color=" + hexColor + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }
        ImGui::SetTooltip("Adds a color attribute");

        // Slider for text size with label and tooltip
        static float sizeValue = 12.0f; // Initial value
        ImGui::SliderFloat("Size", &sizeValue, 6.0f, 36.0f);
        ImGui::SameLine();
        if (ImGui::Button("Add Size"))
        {
            std::string commandText = "<size=" + std::to_string(sizeValue) + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }
        ImGui::SetTooltip("Adds a size attribute");

        // Combo box for alignment selection with label and tooltip
        static const char* alignments[] = { "Left", "Center", "Right" };
        static int alignmentIndex = 0; // Initial alignment index
        ImGui::Combo("Alignment", &alignmentIndex, alignments, IM_ARRAYSIZE(alignments));
        ImGui::SameLine();
        if (ImGui::Button("Add Alignment"))
        {
            std::string alignmentString = alignments[alignmentIndex];
            std::string commandText = "<align=" + alignmentString + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }
        

        ImGui::End(); // End the window
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

