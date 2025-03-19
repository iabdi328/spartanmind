/**
 * @file LoadLevel.h
 * @author Raj Ambekar
 *
 * Class that loads the game levels
 */

#ifndef PROJECT1_SPARTANMINDLIB_LOADLEVEL_H
#define PROJECT1_SPARTANMINDLIB_LOADLEVEL_H

#include <wx/string.h>
#include "Game.h"

/**
 * Class that loads the game levels
 */
class LoadLevel
{
private:
    Game& mGame;

public:
    /**
     * Constructor
     * @param spartanmind Reference to Spartanmind game object
     * @param game Reference to Game object
     */
    LoadLevel(Game& game);

    /**
     * Load level data from an XML file
     * @param filename Path to the XML file
     * @return True if loaded successfully, false otherwise
     */
    bool LoadFromXML(const wxString& filename);

};

#endif //PROJECT1_SPARTANMINDLIB_LOADLEVEL_H
