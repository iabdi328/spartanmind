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
                        mGame.SetBackground(fullBgPath);         // Also update the Game's background.
                    }
                } else if (child->GetName() == "letter") {
                    wxString letterId = child->GetAttribute("id", "");
                    wxString letterWidth = child->GetAttribute("width", "");
                    wxString letterHeight = child->GetAttribute("height", "");
                    wxString letterImage = child->GetAttribute("image", "");
                    wxString letterValue = child->GetAttribute("value", "");
                    if (!letterImage.IsEmpty()) {
                        wxString fullLetterPath = "resources/images/" + letterImage;
                        std::wstring fullLetterPathw = fullLetterPath.ToStdWstring();
                        Letter* letter = new Letter(&mSpartanmind, fullLetterPathw, letterId, letterWidth,
                                                    letterHeight, fullLetterPath, letterValue, letterWidth, letterWidth);
                        mSpartanmind.AddLetter(letter);
                    }
                } else if (child->GetName() == "given") {
                    wxString letterId = child->GetAttribute("id", "");
                    wxString letterWidth = child->GetAttribute("width", "");
                    wxString letterHeight = child->GetAttribute("height", "");
                    wxString letterImage = child->GetAttribute("image", "");
                    wxString letterValue = child->GetAttribute("value", "");
                    if (!letterImage.IsEmpty()) {
                        wxString fullLetterPath = "resources/images/" + letterImage;
                        std::wstring fullLetterPathw = fullLetterPath.ToStdWstring();
                        Given* given = new Given(&mSpartanmind, fullLetterPathw, letterId, letterWidth,
                                                 letterHeight, fullLetterPath, letterValue, letterWidth, letterWidth);
                        mSpartanmind.AddGiven(given);
                    }
                }
                else if (child->GetName() == "tray") {
                    wxString trayId = child->GetAttribute("id", "");
                    wxString trayWidth = child->GetAttribute("width", "");
                    wxString trayHeight = child->GetAttribute("height", "");
                    wxString trayImage = child->GetAttribute("image", "");
                    wxString trayCapacity = child->GetAttribute("capacity", "");
                    if (!trayImage.IsEmpty()) {
                        wxString fullTrayPath = "resources/images/" + trayImage;
                        std::wstring fullTrayPathw = fullTrayPath.ToStdWstring();
                        Tray* tray = new Tray(&mSpartanmind, fullTrayPathw, trayId, trayWidth,
                                                 trayHeight, fullTrayPath, trayCapacity, trayWidth, trayWidth);
                        mSpartanmind.AddTray(tray);
                    }
                }
                else if (child->GetName() == "container")
                {
                    wxString containerId = child->GetAttribute("id", "");
                    wxString containerWidth = child->GetAttribute("width", "");
                    wxString containerHeight = child->GetAttribute("height", "");
                    wxString containerImage = child->GetAttribute("image", "");
                    wxString containerValue = child->GetAttribute("capacity", "");
                    if(!containerImage.IsEmpty())
                    {
                        wxString fullcontainerPath = "resources/images/" + containerImage;
                        std::wstring fullcontainerPathw = fullcontainerPath.ToStdWstring();
                        Container *container = new Container(&mSpartanmind, fullcontainerPathw, containerId, containerWidth,
                                                             containerHeight, fullcontainerPath, containerValue, containerWidth, containerWidth);
                        mSpartanmind.AddContainer(container);
                    }
                }
                child = child->GetNext();
            }
        }
        declarationsNode = declarationsNode->GetNext();
    }

    return true;
}

