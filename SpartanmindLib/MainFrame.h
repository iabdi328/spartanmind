/**
 * @file MainFrame.h
 * @author Ismail Abdi, Raj Ambekar
 *
 * The top-level (main) frame of the application
 */

#include <wx/wx.h>
#include "LoadLevel.h"
#include "SpartanmindView.h"

#ifndef PROJECT1_SPARTANMINDLIB_MAINFRAME_H
#define PROJECT1_SPARTANMINDLIB_MAINFRAME_H

/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
    /// Smart pointer to the game
	std::shared_ptr<Game> mGame;
    /// Smart pointer to the game view
	SpartanmindView* mSpartanmindView;

public:
	void Initialize();
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
};

#endif //PROJECT1_SPARTANMINDLIB_MAINFRAME_H