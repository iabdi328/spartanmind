/**
* @file SpartanmindView.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 */


#include "pch.h"
#include "ids.h"
#include "SpartanmindView.h"
#include "Player.h"
#include "LoadLevel.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>
#include <memory>
#include "TrayVisitor.h"


using namespace std;

/**
 * Initialize the Spartanmind view class.
 * @param parent The parent window for this class
 */
void SpartanmindView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    // Set the background style for smooth painting
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind our event handlers
    Bind(wxEVT_PAINT, &SpartanmindView::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &SpartanmindView::OnKeyDown, this);
    Bind(wxEVT_LEFT_DOWN, &SpartanmindView::OnMouseClick, this);

    // Bind functions from MainFrame
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanmindView::OnLevelZero, this,
                 IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanmindView::OnLevelOne, this,
                 IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,  &SpartanmindView::OnLevelTwo, this,
                 IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,  &SpartanmindView::OnLevelThree, this,
                 IDM_LEVEL3);

    const wxString filename = L"../levels/level1.xml";

    LoadLevel load(&mGame);
    load.Load(filename);
    mGame.ShowLevelBeginPopup(mGame.GetLevel());


    // Create & start the timer for ~60 FPS
    mGameTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, &SpartanmindView::OnTimer, this);
    mGameTimer->Start(16);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanmindView::OnPaint(wxPaintEvent& event)
{
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    std::shared_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));
    if (!gc) return;

    wxRect rect = GetRect();
    // 1. Draw the game world (background, scoreboard, etc.)
    mGame.Update(elapsed);
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

    Refresh(false);

}

/**
 * Timer event, updates the game logic and scoreboard.
 * @param event Timer event
 */
void SpartanmindView::OnTimer(wxTimerEvent& event)
{
//    if (!mGame) return;

    // Get elapsed time in milliseconds since the stopwatch was started.
    long deltaMs = mStopWatch.Time();
    // Restart the stopwatch for the next interval.
    mStopWatch.Start();
    double deltaSeconds = deltaMs / 2000.0;

    // Update game logic and scoreboard using the actual elapsed time.
    mGame.Update(deltaSeconds);
    mGame.UpdateScoreboard(deltaSeconds);

    // Move Sparty
    std::shared_ptr<Player> player(mGame.GetPlayer());

    if (player != nullptr)
    {
        player->Update(deltaSeconds);
    }

    Refresh();
}

/**
 * Handles the mouse single click event
 * @param event mouse click
 */
void SpartanmindView::OnMouseClick(wxMouseEvent& event)
{

    // Get the clicked screen coordinates
    wxPoint pos = event.GetPosition();

    // Get player
    std::shared_ptr<Player> player(mGame.GetPlayer());
    if(event.GetX() - 60 > mGame.GetXOffset() && event.GetX() < mGame.GetXOffset()
        + mGame.GetPixelWidth() * mGame.GetScale())
    {
        if(event.GetY() - 10 > mGame.GetYOffset() && event.GetY() < mGame
            .GetYOffset() + mGame.GetPixelHeight() * mGame.GetScale())
        {
            if(player != nullptr)
            {
                player->SetLocation(pos.x, pos.y);
            }
        }

    }
}

/**
 * Key down event - handles SHIFT or SPACE keys for actions.
 * @param event Key event
 */
void SpartanmindView::OnKeyDown(wxKeyEvent& event)
{
//    if (!mGame) return;

    auto player = mGame.GetPlayer();
    if (!player) return;

    if (event.GetKeyCode() == WXK_SHIFT)
    {
        player->Headbutt();
    }
    else if (event.GetKeyCode() == WXK_SPACE)
    {
        player->Eat();
        mGrabbedItem = mGame.HitTest((player->GetX()+player->GetWidth()),
                                     (player->GetY()+player->GetHeight()));
        if(mGrabbedItem != nullptr)
        {
            TrayVisitor visitor2;
            TrayVisitor visitor;
            mGame.Accept(&visitor2);
            mGrabbedItem->Accept(&visitor);
            bool isLetter = visitor.IsFound();
            if(mGrabbedItem != nullptr && isLetter && !visitor2.GetTray()
                ->IsFull())
            {
                mGame.ItemToTray(mGrabbedItem);
            }
        }
    }

    event.Skip(); // Let other key events process
}

/**
 * Event handler for selecting Level Zero.
 * Loads the first level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelZero(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level0.xml";
    NewLevel(filename, 0);

}


/**
 * Event handler for selecting Level One.
 * Loads the first level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelOne(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level1.xml";
    NewLevel(filename, 1);
}

/**
 * Event handler for selecting Level Two.
 * Loads the second level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelTwo(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level2.xml";
    NewLevel(filename, 2);
}

/**
 * Event handler for selecting Level Three.
 * Loads the third level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelThree(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level3.xml";
    NewLevel(filename, 3);

}

/**
 * Loads in new level
 * @param filename level xml file
 * @param levelNumber number of level
 */
void SpartanmindView::NewLevel(const wxString& filename, int levelNumber)
{
    mGame.ResetScoreboard();
    mStopWatch.Start();
    mTime = 0;

    mGame.Clear();
    mGameIsActive = false;
    mNewLevel = true;

    mGame.SetLevel(levelNumber);

    LoadLevel area(&mGame);
    area.Load(filename);

    mGame.ShowLevelBeginPopup(levelNumber);
}

/**
 * Loads in the next level on game completion
 */
void SpartanmindView::LoadNextLevel()
{
    // current level number
    int currLevel = mGame.GetLevel();

    // next level number
    int nextLevel = currLevel + 1;

    // Load the new level directly without using events
    wxString filename;
    switch (nextLevel)
    {
        case 1:
            filename = L"../levels/level1.xml";
            NewLevel(filename, 1);
            break;
        case 2:
            filename = L"../levels/level2.xml";
            NewLevel(filename, 2);
            break;
        case 3:
            filename = L"../levels/level3.xml";
            NewLevel(filename, 3);
            break;
        default:
            break;
    }

}