/**
 * @file SpartanmindView.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "SpartanmindView.h"
#include <wx/dcbuffer.h>

/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void SpartanmindView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    //SetBackgroundColour(*wxWHITE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &SpartanmindView::OnPaint, this);

}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanmindView::OnPaint(wxPaintEvent& event)
{

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    mSpartanmind.OnDraw(&dc);
}
