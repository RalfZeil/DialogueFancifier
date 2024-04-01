#include "WDTools.h"

WDTools::WDTools(WDTextEdit& wdTextEdit) : wdTextEdit(wdTextEdit) {}

void WDTools::OnUpdate()
{
    if (show)
    {
        ImGui::Begin("Tools");
        ImGui::TextColored(ImVec4(1.0f, 1.0f, 0.8f, 1.0f), "Add Attributes at Cursor");

        // Display tooltip only when hovering over the text
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Clicking on a button below adds corresponding attribute to the text at the cursor's position");

        ImGui::Separator();

        if (ImGui::Button("Undo"))
        {
            CommandManager::GetInstance().Undo();
        }

        ImGui::SameLine();

        if (ImGui::Button("Redo"))
        {
            CommandManager::GetInstance().Redo();
        }

        ImGui::Separator();

        // Color picker with label and tooltip
        static ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); // Initial color value (white)
        ImGui::ColorEdit3("Color", (float*)&color);

        // Display tooltip only when hovering over the color picker
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Adds a color attribute");

        ImGui::SameLine();

        if (ImGui::Button("Add Color"))
        {
            std::string hexColor = ColorToHex(color);
            std::string commandText = "<color=" + hexColor + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }

        // Slider for text size with label and tooltip
        static float sizeValue = 12.0f; // Initial value
        ImGui::SliderFloat("Size", &sizeValue, 6.0f, 36.0f);

        // Display tooltip only when hovering over the slider
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Adds a size attribute");

        ImGui::SameLine();

        if (ImGui::Button("Add Size"))
        {
            std::string commandText = "<size=" + std::to_string(sizeValue) + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }

        // Combo box for alignment selection with label and tooltip
        static const char* alignments[] = { "Left", "Center", "Right" };
        static int alignmentIndex = 0; // Initial alignment index
        ImGui::Combo("Alignment", &alignmentIndex, alignments, IM_ARRAYSIZE(alignments));

        // Display tooltip only when hovering over the combo box
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Adds an alignment attribute");

        ImGui::SameLine();

        if (ImGui::Button("Add Alignment"))
        {
            std::string alignmentString = alignments[alignmentIndex];
            std::string commandText = "<align=" + alignmentString + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText);
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }

        // Event attribute with label and tooltip
        static char customEventInput[256] = "CustomEventName"; // Initial value
        ImGui::InputText("Input Event", customEventInput, sizeof(customEventInput));

        // Display tooltip only when hovering over the input field
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Adds an event attribute");

        ImGui::SameLine();

        if (ImGui::Button("Add Event"))
        {
            std::string eventString = customEventInput;
            std::string commandText = "<event=" + eventString + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText.c_str());
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }

        ImGui::Separator();
        ImGui::Text("Custom Attribute");

        // Custom attribute name with label and tooltip
        static char customAttributeNameInput[256] = "AttributeIndentifier"; // Initial value
        ImGui::InputText("Input Attribute Name", customAttributeNameInput, sizeof(customAttributeNameInput));

        // Custom attribute value with label and tooltip
        static char customAttributeValueInput[256] = "CustomValue"; // Initial value
        ImGui::InputText("Input Attribute Value", customAttributeValueInput, sizeof(customAttributeValueInput));

        // Button to add the custom attribute
        if (ImGui::Button("Add Custom Attribute"))
        {
            std::string attributeName = customAttributeNameInput;
            std::string attributeValue = customAttributeValueInput;
            std::string commandText = "<" + attributeName + "=" + attributeValue + ">";
            InsertTextCommand* cmd = new InsertTextCommand(const_cast<char*>(wdTextEdit.GetTextBuffer()), wdTextEdit.GetCursorPos(), commandText.c_str());
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }

        // Display tooltip only when hovering over the button
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Adds a custom attribute");

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
