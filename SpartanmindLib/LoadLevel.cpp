#include "LoadLevel.h"
#include "Game.h"
#include "Letter.h"
#include "Given.h"
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <iostream>
#include <map>

/**
 * Constructor for LoadLevel
 * @param spartanmind Reference to the Spartanmind game
 * @param game Reference to the Game object
 */
LoadLevel::LoadLevel(Game& game)
    : mGame(game)
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
        std::cout << "Failed to load level file: %s" <<  filename;
        return false;
    }

    wxXmlNode* root = xmlDoc.GetRoot();
    if (root->GetName() != "level") {
        std::cout << "Invalid level file format: %s" << filename;
        return false;
    }

    double width, height, tileWidth, tileHeight;
    root->GetAttribute("width", "0").ToDouble(&width);
    root->GetAttribute("height", "0").ToDouble(&height);
    root->GetAttribute("tilewidth", "48").ToDouble(&tileWidth);
    root->GetAttribute("tileheight", "48").ToDouble(&tileHeight);

    int totalWidth = static_cast<int>(width * tileWidth);
    int totalHeight = static_cast<int>(height * tileHeight);

    // Update the virtual dimensions for the game.
    mGame.SetVirtualDimensions(totalWidth, totalHeight);

    // Store a map of declared items for lookup
    std::map<wxString, wxXmlNode*> declaredItems;

    // Parse <declarations> to build a lookup table
    wxXmlNode* declarationsNode = root->GetChildren();
    while (declarationsNode) {
        if (declarationsNode->GetName() == "declarations") {
            wxXmlNode* child = declarationsNode->GetChildren();
            while (child) {
                wxString id = child->GetAttribute("id", "");
                if (!id.IsEmpty()) {
                    declaredItems[id] = child;  // Store reference for lookup
                }
                child = child->GetNext();
            }
        }
        declarationsNode = declarationsNode->GetNext();
    }

    // Parse <items> for letters and givens
    wxXmlNode* itemsNode = root->GetChildren();
    while (itemsNode) {
        if (itemsNode->GetName() == "items") {
            wxXmlNode* item = itemsNode->GetChildren();
            while (item) {
                if (item->GetName() == "letter" || item->GetName() == "given") {
                    wxString itemId = item->GetAttribute("id", "");
                    if (!itemId.IsEmpty() && declaredItems.find(itemId) != declaredItems.end()) {
                        wxXmlNode* declaration = declaredItems[itemId];

                        wxString itemType = item->GetName();
                        wxString width = declaration->GetAttribute("width", "48");
                        wxString height = declaration->GetAttribute("height", "48");
                        wxString image = declaration->GetAttribute("image", "");
                        wxString value = declaration->GetAttribute("value", "");
                        double col, row;
                        item->GetAttribute("col", "0").ToDouble(&col);
                        item->GetAttribute("row", "0").ToDouble(&row);

                        wxString fullImagePath = "resources/images/" + image;
                        std::wstring fullImagePathw = fullImagePath.ToStdWstring();

                        if (itemType == "letter") {
                            Letter* letter = new Letter(&mGame, fullImagePathw, itemId, width, height,
                                                        fullImagePath, value, width, width);
                            letter->SetLocation(col * tileWidth, row * tileHeight);
                            mGame.AddLetter(letter);
                        } else if (itemType == "given") {
                            Given* given = new Given(&mGame, fullImagePathw, itemId, width, height,
                                                     fullImagePath, value, width, width);
                            given->SetLocation(col * tileWidth, row * tileHeight);
                            mGame.AddGiven(given);
                        }
                    }
                }
                item = item->GetNext();
            }
        }
        itemsNode = itemsNode->GetNext();
    }

    return true;
}
