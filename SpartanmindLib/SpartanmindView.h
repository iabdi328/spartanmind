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
 * Details the Window
 */
class SpartanmindView : public wxWindow
{
private:
    /// An object that describes our game
    Spartanmind  mSpartanmind;

    void OnPaint(wxPaintEvent& event);
public:
    void Initialize(wxFrame* parent);


};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMINDVIEW_H
