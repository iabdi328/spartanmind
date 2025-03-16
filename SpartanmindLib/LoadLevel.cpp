/**
 * @file LoadLevel.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "LoadLevel.h"
#include "Letter.h"
#include "Given.h"
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
                child = child->GetNext();
            }
        }
        declarationsNode = declarationsNode->GetNext();
    }

    return true;
}

