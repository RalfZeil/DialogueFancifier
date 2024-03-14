#include "ICommand.h"
#include <string>
#include <algorithm>

class InsertTextCommand : public ICommand
{
private:
    char* text;
    int cursorPos;
    std::string textToInsert;
    std::string originalText;

public:
    InsertTextCommand(char* text, int cursorPos, const std::string& textToInsert)
        : text(text), cursorPos(cursorPos), textToInsert(textToInsert)
    {
        // Store the original text before modification
        originalText = std::string(text);
    }

    void Execute() override
    {
        // Insert the text at the cursor position
        std::string newText = std::string(text, cursorPos) + textToInsert + std::string(text + cursorPos);
        size_t numCharsToCopy = std::min(newText.size(), static_cast<size_t>(1024 * 16 - 1)); // Assuming text buffer size is 1024 * 16
        strncpy_s(text, 1024 * 16, newText.c_str(), numCharsToCopy);
        text[numCharsToCopy] = '\0'; // Ensure null termination
    }

    void Undo() override
    {
        size_t numCharsToCopy = std::min(originalText.size(), static_cast<size_t>(1024 * 16 - 1)); // Assuming text buffer size is 1024 * 16
        strncpy_s(text, 1024 * 16, originalText.c_str(), numCharsToCopy);
        text[numCharsToCopy] = '\0'; // Ensure null termination
    }
};
