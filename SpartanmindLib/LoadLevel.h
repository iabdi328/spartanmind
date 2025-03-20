/**
 * @file LoadLevel.h
 * @author Raj Ambekar
 *
 * Class that loads the game levels
 */

#ifndef PROJECT1_SPARTANMINDLIB_LOADLEVEL_H
#define PROJECT1_SPARTANMINDLIB_LOADLEVEL_H

#include <wx/string.h>
#include <wx/xml/xml.h>
#include "Game.h"

/**
 * Class that loads the game levels
 */
class LoadLevel
{
private:
    /// Game pointer
    Game* mGame;

public:
    LoadLevel(Game * game);
    /// Default constructor (disabled)
    LoadLevel() = delete;
    /// Copy constructor (disabled)
    LoadLevel(const LoadLevel &) = delete;
    /// Assignment operator
    void operator=(const LoadLevel &) = delete;

    void Load(const wxString &filename);
    void BackgroundNode(wxXmlNode * node);
    void LetterNode(wxXmlNode * node);
    void TrayNode(wxXmlNode *node);
    void PlayerNode(wxXmlNode * node);
    void ContainerNode(wxXmlNode * node);
    void Clear();

};

#endif //PROJECT1_SPARTANMINDLIB_LOADLEVEL_H
