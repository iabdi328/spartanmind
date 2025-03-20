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
    /// Game object for virtual-pixel handling
    Game mGame;
    /// Timer for periodic updates
	wxTimer* mGameTimer = nullptr;

    /// Game Active
    bool mGameIsActive;
    ///New level
    bool mNewLevel = false;

    /// The last stopwatch time
    long mTime = 0;
    /// StopWatch instance
    wxStopWatch mStopWatch;

	void OnPaint(wxPaintEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxTimerEvent& event);

public:

    void Initialize(wxFrame* parent);
    void OnMouseClick(wxMouseEvent& event);
    void OnLevelZero(wxCommandEvent& event);
    void OnLevelOne(wxCommandEvent &event);
    void OnLevelTwo(wxCommandEvent &event);
    void OnLevelThree(wxCommandEvent &event);
    void LoadNextLevel();
    void NewLevel(const wxString &filename, int levelNumber);
};

#endif // PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H