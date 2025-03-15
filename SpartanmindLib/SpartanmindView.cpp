/**
 * @file SpartanmindView.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 */

#include "pch.h"
#include "SpartanmindView.h"
#include "Spartanmind.h"
#include "LoadLevel.h"
#include "Given.h"
#include "Letter.h"
#include "Sparty.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>

class Given;

/**
 * Constructor
 * @param parent
 * @param spartanmind
 */
SpartanmindView::SpartanmindView(wxFrame* parent, Spartanmind& spartanmind)
    : wxWindow(parent, wxID_ANY), mSpartanmind(spartanmind)
{
    mGameTimer = new wxTimer(this, 1);
    mLevelLoader = new LoadLevel(mSpartanmind, mGame);

    Bind(wxEVT_TIMER, &SpartanmindView::OnTimer, this);

    mGameTimer->Start(16);

    Initialize(parent);
}

/**
 * Destructor
 */
SpartanmindView::~SpartanmindView()
{
    delete mLevelLoader;
    delete mGameTimer;
}

/**
 * Initialize the Spartanmind view class.
 * @param parent The parent window for this class
 */
void SpartanmindView::Initialize(wxFrame* parent) {
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &SpartanmindView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SpartanmindView::OnLeftDown, this);  // Mouse left-click event
    Bind(wxEVT_KEY_DOWN, &SpartanmindView::OnKeyDown, this);    // Spacebar event
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanmindView::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    std::shared_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));
    if (!gc) return;

    wxRect rect = GetRect();
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());
    if (mSpartanmind.GetPlayer()) {
        mSpartanmind.GetPlayer()->Draw(gc.get());
    }

    int x = 200;
    int y = 300;
    for (const auto& letter : mSpartanmind.GetLetters()) {
        letter->SetLocation(x, y);
        letter->Draw(&dc);
        x += 50;
        if (x == 700)
        {
            y += 50;
            x = 300;
        }
    }
    int givenX = 200;
    int givenY = 100;
    for (const auto& given : mSpartanmind.GetGivens()) {
        given->SetLocation(x, y);
        given->Draw(&dc);
        x += 50;
        if (x == 700)
        {
            y += 50;
            x = 300;
        }
    }
}

/**
 * Defines the timer scoreboard
 * @param event timerEvent
 */
void SpartanmindView::OnTimer(wxTimerEvent& event) {
    mSpartanmind.Update(0.016);
    mGame.UpdateScoreboard(0.016);
    Refresh();
}

/**
 * Mouse Left Click event - moves Sparty to the clicked position
 * @param event
 */
void SpartanmindView::OnLeftDown(wxMouseEvent& event) {
    int x = event.GetX();
    int y = event.GetY();
    // Invert y coordinate because window origin is top-left
    int gameY = GetClientSize().GetHeight() - y;

    mSpartanmind.GetPlayer()->SetTarget(x, y);

    Refresh();
}

/**
 * Key Down event - handles spacebar for headbutt action
 * @param event
 */
void SpartanmindView::OnKeyDown(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_SHIFT) {
        mSpartanmind.GetPlayer()->Headbutt();
    }
    else if (event.GetKeyCode() == WXK_SPACE) {
        mSpartanmind.GetPlayer()->Eat();

    }
    event.Skip();
}

/**
 * Load the level files
 * @param filename file
 * @return
 */
bool SpartanmindView::LoadFromXML(const wxString& filename) {
    bool success = mLevelLoader->LoadFromXML(filename);

    return success;
}