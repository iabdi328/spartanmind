/**
 * @file SpartanmindView.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "SpartanmindView.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>

/**
 * Initialize the Spartanmind view class.
 * @param parent The parent window for this class
 */
void SpartanmindView::Initialize(wxFrame* parent) {
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &SpartanmindView::OnPaint, this);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanmindView::OnPaint(wxPaintEvent& event) {
    wxAutoBufferedPaintDC dc(this);
    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();
    mSpartanmind.OnDraw(&dc);
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

    // Validate root element
    wxXmlNode* root = xmlDoc.GetRoot();
    if (root->GetName() != "level") {
        wxLogError("Invalid level file format: %s", filename);
        return false;
    }

    // Extract and log level info
    long width, height, tileWidth, tileHeight;
    root->GetAttribute("width", "0").ToLong(&width);
    root->GetAttribute("height", "0").ToLong(&height);
    root->GetAttribute("tilewidth", "48").ToLong(&tileWidth);
    root->GetAttribute("tileheight", "48").ToLong(&tileHeight);

    wxLogMessage("Loaded level %s: %ldx%ld tiles (%ldx%ld pixels per tile)", filename, width, height, tileWidth, tileHeight);

    // Compute the total pixel dimensions for the level
    int totalWidth = static_cast<int>(width * tileWidth);
    int totalHeight = static_cast<int>(height * tileHeight);

    // Resize this view to match the level dimensions.
    // Note: If this view is managed by a sizer, the sizer might override this size.
    SetSize(totalWidth, totalHeight);

    // Optionally log the level content (if relevant)
    wxXmlNode* layerNode = root->GetChildren();
    while (layerNode) {
        wxLogMessage("Layer name: %s", layerNode->GetName());
        layerNode = layerNode->GetNext();
    }

    return true;
}
