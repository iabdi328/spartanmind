/**
 * @file MainFrame.cpp
 * @author Ismail Abdi, Raj Ambekar
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartanmindView.h"
#include "Spartanmind.h"
#include "ids.h"
#include <wx/xml/xml.h>
#include <wx/wfstream.h>

wxBEGIN_EVENT_TABLE(MainFrame, wxFrame)
    EVT_MENU(wxID_EXIT, MainFrame::OnExit)
    EVT_MENU(wxID_ABOUT, MainFrame::OnAbout)
    EVT_MENU_RANGE(IDM_LOAD_LEVEL0, IDM_LOAD_LEVEL0 + 3, MainFrame::OnLoadLevel)
    EVT_CLOSE(MainFrame::OnClose)
wxEND_EVENT_TABLE()

/**
 * Initializes MainFrame with custom settings.
 */
void MainFrame::Initialize() {
    // Default level file (level0) to determine the initial window size.
    wxString level0File = "resources/levels/level1.xml";
    long width = 20, height = 15, tileWidth = 48, tileHeight = 48; // Default values
    {
        wxXmlDocument xmlDoc;
        wxFileInputStream inputStream(level0File);
        if (inputStream.IsOk() && xmlDoc.Load(inputStream)) {
            wxXmlNode* root = xmlDoc.GetRoot();
            if (root) {
                root->GetAttribute("width", "0").ToLong(&width);
                root->GetAttribute("height", "0").ToLong(&height);
                root->GetAttribute("tilewidth", "48").ToLong(&tileWidth);
                root->GetAttribute("tileheight", "48").ToLong(&tileHeight);
            }
        } else {
            wxLogError("Failed to load initial level file: %s", level0File);
        }
    }

    int totalWidth = static_cast<int>(width * tileWidth);
    int totalHeight = static_cast<int>(height * tileHeight);

    // Create the main frame with the calculated level dimensions.
    Create(nullptr, wxID_ANY, "Spartanmind", wxDefaultPosition, wxSize(totalWidth, totalHeight));

    auto sizer = new wxBoxSizer(wxVERTICAL);

    // Create Spartanmind instance as a member of MainFrame
    //mGame = new Spartanmind();  // Create the Spartanmind object and store it as a member
    mGame = new Game();

    // Create SpartanmindView and pass the Spartanmind object (not pointer) to it
    mSpartanmindView = new SpartanmindView(this, *mGame);  // Pass spartanmind by reference
    sizer->Add(mSpartanmindView, 1, wxEXPAND | wxALL);

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
        levelsMenu->Append(IDM_LOAD_LEVEL0 + i, levelLabel, wxString::Format("Load %s", levelLabel));
    }

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    menuBar->Append(fileMenu, "&File");
    menuBar->Append(levelsMenu, "&Levels");
    menuBar->Append(helpMenu, "&Help");

    SetMenuBar(menuBar);

    // Optionally load level0 immediately
    if (!mSpartanmindView->LoadFromXML(level0File)) {
        SetStatusText("Failed to load Level 0");
    } else {
        SetStatusText(wxString::Format("Loaded Level 0 (%d x %d)", totalWidth, totalHeight));
    }
}

/**
 * Handles loading levels from XML files and resizing the main frame accordingly.
 */
void MainFrame::OnLoadLevel(wxCommandEvent& event)
{
    mGame->ClearLetters();
    mGame->ClearGivens();
    mGame->ClearTrays();
    mGame->ClearContainers();
    int levelIndex = event.GetId() - IDM_LOAD_LEVEL0;
    wxString levelFile = wxString::Format("resources/levels/level%d.xml", levelIndex);

    if (!mSpartanmindView->LoadFromXML(levelFile)) {
        SetStatusText(wxString::Format("Failed to load Level %d", levelIndex));
    } else {
        // Parse the XML file again to extract the level dimensions.
        wxXmlDocument xmlDoc;
        wxFileInputStream inputStream(levelFile);
        long width = 0, height = 0, tileWidth = 48, tileHeight = 48;
        if (inputStream.IsOk() && xmlDoc.Load(inputStream)) {
            wxXmlNode* root = xmlDoc.GetRoot();
            if (root) {
                root->GetAttribute("width", "0").ToLong(&width);
                root->GetAttribute("height", "0").ToLong(&height);
                root->GetAttribute("tilewidth", "48").ToLong(&tileWidth);
                root->GetAttribute("tileheight", "48").ToLong(&tileHeight);
            }
        }
        int totalWidth = static_cast<int>(width * tileWidth);
        int totalHeight = static_cast<int>(height * tileHeight);

        // Update the client size of the main frame to match the level's dimensions.
        SetClientSize(totalWidth, totalHeight);
        Layout();
        SetStatusText(wxString::Format("Loaded Level %d (%d x %d)", levelIndex, totalWidth, totalHeight));
    }
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
