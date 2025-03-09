/**
 * @file SpartanmindView.h
 * @author Raj Ambekar
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H

#include "Spartanmind.h"

/**
 * View class for displaying the Spartanmind game
 */
class SpartanmindView : public wxWindow
{
private:
	/// An object that describes our game
	Spartanmind  mSpartanmind;

	void OnPaint(wxPaintEvent& event);
public:
	/**
	 * Initialize the view
	 * @param parent Parent window
	 */
	void Initialize(wxFrame* parent);

	/**
	 * Load level data from an XML file
	 * @param filename Path to the XML file
	 * @return True if loaded successfully, false otherwise
	 */
	bool LoadFromXML(const wxString& filename);
};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
