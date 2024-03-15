#include "SaveManager.h"


void SaveManager::SaveToXML()
{
    // Retrieve the text buffer
    const char* textBuffer = wdTextEdit.GetTextBuffer();

    // Create an XML document
    tinyxml2::XMLDocument doc;
    tinyxml2::XMLElement* root = doc.NewElement("root");
    doc.InsertFirstChild(root);

    // Create an element for the text
    tinyxml2::XMLElement* textElement = doc.NewElement("text");
    textElement->SetText(textBuffer);
    root->InsertEndChild(textElement);

    // Save the XML document to a file
    doc.SaveFile("output.xml");
}

void SaveManager::LoadFromXML(const std::string& filePath)
{
    // Create an XML document
    tinyxml2::XMLDocument doc;

    // Load the XML file
    if (doc.LoadFile(filePath.c_str()) != tinyxml2::XML_SUCCESS)
    {
        std::cerr << "Failed to load XML file: " << filePath << std::endl;
        return;
    }

    // Get the root element
    tinyxml2::XMLElement* root = doc.RootElement();
    if (!root)
    {
        std::cerr << "Failed to get root element." << std::endl;
        return;
    }

    // Find the <text> element
    tinyxml2::XMLElement* textElement = root->FirstChildElement("text");
    if (!textElement)
    {
        std::cerr << "Failed to find <text> element." << std::endl;
        return;
    }

    // Get the text content
    const char* loadedText = textElement->GetText();
    if (!loadedText)
    {
        std::cerr << "Failed to get text content." << std::endl;
        return;
    }

    // Load the text into the WDTextEdit instance
    wdTextEdit.SetTextBuffer(loadedText);

    std::cout << "Loaded text: " << loadedText << std::endl;
}



