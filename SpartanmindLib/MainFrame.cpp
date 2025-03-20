/**
 * @file MainFrame.cpp
 * @author Ismail Abdi, Raj Ambekar
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartanmindView.h"
#include "ids.h"
#include <wx/xml/xml.h>



/**
 * Initializes MainFrame with custom settings.
 */
void MainFrame::Initialize() {

    wxString level0File = "resources/levels/level1.xml";
    long width = 20, height = 15, tileWidth = 48, tileHeight = 48; // Default values

    int totalWidth = static_cast<int>(width * tileWidth);
    int totalHeight = static_cast<int>(height * tileHeight);


    // Create the main frame with the calculated level dimensions.
    Create(nullptr, wxID_ANY, "Spartanmind", wxDefaultPosition, wxSize(totalWidth, totalHeight));

    auto sizer = new wxBoxSizer(wxVERTICAL);

    // Create SpartanmindView and pass the Spartanmind object (not pointer) to it
    auto spartanMindView = new SpartanmindView();  // Pass spartanmind by reference
    spartanMindView->Initialize(this);

    sizer->Add(spartanMindView, 1, wxEXPAND | wxALL);

    SetSizer(sizer);
    Layout();

    auto menuBar = new wxMenuBar();
    auto fileMenu = new wxMenu();
    auto levelsMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(levelsMenu, "&Levels");
    menuBar->Append(helpMenu, "&Help");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit the program");
    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    levelsMenu->Append(IDM_LEVEL1, L"&Level 1", L"&Move to Level 1");
    levelsMenu->Append(IDM_LEVEL2, L"&Level 2", L"&Move to Level 2");
    levelsMenu->Append(IDM_LEVEL3, L"&Level 3", L"&Move to Level 3");

    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    SetStatusText("Welcome to Spartanmind!");

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnAbout, this, wxID_ABOUT);

    SetMenuBar(menuBar);

}


/**
 * Handles the exit event.
 */
void MainFrame::OnExit(wxCommandEvent& event) {
    Close(true);
}

/**
 * Handles the about dialog event.
 */
void MainFrame::OnAbout(wxCommandEvent& event) {
    wxMessageBox("Welcome to Spartanmind!",
                 "About Spartanmind", wxOK | wxICON_INFORMATION);
}

