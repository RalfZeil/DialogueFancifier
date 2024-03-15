#include "WDMenuBar.h"

WDMenuBar::WDMenuBar(WDTextEdit& wdTextEdit) : wdTextEdit(wdTextEdit) {}

void WDMenuBar::OnUpdate()
{
    if (show)
    {
        ImGui::BeginMainMenuBar();
        if (ImGui::BeginMenu("File"))
        {
            //if (ImGui::MenuItem("New"))
            //{
            //    // Implementation for "New" menu item
            //}
            if (ImGui::BeginMenu("Save as"))
            {
                // Save text to XML using SaveManager
                if (ImGui::MenuItem("XML"))
                {
                    SaveManager::GetInstance(wdTextEdit).SaveToXML();
                }
                ImGui::EndMenu();
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

    // Display the file dialog and handle the result
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
