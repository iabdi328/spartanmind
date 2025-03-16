/**
 * @file SpartanmindView.cpp
 */

#include "pch.h"
#include "SpartanmindView.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>
#include "Given.h"
#include "Letter.h"
#include "Sparty.h"

/**
 * Constructor. Creates the wxWindow and starts the game timer.
 * @param parent The parent window.
 * @param spartanmind Reference to the Spartanmind game logic.
 */
SpartanmindView::SpartanmindView(wxWindow* parent, Spartanmind& spartanmind)
    : wxWindow(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
      mSpartanmind(&spartanmind)
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
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());

    // 2. Draw Sparty (the player character) if valid
    if (mSpartanmind && mSpartanmind->GetPlayer())
    {
        mSpartanmind->GetPlayer()->Draw(gc.get());
    }

    // 3. Draw all letters stored in Spartanmind
    int x = 200;
    int y = 300;
    for (const auto& letter : mSpartanmind->GetLetters())
    {
        letter->SetLocation(x, y);
        letter->Draw(&dc);
        x += 50;
        if (x == 700)
        {
            y += 50;
            x = 300;
        }
    }

    // 4. Draw all givens
    x = 200;
    y = 100;
    for (const auto& given : mSpartanmind->GetGivens())
    {
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
 * Timer event, updates the game logic and scoreboard.
 * @param event Timer event
 */
void SpartanmindView::OnTimer(wxTimerEvent& event)
{
    if (!mSpartanmind) return;

    // Get elapsed time in milliseconds since the stopwatch was started.
    long deltaMs = mStopWatch.Time();
    // Restart the stopwatch for the next interval.
    mStopWatch.Start();
    double deltaSeconds = deltaMs / 1000.0;

    // Update game logic and scoreboard using the actual elapsed time.
    mSpartanmind->Update(deltaSeconds);
    mGame.UpdateScoreboard(deltaSeconds);

    Refresh();
}


/**
 * Mouse left-click event - moves Sparty to the clicked position.
 * @param event Mouse event
 */
void SpartanmindView::OnLeftDown(wxMouseEvent& event)
{
    if (!mSpartanmind) return;

    int x = event.GetX();
    int y = event.GetY();
    // Invert y coordinate because window origin is top-left
    int gameY = GetClientSize().GetHeight() - y;

    // Update Sparty's target
    if (mSpartanmind->GetPlayer())
    {
        mSpartanmind->GetPlayer()->SetTarget(x, y);
    }
    Refresh();
}

/**
 * Key down event - handles SHIFT or SPACE keys for actions.
 * @param event Key event
 */
void SpartanmindView::OnKeyDown(wxKeyEvent& event)
{
    if (!mSpartanmind) return;

    auto player = mSpartanmind->GetPlayer();
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
    if (!mSpartanmind) return false;

    wxXmlDocument xmlDoc;
    wxFileInputStream inputStream(filename);
    if (!inputStream.IsOk() || !xmlDoc.Load(inputStream))
    {
        wxLogError("Failed to load level file: %s", filename);
        return false;
    }

    wxXmlNode* root = xmlDoc.GetRoot();
    if (!root || root->GetName() != "level")
    {
        wxLogError("Invalid level file format: %s", filename);
        return false;
    }

    // Grab width/height from XML
    double width, height, tileWidth, tileHeight;
    root->GetAttribute("width", "0").ToDouble(&width);
    root->GetAttribute("height", "0").ToDouble(&height);
    root->GetAttribute("tilewidth", "48").ToDouble(&tileWidth);
    root->GetAttribute("tileheight", "48").ToDouble(&tileHeight);

    int totalWidth = static_cast<int>(width * tileWidth);
    int totalHeight = static_cast<int>(height * tileHeight);

    SetSize(totalWidth, totalHeight);

    // Update the virtual dimensions in our Game object
    mGame.SetVirtualDimensions(totalWidth, totalHeight);

    // Parse <declarations> to set background, letters, givens, etc.
    wxXmlNode* declarationsNode = root->GetChildren();
    while (declarationsNode)
    {
        if (declarationsNode->GetName() == "declarations")
        {
            wxXmlNode* child = declarationsNode->GetChildren();
            while (child)
            {
                if (child->GetName() == "background")
                {
                    wxString bgImage = child->GetAttribute("image", "");
                    if (!bgImage.IsEmpty())
                    {
                        wxString fullBgPath = "resources/images/" + bgImage;
                        mSpartanmind->SetBackground(fullBgPath);
                        mGame.SetBackground(fullBgPath);
                    }
                }
                else if (child->GetName() == "letter")
                {
                    wxString letterId = child->GetAttribute("id", "");
                    wxString letterWidth = child->GetAttribute("width", "");
                    wxString letterHeight = child->GetAttribute("height", "");
                    wxString letterImage = child->GetAttribute("image", "");
                    wxString letterValue = child->GetAttribute("value", "");
                    if (!letterImage.IsEmpty())
                    {
                        wxString fullLetterPath = "resources/images/" + letterImage;
                        std::wstring fullLetterPathw = fullLetterPath.ToStdWstring();
                        Letter* letter = new Letter(mSpartanmind, fullLetterPathw, letterId,
                                                    letterWidth, letterHeight, fullLetterPath,
                                                    letterValue, letterWidth, letterWidth);
                        mSpartanmind->AddLetter(letter);
                    }
                }
                else if (child->GetName() == "given")
                {
                    wxString letterId = child->GetAttribute("id", "");
                    wxString letterWidth = child->GetAttribute("width", "");
                    wxString letterHeight = child->GetAttribute("height", "");
                    wxString letterImage = child->GetAttribute("image", "");
                    wxString letterValue = child->GetAttribute("value", "");
                    if (!letterImage.IsEmpty())
                    {
                        wxString fullLetterPath = "resources/images/" + letterImage;
                        std::wstring fullLetterPathw = fullLetterPath.ToStdWstring();
                        Given* given = new Given(mSpartanmind, fullLetterPathw, letterId,
                                                 letterWidth, letterHeight, fullLetterPath,
                                                 letterValue, letterWidth, letterWidth);
                        mSpartanmind->AddGiven(given);
                    }
                }
                child = child->GetNext();
            }
        }
        declarationsNode = declarationsNode->GetNext();
    }

    Refresh();
    return true;
}