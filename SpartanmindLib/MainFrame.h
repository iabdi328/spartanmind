/**
* @file MainFrame.h
 * @author Ismail Abdi, Raj Ambekar
 *
 * The top-level (main) frame of the application
 */

#include <wx/wx.h>
#include "SpartanmindView.h"

#ifndef PROJECT1_SPARTANMINDLIB_MAINFRAME_H
#define PROJECT1_SPARTANMINDLIB_MAINFRAME_H

//class SpartanmindView;
/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
	Game* mGame;       // Pointer to the game logic object
	SpartanmindView* mSpartanmindView; // Pointer to the game view

public:
	void Initialize();
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnClose(wxCloseEvent& event);
	void OnLoadLevel(wxCommandEvent& event);
	wxDECLARE_EVENT_TABLE();

};

#endif //PROJECT1_SPARTANMINDLIB_MAINFRAME_H