/**
 * @file MainFrame.cpp
 * @author Ismail Abdi, Raj Ambekar
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartanmindView.h"
#include "ids.h"
#include "Game.h"
#include <wx/xml/xml.h>
#include <wx/wfstream.h>



/**
 * Initializes MainFrame with custom settings.
 */
void MainFrame::Initialize()
{

    mGame = std::make_shared<Game>();
    wxString level0File = "resources/levels/level1.xml";
    long width = 20, height = 15, tileWidth = 48, tileHeight = 48;

    int totalWidth = (int)(width * tileWidth);
    int totalHeight = (int)(height * tileHeight);


    Create(nullptr, wxID_ANY, "Spartanmind", wxDefaultPosition, wxSize(totalWidth, totalHeight));

    auto sizer = new wxBoxSizer(wxVERTICAL);

    mSpartanmindView = new SpartanmindView();
    mSpartanmindView->Initialize(this);
    sizer->Add(mSpartanmindView, 1, wxEXPAND | wxALL);

    SetSizer(sizer);
    Layout();

    auto menuBar = new wxMenuBar();
    auto fileMenu = new wxMenu();
    auto levelsMenu = new wxMenu();
    auto helpMenu = new wxMenu();
    auto TimerMenu = new wxMenu();


    menuBar->Append(fileMenu, "&File");
    menuBar->Append(levelsMenu, "&Levels");
    menuBar->Append(helpMenu, "&Help");
    menuBar->Append(TimerMenu, "&Timer");

    fileMenu->Append(wxID_EXIT, "E&xit\tAlt-X", "Quit the program");
    fileMenu->Append(IDM_SOLVE, "Solve", "Solve the game");
    TimerMenu->Append(IDM_REMOVE_TIME, "Remove 10 Seconds", "Subtract 10 seconds from timer");

    helpMenu->Append(wxID_ABOUT, "&About\tF1", "Show about dialog");

    levelsMenu->Append(IDM_LEVEL0, L"&Level 0", L"&Move to Level 0");
    levelsMenu->Append(IDM_LEVEL1, L"&Level 1", L"&Move to Level 1");
    levelsMenu->Append(IDM_LEVEL2, L"&Level 2", L"&Move to Level 2");
    levelsMenu->Append(IDM_LEVEL3, L"&Level 3", L"&Move to Level 3");

    CreateStatusBar(1, wxSTB_SIZEGRIP, wxID_ANY);

    SetStatusText("Welcome to Spartanmind!");

    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnRemoveTime, this, IDM_REMOVE_TIME);
    Bind(wxEVT_CLOSE_WINDOW, &MainFrame::OnClose, this);




    SetMenuBar(menuBar);

}

/**
 * Handles on exit menu button
 * @param event click event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

/**
 * Handles the about menu button
 * @param event click event
 */
void MainFrame::OnAbout(wxCommandEvent& event) {
 wxMessageBox("Welcome to Spartanmind!",
              "About Spartanmind", wxOK | wxICON_INFORMATION);
}



void MainFrame::OnRemoveTime(wxCommandEvent& event)
{
 if (mSpartanmindView)
 {
  mSpartanmindView->Remove10Seconds();
 }

}


void MainFrame::OnClose(wxCloseEvent& event)
{
 if (mSpartanmindView)
 {
  mSpartanmindView->Destroy();
  mSpartanmindView = nullptr;
 }

 Destroy();  // Destroy this frame
}
