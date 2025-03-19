/**
 * @file LoadLevel.h
 * @author Raj Ambekar
 *
 * Class that loads the game levels
 */

#ifndef PROJECT1_SPARTANMINDLIB_LOADLEVEL_H
#define PROJECT1_SPARTANMINDLIB_LOADLEVEL_H


#include "Game.h"
#include "Declaration.h"
#include "Item.h"
#include <wx/string.h>

/**
 * Class that loads the game levels
 */
class LoadLevel
{
private:




    Game* mGame = nullptr;

    int mWidth = 0;
    int mHeight = 0;
    int mTileWidth = 0;
    int mTileHeight = 0;

    std::vector<std::shared_ptr<Declaration>> mDeclarations;

    int mWordCol = 0;
    int mWordRow = 0;
    int mWordLength = 0;
    std::vector<int> mWord;

    std::vector<std::shared_ptr<Item>> mItems;

public:
    /**
     * Constructor
     * @param spartanmind Reference to Spartanmind game object
     * @param game Reference to Game object
     */
    LoadLevel();

    /**
     * Load level data from an XML file
     * @param filename Path to the XML file
     * @return True if loaded successfully, false otherwise
     */
     void LoadFromXML(const wxString& filename);
     void LoadXmlDeclaration(wxXmlNode* node);
     void LoadXmlItem(wxXmlNode* node);

     void OnDraw(std::shared_ptr<wxGraphicsContext> graphics);

     int GetWidth() const { return mWidth; }
     int GetHeight() const { return mHeight; }
     int GetTileWidth() const { return mTileWidth; }
     int GetTileHeight() const { return mTileHeight; }


};

#endif //PROJECT1_SPARTANMINDLIB_LOADLEVEL_H
