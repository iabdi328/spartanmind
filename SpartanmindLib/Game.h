/**
 * @file Game.h
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 *
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <random>
#include <iostream>
#include <wx/graphics.h>
#include <wx/bitmap.h>
#include <wx/string.h>
#include "Scoreboard.h"
#include "Tray.h"
#include "Item.h"
#include "Letter.h"
#include "Container.h"
#include "PopUps.h"

class Player;

/**
 * This class is responsible for drawing the game world using a virtual coordinate system,
 * scaling the view appropriately, handling mouse input, and managing game state.
 */
class Game {
private:
    double mScale;         ///< Scale factor from virtual to screen coordinates.
    double mXOffset;       ///< X offset (screen pixels) to center the playing area.
    double mYOffset;       ///< Y offset (screen pixels) to center the playing area.
    int mVirtualWidth;     ///< Virtual width (e.g., level width in tiles * tile width).
    int mVirtualHeight;    ///< Virtual height (e.g., level height in tiles * tile height).
    int mTileWidth = 0;    ///< Tile width
    int mTileHeight = 0;   ///< Tile height
    int mWidth = 0;        ///< Width
    int mHeight = 0;       ///< Height

    /// Represents the current level of the game.
    int mLevel = 1;

    /// Background image for the level.
    std::unique_ptr<wxBitmap> mBackground;

    /// The scoreboard instance.
    Scoreboard mScoreboard;

    /// player object
    std::shared_ptr<Player> mPlayer;

    /// Pop Up message
    PopUps mPopUps;

    std::vector<std::shared_ptr<Given>> mGivens;

    /// All the items to populate our game
    std::vector<std::shared_ptr<Item>> mItems;

    /// List for the word solution
    std::vector<int> mWord;

    /// List for the current word guessed by user
    std::vector<int> mUserGuess;

    /// random generatorr
    std::mt19937 mRandom;

public:
    /// Constructor and Destructor
    Game();

    void Update(double deltaSeconds);
    void OnDraw(std::shared_ptr<wxGraphicsContext>gc, int width, int height);
    void UpdateScoreboard(double deltaSeconds);
    void SetVirtualDimensions(int virtualWidth, int virtualHeight);
    void Add(std::shared_ptr<Item> item);
    void AddAnswer(int number);
    void Clear();
    void ShowLevelBeginPopup(int levelNumber);
    std::shared_ptr<Item> GetItems(double mX, double mY);
    std::shared_ptr<Item> HitTest(int x, int y);
    void Accept(ItemVisitor *visitor);
    void ItemToTray(std::shared_ptr<Item> item);
    std::mt19937& GetRandom() { return mRandom; }
    bool CellOccupied(double x, double y);
    std::tuple<int,int> Cords2Cell(double x, double y);


    /**
     * Return the pointer of the player
     * @return player smart pointer
     */
    std::shared_ptr<Player> GetPlayer() const { return mPlayer; }

    /**
     * Get the Level of the game
     * @return level
     */
    int GetLevel() const { return mLevel; }

    /**
    * @brief Retrieves the height of a tile in the game.
    * @return The height of a tile.
    */
    int GetTileHeight() const { return mTileHeight; }

    /**
     * @brief Retrieves the width of a tile in the game.
     * @return The width of a tile.
     */
    int GetTileWidth() const { return mTileWidth; }

    /**
     * GetScale
     * @return scale
     */
    double GetScale() const { return mScale; }

    /**
     * Get the offset of x
     * @return x offset
     */
    double GetXOffset() const { return mXOffset; }

    /**
     * @brief Retrieves the current Y offset in the game.
     * @return Y offset value.
     */
    double GetYOffset() const { return mYOffset; }

    /**
     * Get Pixel width
     * @return the pixel width of the game.
     */
    int GetPixelWidth() const { return mWidth*mTileWidth; }

    /**
     * @brief Calculates and retrieves the height of the game in pixels.
     * @return The pixel height of the game.
     */
    int GetPixelHeight() const { return mHeight*mTileHeight; }

    /**
     * Set the background image using a file path.
     * @param file File path to the background image.
     */
    void SetBackground (const wxString &file)
    {
        wxString loc = L"../images/";
        mBackground = std::make_unique<wxBitmap>(loc+file, wxBITMAP_TYPE_ANY);
    }

    /**
     * Set level
     * @param level number of current level).
     */
    void SetLevel(int level) { mLevel = level; }

    /**
     * @brief Sets the width ofgame .
     * @param width New width.
     */
    void SetWidth(int width){ mWidth = width; }

    /**
     * @brief Sets the height of the game world.
     * @param height New height value.
     */
    void SetHeight(int height){ mHeight = height; }

    /**
     * @brief Sets the width of a tile in the game world.
     * @param tileWidth New tile width value.
     */
    void SetTileWidth(int tileWidth) { mTileWidth = tileWidth; }

    /**
     * @brief Sets the height of a tile in the game world.
     * @param tileHeight New tile height value.
     */
    void SetTileHeight(int tileHeight){ mTileHeight = tileHeight; }

    /**
     * @brief set the player character
     * @param player to the player object
     */
    void SetPlayer(std::shared_ptr<Player> player) { mPlayer = player; }


    void ResetScoreboard();

    void FullMessage(std::shared_ptr<wxGraphicsContext> graphics);
    void RemoveTrayItems(std::shared_ptr<Item> item);

    void SubtractTimeFromScoreboard(double seconds);

    void AddContainerLetters(std::shared_ptr<Letter> letter);

    std::vector<int> GetWord() { return mWord; }

    std::vector<int> GetUserGuess()
    {
        return mUserGuess;
    }

    void SetUserGuess(int index, int value)
    {
        mUserGuess[index] = value;
    }

    void ResizeUserGuess(int size)
    {
        mUserGuess.resize(size, -1);
    }

    void ClearWord()
    {
        mWord.clear();
    }

    void ClearGuessedWord()
    {
        mUserGuess.clear();
    }

    std::vector<std::shared_ptr<Given>> GetGivens()
    {
        return mGivens;
    }

    void ClearGivens()
    {
        mGivens.clear();
    }

    void AddGiven(std::shared_ptr<Given> given) { mGivens.push_back(given); }
};

#endif // GAME_H