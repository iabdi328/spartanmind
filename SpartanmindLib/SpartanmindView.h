/**
* @file SpartanmindView.h
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H

#include <wx/wx.h>
#include "Game.h"
#include <wx/stopwatch.h>

/**
 * View class for displaying the Spartanmind game
 */
class SpartanmindView : public wxWindow
{
private:
	wxTimer* mGameTimer = nullptr; ///< Timer for periodic updates
	Game* mGame;                    ///< Game object for virtual-pixel handling
	//Spartanmind* mSpartanmind;     ///< Pointer to the Spartanmind game logic

	// Event handlers
	void OnPaint(wxPaintEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnKeyDown(wxKeyEvent& event);
	void OnTimer(wxTimerEvent& event);
	wxStopWatch mStopWatch;

public:
	/**
	 * Constructor.
	 * @param parent The parent window.
	 * @param spartanmind Reference to the Spartanmind game logic.
	 */
	SpartanmindView(wxWindow* parent, Game& game);

	/**
	 * Destructor. Stops and cleans up the timer.
	 */
	~SpartanmindView();

	/**
	 * Load level data from an XML file.
	 * @param filename Path to the XML file.
	 * @return True if loaded successfully, false otherwise.
	 */
	bool LoadFromXML(const wxString& filename);
};

#endif // PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H