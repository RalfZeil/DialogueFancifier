#include <iostream>
#include "tinyxml2.h"
#include "../Windows/WDTextEdit.h"

class SaveManager
{
private:
    WDTextEdit& wdTextEdit;

    SaveManager(const SaveManager&) = delete; // Prevent copying
    void operator=(const SaveManager&) = delete; // Prevent assignment

public:
    SaveManager(WDTextEdit& wdTextEditInstance) : wdTextEdit(wdTextEditInstance) {}

    static SaveManager& GetInstance(WDTextEdit& wdTextEditInstance)
    {
        static SaveManager instance(wdTextEditInstance);
        return instance;
    }

    void SaveToXML(const std::string& filename);

    void LoadFromXML(const std::string& filePath);

};

