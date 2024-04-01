#include "WDMenuBar.h"
#include <windows.h> 

WDMenuBar::WDMenuBar(WDTextEdit& wdTextEdit) : wdTextEdit(wdTextEdit), saveModalOpen(false) {}

void WDMenuBar::OnUpdate()
{
    if (show)
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Save As..."))
            {
                saveModalOpen = true; // Open the save modal
            }
            if (ImGui::MenuItem("Load"))
            {
                // Open the file dialog using ImGuiFileDialog
                ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose File", ".xml");
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }

    // Display the save modal dialog
    if (saveModalOpen)
    {
        ImGuiFileDialog::Instance()->OpenDialog("Save As", "Choose Directory", ".xml");
        saveModalOpen = false; // Reset saveModalOpen
    }

    // Handle the file dialog result for save operation
    if (ImGuiFileDialog::Instance()->Display("Save As"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            // Retrieve the selected file path from the file dialog
            std::string filepath = ImGuiFileDialog::Instance()->GetFilePathName();

            // Check if the file already has .xml extension
            if (filepath.substr(filepath.find_last_of(".") + 1) != "xml")
            {
                // Append .xml extension to the file path
                filepath += ".xml";
            }

            // Save the file
            SaveManager::GetInstance(wdTextEdit).SaveToXML(filepath);

            // Close the file dialog
            ImGuiFileDialog::Instance()->Close();
        }
    }

    // Display the file dialog and handle the result for load operation
    if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::string filePathName = ImGuiFileDialog::Instance()->GetFilePathName();
            // Load the selected XML file
            SaveManager::GetInstance(wdTextEdit).LoadFromXML(filePathName);
        }
        ImGuiFileDialog::Instance()->Close();
    }
}

std::wstring WDMenuBar::SelectFile()
{
	OPENFILENAME ofn;       // common dialog box structure
	wchar_t szFile[260];    // buffer for file name

	// Initialize OPENFILENAME
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.lpstrFile = szFile;
	ofn.nMaxFile = sizeof(szFile) / sizeof(wchar_t); // Adjusted for wchar_t
	ofn.lpstrFilter = L"XML Files\0*.xml\0All Files\0*.*\0"; // Use L prefix for wide string literals
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFileTitle = 0;
	ofn.lpstrInitialDir = NULL;
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Display the Open dialog box.
	if (GetOpenFileName(&ofn) == TRUE)
	{
		return ofn.lpstrFile;
	}
	return L""; // Return empty wide string
}
