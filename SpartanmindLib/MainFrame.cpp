/**
 * @file MainFrame.cpp
 * @author Ismail Abdi, Raj Ambekar
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartanmindView.h"
#include "ids.h"
#include <wx/xml/xml.h>
#include <wx/wfstream.h>



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

    // Create Spartanmind instance as a member of MainFrame
    //mGame = new Spartanmind();  // Create the Spartanmind object and store it as a member


    // Create SpartanmindView and pass the Spartanmind object (not pointer) to it
    auto spartanMindView = new SpartanmindView();  // Pass spartanmind by reference
    spartanMindView->Initialize(this);

    sizer->Add(spartanMindView, 1, wxEXPAND | wxALL);

    SetSizer(sizer);
    Layout();

    CreateStatusBar();
    SetStatusText("Welcome to Spartanmind!");

    auto menuBar = new wxMenuBar();
    auto fileMenu = new wxMenu();
    auto levelsMenu = new wxMenu();
    auto helpMenu = new wxMenu();

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit the program");

    // Adding levels 0 to 3 based on XML files and setting help strings for hover status text.
    for (int i = 0; i <= 3; i++) {
        wxString levelLabel = wxString::Format("Level %d", i);
        levelsMenu->Append(IDM_LEVEL1 + i, levelLabel, wxString::Format("Load %s", levelLabel));
    }

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(levelsMenu, "&Levels");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);

    // Optionally load level0 immediately
//    if (!mSpartanmindView->LoadFromXML(level0File)) {
//        SetStatusText("Failed to load Level 0");
//    } else {
//        SetStatusText(wxString::Format("Loaded Level 0 (%d x %d)", totalWidth, totalHeight));
//    }
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

/**
 * Handles the window close event.
 */
void MainFrame::OnClose(wxCloseEvent& event) {
    if (mSpartanmindView) {
        mSpartanmindView->Destroy();
        mSpartanmindView = nullptr;
    }
    Destroy();
}
