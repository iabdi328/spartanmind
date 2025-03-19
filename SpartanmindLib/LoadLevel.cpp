/**
 * @file LoadLevel.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "LoadLevel.h"
#include "Letter.h"
#include "Given.h"
#include "Tray.h"
#include "Container.h"
#include <wx/xml/xml.h>
#include <wx/wfstream.h>

/**
 * Constructor for LevelLoader
 * @param spartanmind Reference to the Spartanmind game
 * @param game Reference to the Game object
 */
LoadLevel::LoadLevel(Spartanmind& spartanmind, Game& game)
    : mSpartanmind(spartanmind), mGame(game)
{
}

/**
 * Load level data from an XML file.
 * @param filename Path to the XML file.
 * @return True if loaded successfully, false otherwise.
 */
bool LoadLevel::LoadFromXML(const wxString& filename)
{
    std::cout << "Loading from XML" << std::endl;
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

    double width, height, tileWidth, tileHeight;
    root->GetAttribute("width", "0").ToDouble(&width);
    root->GetAttribute("height", "0").ToDouble(&height);
    root->GetAttribute("tilewidth", "48").ToDouble(&tileWidth);
    root->GetAttribute("tileheight", "48").ToDouble(&tileHeight);

    int totalWidth = (int)(width * tileWidth);
    int totalHeight = (int)(height * tileHeight);

    // Update the virtual dimensions for the game.
    mGame.SetVirtualDimensions(totalWidth, totalHeight);

    // Look for the background element in the <declarations> node.
   wxXmlNode* itemsNode = root->GetChildren();
while (itemsNode) {
    if (itemsNode->GetName() == "items") {
        wxXmlNode* item = itemsNode->GetChildren();
        while (item) {
            if (item->GetName() == "letter" || item->GetName() == "given") {
                wxString id = item->GetAttribute("id", "");
                wxString col = item->GetAttribute("col", "");
                wxString row = item->GetAttribute("row", "");

                // Find matching letter/given attributes from declarations
                wxXmlNode* declarationsNode = root->GetChildren();
                while (declarationsNode) {
                    if (declarationsNode->GetName() == "items") {
                        wxXmlNode* declChild = declarationsNode->GetChildren();
                        while (declChild) {
                            if (declChild->GetName() == item->GetName() && declChild->GetAttribute("id", "") == id) {
                                wxString width = declChild->GetAttribute("width", "");
                                wxString height = declChild->GetAttribute("height", "");
                                wxString image = declChild->GetAttribute("image", "");
                                wxString value = declChild->GetAttribute("value", "");

                                if (!image.IsEmpty()) {
                                    wxString fullPath = "resources/images/" + image;
                                    std::wstring fullPathw = fullPath.ToStdWstring();

                                    if (item->GetName() == "letter") {
                                        Letter* letter = new Letter(&mGame, fullPathw, id, width, height, fullPath, value, col, row);
                                        // mGame.AddLetter(letter);
                                    } else if (item->GetName() == "given") {
                                        Given* given = new Given(&mGame, fullPathw, id, width, height, fullPath, value, col, row);
                                        // mGame.AddGiven(given);
                                    }
                                }
                            }
                            declChild = declChild->GetNext();
                        }
                    }
                    declarationsNode = declarationsNode->GetNext();
                }
            }
            item = item->GetNext();
        }
    }
    itemsNode = itemsNode->GetNext();
}


    return true;
}

