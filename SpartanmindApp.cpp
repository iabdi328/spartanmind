/**
* @file SpartanmindApp.cpp
 * @author Raj Ambekar, Ismail Abdi
 */

#include "pch.h"
#include "SpartanmindApp.h"
#include <MainFrame.h>

/**
 * Initialize the application.
 * @return init
 */
bool SpartanmindApp::OnInit()
{
	if (!wxApp::OnInit())
		return false;

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