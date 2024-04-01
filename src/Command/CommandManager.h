#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include "ICommand.h"
#include <stack>

class CommandManager
{
private:
    std::stack<ICommand*> commandStack;
    std::stack<ICommand*> undoStack;
    std::stack<ICommand*> redoStack;

    CommandManager() {} // Private constructor
    CommandManager(const CommandManager&) = delete; // Prevent copying
    void operator=(const CommandManager&) = delete; // Prevent assignment

public:
    static CommandManager& GetInstance()
    {
        static CommandManager instance;
        return instance;
    }

    void ExecuteCommand(ICommand* command)
    {
        command->Execute();
        commandStack.push(command);
        undoStack.push(command); // Add command to undo stack

        // Clear redo stack when a new command is executed
        while (!redoStack.empty())
        {
            delete redoStack.top();
            redoStack.pop();
        }
    }

    void Undo()
    {
        if (!undoStack.empty())
        {
            ICommand* command = undoStack.top();
            command->Undo();
            undoStack.pop();
            // Add undone command to redo stack
            redoStack.push(command);
        }
    }

    void Redo()
    {
        if (!redoStack.empty())
        {
            ICommand* command = redoStack.top();
            command->Execute();
            redoStack.pop();
            // Add redone command back to undo stack
            undoStack.push(command);
        }
    }
};

#endif // COMMAND_MANAGER_H
