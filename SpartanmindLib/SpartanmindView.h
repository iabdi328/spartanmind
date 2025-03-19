/**
* @file SpartanmindView.h
 * @author Raj Ambekar
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H

#include <wx/wx.h>
#include "Game.h"
#include "LoadLevel.h"
#include <wx/stopwatch.h>

/**
 * View class for displaying the Spartanmind game
 */
class SpartanmindView : public wxWindow
{
private:
	wxTimer* mGameTimer = nullptr; ///< Timer for periodic updates
	Game mGame;                    ///< Game object for virtual-pixel handling

    bool mGameIsActive;

    /// The last stopwatch time
    long mTime = 0;

	// Event handlers
	void OnPaint(wxPaintEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxTimerEvent& event);
	wxStopWatch mStopWatch;
    ///New level
    bool mNewLevel = false;


public:
    /**
	 * Initialize the view
	 * @param parent Parent window
	 */
    void Initialize(wxFrame* parent);
    void OnMouseClick(wxMouseEvent& event); /// Event handler for mouse clicks
    void OnLevelOne(wxCommandEvent &event);
    void OnLevelTwo(wxCommandEvent &event);
    void OnLevelThree(wxCommandEvent &event);
    void LoadNextLevel();
    void NewLevel(const wxString &filename, int levelNumber); /// Load a new level
};

#endif // PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H