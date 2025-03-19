/**
 * @file SpartanmindView.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 */

#include "pch.h"
#include "SpartanmindView.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>
#include <map>
#include "Given.h"
#include "Letter.h"
#include "Sparty.h"
#include "Tray.h"
#include "LoadLevel.h"  // Include the LoadLevel class

/**
 * Constructor. Creates the wxWindow and starts the game timer.
 * @param parent The parent window.
 * @param spartanmind Reference to the Spartanmind game logic.
 */
SpartanmindView::SpartanmindView(wxWindow* parent, Game& game)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
      mGame(&game)
{
    // Set the background style for smooth painting
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind our event handlers
    Bind(wxEVT_PAINT, &SpartanmindView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SpartanmindView::OnLeftDown, this);
    Bind(wxEVT_KEY_DOWN, &SpartanmindView::OnKeyDown, this);

    // Create & start the timer for ~60 FPS
    mGameTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, &SpartanmindView::OnTimer, this);
    mGameTimer->Start(16);
}

/**
 * Destructor. Stop the timer and clean up.
 */
SpartanmindView::~SpartanmindView()
{
    if (mGameTimer)
    {
        mGameTimer->Stop();
        delete mGameTimer;
        mGameTimer = nullptr;
    }
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanmindView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    std::shared_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));
    if (!gc) return;

    wxRect rect = GetRect();
    // 1. Draw the game world (background, scoreboard, etc.)
    mGame->OnDraw(gc, rect.GetWidth(), rect.GetHeight());

    // 2. Draw Sparty (the player character) if valid
    if (mGame && mGame->GetPlayer())
    {
        mGame->GetPlayer()->Draw(gc.get());
    }

    // 3. Draw all letters stored in Spartanmind
    for (const auto& letter : mGame->GetLetters())
    {
        letter->Draw(&dc);
    }

    // 4. Draw all givens
    for (const auto& given : mGame->GetGivens())
    {
        given->Draw(&dc);
    }
    int x = 800;
    int y = 144;
    for (const auto& tray : mGame->GetTray())
    {
        tray->SetLocation(x, y);
        tray->Draw(&dc);
    }
}

/**
 * Timer event, updates the game logic and scoreboard.
 * @param event Timer event
 */
void SpartanmindView::OnTimer(wxTimerEvent& event)
{
    if (!mGame) return;

    // Get elapsed time in milliseconds since the stopwatch was started.
    long deltaMs = mStopWatch.Time();
    // Restart the stopwatch for the next interval.
    mStopWatch.Start();
    double deltaSeconds = deltaMs / 1000.0;

    // Update game logic and scoreboard using the actual elapsed time.
    mGame->Update(deltaSeconds);
    mGame->UpdateScoreboard(deltaSeconds);

    Refresh();
}


/**
 * Mouse left-click event - moves Sparty to the clicked position.
 * @param event Mouse event
 */
void SpartanmindView::OnLeftDown(wxMouseEvent& event)
{
    if (!mGame) return;

    int x = event.GetX();
    int y = event.GetY();
    // Invert y coordinate because window origin is top-left
    int gameY = GetClientSize().GetHeight() - y;

    // Update Sparty's target
    if (mGame->GetPlayer())
    {
        mGame->GetPlayer()->SetTarget(x, y);
    }
    Refresh();
}

/**
 * Key down event - handles SHIFT or SPACE keys for actions.
 * @param event Key event
 */
void SpartanmindView::OnKeyDown(wxKeyEvent& event)
{
    if (!mGame) return;

    auto player = mGame->GetPlayer();
    if (!player) return;

    if (event.GetKeyCode() == WXK_SHIFT)
    {
        player->Headbutt();
    }
    else if (event.GetKeyCode() == WXK_SPACE)
    {
        player->Eat();
    }

    event.Skip(); // Let other key events process
}

/**
 * Load level data from an XML file.
 * @param filename Path to the XML file.
 * @return True if loaded successfully, false otherwise.
 */
bool SpartanmindView::LoadFromXML(const wxString& filename)
{
    if (!mGame) return false;

    // Use the LoadLevel class to load the level
    LoadLevel loadLevel(*mGame);
    loadLevel.LoadFromXML(filename);
    return true;
}
