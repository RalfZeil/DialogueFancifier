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
