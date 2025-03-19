/**
 * @file Game.h
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 *
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <iostream>
#include <wx/graphics.h>
#include <wx/bitmap.h>
#include <wx/string.h>
#include "Scoreboard.h"
#include "Tray.h"
#include "Item.h"
#include "Letter.h"
#include "Container.h"



class Player;

/**
 * This class is responsible for drawing the game world using a virtual coordinate system,
 * scaling the view appropriately, handling mouse input, and managing game state.
 */
class Game
{
private:
    // Display and scaling properties
    double mScale;         ///< Scale factor from virtual to screen coordinates.
    double mXOffset;       ///< X offset (screen pixels) to center the playing area.
    double mYOffset;       ///< Y offset (screen pixels) to center the playing area.
    int mVirtualWidth;     ///< Virtual width (e.g., level width in tiles * tile width).
    int mVirtualHeight;    ///< Virtual height (e.g., level height in tiles * tile height).
    int mTileWidth = 0;    /// Tile width
    int mTileHeight = 0;   /// Tile height
    int mWidth = 0;        /// Width
    int mHeight = 0;       /// Height


    int mLevel = 1;        /// Represents the current level of the game.

    std::unique_ptr<wxBitmap> mBackground; ///< Background image for the level.

    Scoreboard mScoreboard;  ///< The scoreboard instance.

    std::shared_ptr<Player> mPlayer;     ///player object

    /// All the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;


public:
    /// Constructor and Destructor
    Game();

    std::shared_ptr<Player> GetPlayer() const { return mPlayer; }
    int GetLevel() { return mLevel; }
    /**
    * @brief Retrieves the height of a tile in the game.
    * @return The height of a tile.
    */
    int GetTileHeight() { return mTileHeight;}
    /**
     * @brief Retrieves the width of a tile in the game.
     * @return The width of a tile.
     */
    int GetTileWidth() { return mTileWidth;}
    double GetScale() { return mScale; }
    double GetXOffset() { return mXOffset; }
    /**
     * @brief Retrieves the current Y offset in the game.
     * @return Y offset value.
     */
    double GetYOffset() { return mYOffset; }
    int GetPixelWidth() {return mWidth*mTileWidth;}

    /**
     * @brief Calculates and retrieves the height of the game in pixels.
     * @return The pixel height of the game.
     */
    int GetPixelHeight() { return  mHeight*mTileHeight;}

    /**
     * Set the background image using a file path.
     * @param imagePath File path to the background image.
     */
    void SetBackground (wxString file)
    {
        wxString loc = L"../images/";
        mBackground = std::make_unique<wxBitmap>(loc+file, wxBITMAP_TYPE_ANY);
    }
    /**
     * Set Virtual Pixels
     * @param virtualWidth Virtual width (e.g., level width in tiles * tile width).
     * @param virtualHeight Virtual height (e.g., level height in tiles * tile height).
     */
    void SetVirtualDimensions(int virtualWidth, int virtualHeight);
    /**
     * Set level
     * @param level number of current level).
     */
    void SetLevel(int level) { mLevel = level; }
    /**
     * @brief Sets the width ofgame .
     * @param width New width.
     */
    void SetWidth(int width){mWidth = width;}
    /**
     * @brief Sets the height of the game world.
     * @param height New height value.
     */
    void SetHeight(int height){mHeight = height;}
    /**
     * @brief Sets the width of a tile in the game world.
     * @param tileWidth New tile width value.
     */
    void SetTileWidth(int tileWidth){
        std::cout << "@DEBUG SetTileWidth called tielWidth: " << tileWidth << std::endl;

        mTileWidth = tileWidth;}
    /**
     * @brief Sets the height of a tile in the game world.
     * @param tileHeight New tile height value.
     */
    void SetTileHeight(int tileHeight){
        std::cout << "@DEBUG SetTileHeigth called TileHeight: " << tileHeight << std::endl;
        mTileHeight = tileHeight;}
    /**
     * @brief set the player character
     * @param pointer to the player object
     */
    void SetPlayer(std::shared_ptr<Player> player) {
        mPlayer = player;
    }

    // Game member functions

    /**
     * Update the Game State
     * @param deltaSeconds The time elapsed since the last frame
     */
    void Update(double deltaSeconds);
    /**
     * draws the background image
     *
     * @param gc Graphics context to draw on.
     * @param width Width  window.
     * @param height Height of window.
     */
    void OnDraw(std::shared_ptr<wxGraphicsContext>gc, int width, int height);
    /**
    * Updates the scoreboard number
    * @param deltaSeconds
    */
    void UpdateScoreboard(double deltaSeconds);
    /**
    * Add items to the game
    * @param item collection of items in gamee
    */
    void Add(std::shared_ptr<Item> item);
    /**
    * cleer the game items
    */
    void Clear();
};

#endif // GAME_H