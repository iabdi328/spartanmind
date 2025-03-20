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

//class SpartanmindView;
/**
 * The top-level (main) frame of the application
 */
class MainFrame : public wxFrame
{
private:
	std::shared_ptr<Game> mGame;
	SpartanmindView* mSpartanmindView;
public:
	void Initialize();
	void OnExit(wxCommandEvent& event);
	void OnAbout(wxCommandEvent& event);
	void OnSelectLevel1(wxCommandEvent &event);
	void OnSelectLevel2(wxCommandEvent &event);
	void OnSelectLevel3(wxCommandEvent &event);
};

#endif //PROJECT1_SPARTANMINDLIB_MAINFRAME_H