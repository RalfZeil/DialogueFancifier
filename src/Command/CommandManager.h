#ifndef COMMAND_MANAGER_H
#define COMMAND_MANAGER_H

#include "ICommand.h"
#include <stack>

class CommandManager
{
private:
    std::stack<ICommand*> commandStack;
    std::stack<ICommand*> undoStack;

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
        undoStack.push(command);
    }

    void Undo()
    {
        if (!undoStack.empty())
        {
            ICommand* command = undoStack.top();
            command->Undo();
            undoStack.pop();
            commandStack.pop();
        }
    }
};

#endif // COMMAND_MANAGER_H