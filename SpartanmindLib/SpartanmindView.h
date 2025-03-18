/**
* @file SpartanmindView.h
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

	// Event handlers
	void OnPaint(wxPaintEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxTimerEvent& event);
	wxStopWatch mStopWatch;

public:
    /**
	 * Initialize the view
	 * @param parent Parent window
	 */
    void Initialize(wxFrame* parent);
	/**
	 * Destructor. Stops and cleans up the timer.
	 */
//	~SpartanmindView();

	/**
	 * Load level data from an XML file.
	 * @param filename Path to the XML file.
	 * @return True if loaded successfully, false otherwise.
	 */
//	bool LoadFromXML(const wxString& filename);

    void OnLevelOne(wxCommandEvent &event);
    void OnLevelTwo(wxCommandEvent &event);
    void OnLevelThree(wxCommandEvent &event);
    void LoadNewLevel(const wxString &filename, int levelNumber); /// Load a new level
};

#endif // PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H