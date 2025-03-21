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
	SpartanmindView* mSpartanmindView = nullptr;

public:
	/**
	 * Initializes the application.
	 */
	void Initialize();

	/**
	 * Handles the exit command.
	 * @param event The wxCommandEvent triggered by the exit action.
	 */
	void OnExit(wxCommandEvent& event);

	/**
	 * Displays the About dialog.
	 * @param event The wxCommandEvent triggered by the About action.
	 */
	void OnAbout(wxCommandEvent& event);

	/**
	 * Handles the removal of time from the game.
	 * @param event The wxCommandEvent triggered when time removal is requested.
	 */
	void OnRemoveTime(wxCommandEvent& event);

	/**
	 * Handles the window close event.
	 * @param event The wxCloseEvent triggered when the window is closing.
	 */
	void OnClose(wxCloseEvent& event);


};

#endif //PROJECT1_SPARTANMINDLIB_MAINFRAME_H