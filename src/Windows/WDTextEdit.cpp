#include "WDTextEdit.h"

WDTextEdit::WDTextEdit() : cursorPos(0) {
    // Initialize text buffer
    snprintf(text, sizeof(text),
        "/*\n"
        " The Pentium F00F bug, shorthand for F0 0F C7 C8,\n"
        " the hexadecimal encoding of one offending instruction,\n"
        " more formally, the invalid operand with locked CMPXCHG8B\n"
        " instruction bug, is a design flaw in the majority of\n"
        " Intel Pentium, Pentium MMX, and Pentium OverDrive\n"
        " processors (all in the P5 microarchitecture).\n"
        "*/\n\n"
        "label:\n"
        "\tlock cmpxchg8b eax\n");
}

WDTextEdit::~WDTextEdit() {}

void WDTextEdit::OnUpdate() {
    if (show)
    {
        ImGui::Begin("Text");

        ImGui::Text("Input Text");

        static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput | ImGuiInputTextFlags_CallbackAlways;
        ImGui::InputTextMultiline("##source", text, IM_ARRAYSIZE(text), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags,
            [](ImGuiInputTextCallbackData* data) {
                // Update the global cursor position variable
                WDTextEdit* wdTextEdit = static_cast<WDTextEdit*>(data->UserData);
                wdTextEdit->cursorPos = data->CursorPos;
                return 0;
            }, this);

        if (ImGui::Button("Insert Text"))
        {
            // Create and execute the command
            InsertTextCommand* cmd = new InsertTextCommand(text, cursorPos, " inserted text");
            CommandManager::GetInstance().ExecuteCommand(cmd);
        }
        ImGui::SetItemTooltip("This inserts text at the cursor position");

        if (ImGui::Button("Undo"))
        {
            // Create and execute the command
            CommandManager::GetInstance().Undo();
        }
        ImGui::SetItemTooltip("Undoes prev action");

        ImGui::End();
    }
}

const char* WDTextEdit::GetTextBuffer() const {
    return text;
}

int WDTextEdit::GetCursorPos() const {
    return cursorPos;
}
