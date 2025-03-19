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

    mGame.SetVirtualDimensions(totalWidth, totalHeight);

    std::map<wxString, wxXmlNode*> declaredItems;

    wxXmlNode* declarationsNode = root->GetChildren();
    while (declarationsNode) {
        if (declarationsNode->GetName() == "declarations") {
            wxXmlNode* child = declarationsNode->GetChildren();
            while (child) {
                wxString id = child->GetAttribute("id", "");
                if (!id.IsEmpty()) {
                    declaredItems[id] = child;
                    if (child->GetName() == "background") {
                        wxString image = child->GetAttribute("image", "");
                        if (!image.IsEmpty()) {
                            wxString fullImagePath = "resources/images/" + image;
                            mGame.SetBackground(fullImagePath);
                        }
                    }
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
                            // Compute the correct position inside the tray
                            int trayStartX = 0;
                            int trayStartY = 0;
                            double trayX = trayStartX + col * tileWidth + ((tileWidth - 48) / 2);
                            double trayY = trayStartY + row * tileHeight + (tileHeight - 48) / 2;

                            given->SetLocation(trayX, trayY);

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
