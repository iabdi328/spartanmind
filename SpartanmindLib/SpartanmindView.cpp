/**
 * @file SpartanmindView.cpp
 * @author Raj Ambekar, Ismail Abdi
 */

#include "pch.h"
#include "SpartanmindView.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>


/**
 * Initialize the Spartanmind view class.
 * @param parent The parent window for this class
 */
void SpartanmindView::Initialize(wxFrame* parent) {
    // Use the wxFULL_REPAINT_ON_RESIZE style.
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &SpartanmindView::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &SpartanmindView::OnLeftDown, this);
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
}



void SpartanmindView::OnLeftDown(wxMouseEvent& event) {
    int x = event.GetX();
    int y = event.GetY();
    mGame.OnLeftDown(x, y);
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

    wxLogMessage("Loaded level %s: %ldx%ld tiles (%ldx%ld pixels per tile)",
                 filename, width, height, tileWidth, tileHeight);

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
                        wxLogMessage("Background updated to: %s", fullBgPath);
                    }
                    break;
                }
                child = child->GetNext();
            }
        }
        declarationsNode = declarationsNode->GetNext();
    }

    Refresh();
    return true;
}

