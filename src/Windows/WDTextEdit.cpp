#include "WDTextEdit.h"

WDTextEdit::WDTextEdit() : cursorPos(0) {
    // Initialize text buffer
    snprintf(text, sizeof(text),
        "Start Typing your text here!"
    );
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
                WDTextEdit* wdTextEdit = static_cast<WDTextEdit*>(data->UserData);
                wdTextEdit->cursorPos = data->CursorPos;
                return 0;
            }, this);

        // Debug print statement to verify text buffer update
        printf("Current text buffer: %s\n", text);

        ImGui::End();
    }
}

const char* WDTextEdit::GetTextBuffer() const {
    return text;
}

int WDTextEdit::GetCursorPos() const {
    return cursorPos;
}
