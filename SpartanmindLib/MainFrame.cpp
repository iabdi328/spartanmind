/**
 * @file MainFrame.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "MainFrame.h"
#include "SpartanmindView.h"

/**
 * Initialize the MainFrame window.
 */
void MainFrame::Initialize()
{
    Create(nullptr, wxID_ANY, L"Spartanmind",
           wxDefaultPosition,  wxSize( 1000,800 ));

    // Create a sizer that will lay out child windows vertically
    // one above each other
    auto sizer = new wxBoxSizer( wxVERTICAL );

    // Create the view class object as a child of MainFrame
    auto spartanmindView = new SpartanmindView();
    spartanmindView->Initialize(this);

    // Add it to the sizer
    sizer->Add(spartanmindView,1, wxEXPAND | wxALL );

    // Set the sizer for this frame
    SetSizer( sizer );

    // Layout (place) the child windows.
    Layout();

    Bind(wxEVT_COMMAND_MENU_SELECTED, &MainFrame::OnExit, this, wxID_EXIT);

}

/**
 * Exit menu option handlers
 * @param event
 */
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
