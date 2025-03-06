/**
 * @file SpartanmindApp.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "SpartanmindApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return
 */
bool SpartanmindApp::OnInit()
{
    if (!wxApp::OnInit())
        return false;

    // Add image type handlers
    wxInitAllImageHandlers();

    auto frame = new MainFrame();
    frame->Initialize();
    frame->Show(true);

    return true;
}
