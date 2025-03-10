/**
 * @file SpartanmindView.h
 * @author Raj Ambekar
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H

#include "Spartanmind.h"
#include "Game.h"

/**
 * View class for displaying the Spartanmind game
 */
class SpartanmindView : public wxWindow
{
private:
	wxTimer* mGameTimer;  // Timer for periodic updates
	/// An object that describes our game
	Spartanmind&  mSpartanmind;

	Game mGame; // New: a Game object that handles virtual pixels.

	void OnPaint(wxPaintEvent& event);
	void OnLeftDown(wxMouseEvent& event);
	void OnKeyDown(wxKeyEvent& event);

public:
	// Constructor that accepts a pointer to Spartanmind
	SpartanmindView(wxFrame* parent, Spartanmind& spartanmind);
	/**
	 * Initialize the view
	 * @param parent Parent window
	 */
	void Initialize(wxFrame* parent);


	void OnTimer(wxTimerEvent& event);

	/**
	 * Load level data from an XML file
	 * @param filename Path to the XML file
	 * @return True if loaded successfully, false otherwise
	 */
	bool LoadFromXML(const wxString& filename);
};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
