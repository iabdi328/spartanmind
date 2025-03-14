/**
 * @file SpartanmindView.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 */

#include "pch.h"
#include "SpartanmindView.h"
#include "Spartanmind.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>

#include "Letter.h"
#include "Sparty.h"

// SpartanmindView constructor updated to accept a reference to Spartanmind
SpartanmindView::SpartanmindView(wxFrame* parent, Spartanmind& spartanmind)
    : wxWindow(parent, wxID_ANY), mSpartanmind(spartanmind)  // Initialize mSpartanmind with a reference
{
    mGameTimer = new wxTimer(this, 1); // Create timer

    Bind(wxEVT_TIMER, &SpartanmindView::OnTimer, this); // Bind timer event

    mGameTimer->Start(16);

    Initialize(parent);
}

void SpartanmindView::OnTimer(wxTimerEvent& event) {
    mSpartanmind.Update(0.016);  // Update the game with 16ms, ~60 FPS

    // Update the scoreboard (0.016 seconds elapsed).
    mGame.UpdateScoreboard(0.016);


    Refresh();  // Trigger a redraw of the screen
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
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());  // Draw the game world
    // 2. Draw Sparty (the player character) on top of the background
    if (mSpartanmind.GetPlayer()) {
        mSpartanmind.GetPlayer()->Draw(gc.get());  // Draw Sparty using the graphics context
    }

    // Draw all letters stored in Spartanmind
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
}

/**
 * Mouse Left Click event - moves Sparty to the clicked position
 */
void SpartanmindView::OnLeftDown(wxMouseEvent& event) {
    int x = event.GetX();
    int y = event.GetY();

    // Update Sparty's target position based on mouse click
    mSpartanmind.GetPlayer()->SetTarget(x, y);  // Set the new target for Sparty

    // We don't call Update immediately; instead, it will be called during the game loop
    Refresh();  // Refresh the view to update Sparty's position
}

/**
 * Key Down event - handles spacebar for headbutt action
 */
void SpartanmindView::OnKeyDown(wxKeyEvent& event) {
    if (event.GetKeyCode() == WXK_SHIFT) {  // If shift is pressed
        mSpartanmind.GetPlayer()->Headbutt();  // Perform the headbutt action
    }
    else if (event.GetKeyCode() == WXK_SPACE) {
        mSpartanmind.GetPlayer()->Eat();

    }
    event.Skip();  // Continue processing other key events
}

/**
 * Load level data from an XML file.
 * @param filename Path to the XML file.
 * @return True if loaded successfully, false otherwise.
 */
bool SpartanmindView::LoadFromXML(const wxString& filename) {
    wxXmlDocument xmlDoc;
    wxFileInputStream inputStream(filename);

    if (!inputStream.IsOk() || !xmlDoc.Load(inputStream)) {
        wxLogError("Failed to load level file: %s", filename);
        return false;
    }

    wxXmlNode* root = xmlDoc.GetRoot();
    if (root->GetName() != "level") {
        wxLogError("Invalid level file format: %s", filename);
        return false;
    }

    long width, height, tileWidth, tileHeight;
    root->GetAttribute("width", "0").ToLong(&width);
    root->GetAttribute("height", "0").ToLong(&height);
    root->GetAttribute("tilewidth", "48").ToLong(&tileWidth);
    root->GetAttribute("tileheight", "48").ToLong(&tileHeight);

    int totalWidth = static_cast<int>(width * tileWidth);
    int totalHeight = static_cast<int>(height * tileHeight);

    SetSize(totalWidth, totalHeight);

    // Update the virtual dimensions for the game.
    mGame.SetVirtualDimensions(totalWidth, totalHeight);

    // Look for the background element in the <declarations> node.
    wxXmlNode* declarationsNode = root->GetChildren();
    while (declarationsNode) {
        if (declarationsNode->GetName() == "declarations") {
            wxXmlNode* child = declarationsNode->GetChildren();
            while (child) {
                if (child->GetName() == "background") {
                    wxString bgImage = child->GetAttribute("image", "");
                    if (!bgImage.IsEmpty()) {
                        wxString fullBgPath = "resources/images/" + bgImage;
                        mSpartanmind.SetBackground(fullBgPath);  // Update Spartanmind's background.
                        mGame.SetBackground(fullBgPath);           // Also update the Game's background.
                    }
                    break;
                } else if (child->GetName() == "letter")
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
                        Letter* letter = new Letter(&mSpartanmind, fullLetterPathw, letterId, letterWidth, letterHeight, fullLetterPath, letterValue, letterWidth, letterWidth);
                        mSpartanmind.AddLetter(letter);
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
