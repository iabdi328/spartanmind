/**
* @file SpartanmindApp.cpp
 * @author Raj Ambekar, Ismail Abdi
 */

#include "pch.h"
#include "SpartanmindApp.h"
#include <MainFrame.h>
#include <wx/filename.h>
#include <wx/stdpaths.h>

/**
 * Initialize the application.
 * @return init
 */
bool SpartanmindApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

	// Set working directory to the exe's location so assets are always found
	wxFileName exePath(wxStandardPaths::Get().GetExecutablePath());
	wxSetWorkingDirectory(exePath.GetPath());

	// Add image type handlers
	wxInitAllImageHandlers();

	MainFrame* frame = new MainFrame();
	frame->Initialize();
	frame->Show(true);

	return true;
}

/**
 * Exit the application
 * @return exit
 */
int SpartanmindApp::OnExit()
{
	return wxApp::OnExit();
}