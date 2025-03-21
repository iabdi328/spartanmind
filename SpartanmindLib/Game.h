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

    /**
     * Updates the game state.
     * @param deltaSeconds The time elapsed since the last update, in seconds.
     */
    void Update(double deltaSeconds);

    /**
     * Draws the game scene.
     * @param gc A shared pointer to the wxGraphicsContext used for drawing.
     * @param width The width of the drawing area.
     * @param height The height of the drawing area.
     */
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    /**
     * Updates the scoreboard based on the elapsed time.
     * @param deltaSeconds The time elapsed since the last scoreboard update, in seconds.
     */
    void UpdateScoreboard(double deltaSeconds);

    /**
     * Sets the virtual dimensions of the game world.
     * @param virtualWidth The virtual width (e.g., in tiles).
     * @param virtualHeight The virtual height (e.g., in tiles).
     */
    void SetVirtualDimensions(int virtualWidth, int virtualHeight);

    /**
     * Adds an item to the game.
     * @param item A shared pointer to the item to be added.
     */
    void Add(std::shared_ptr<Item> item);

    /**
     * Adds an answer value to the game.
     * @param number The answer number to add.
     */
    void AddAnswer(int number);

    /**
     * Clears the game state, removing all items and resetting relevant variables.
     */
    void Clear();

    /**
     * Displays a popup message at the beginning of a level.
     * @param levelNumber The number of the level that is starting.
     */
    void ShowLevelBeginPopup(int levelNumber);

    /**
     * Retrieves an item at the specified coordinates.
     * @param mX The x-coordinate in the game world.
     * @param mY The y-coordinate in the game world.
     * @return A shared pointer to the item at the specified coordinates, if any.
     */
    std::shared_ptr<Item> GetItems(double mX, double mY);

    /**
     * Performs a hit test to determine if an item exists at the given coordinates.
     * @param x The x-coordinate for the hit test.
     * @param y The y-coordinate for the hit test.
     * @return A shared pointer to the item if found, otherwise nullptr.
     */
    std::shared_ptr<Item> HitTest(int x, int y);

    /**
     * Accepts a visitor to perform operations on game items.
     * @param visitor A pointer to the ItemVisitor object.
     */
    void Accept(ItemVisitor *visitor);

    /**
     * Moves an item to the tray.
     * @param item A shared pointer to the item to move.
     */
    void ItemToTray(std::shared_ptr<Item> item);

    /**
     * Provides access to the random number generator.
     * @return A reference to the random number generator.
     */
    std::mt19937& GetRandom() { return mRandom; }

    /**
     * Checks whether a cell is occupied at the specified coordinates.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return True if the cell is occupied, false otherwise.
     */
    bool CellOccupied(double x, double y);

    /**
     * Converts screen coordinates to cell indices.
     * @param x The x-coordinate.
     * @param y The y-coordinate.
     * @return A tuple containing the cell indices (row, column).
     */
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


        /**
     * Resets the scoreboard to its default state.
     */
    void ResetScoreboard();

    /**
     * Displays the full message on the screen using the specified graphics context.
     * @param graphics A shared pointer to the wxGraphicsContext used for drawing.
     */
    void FullMessage(std::shared_ptr<wxGraphicsContext> graphics);

    /**
     * Removes the tray items associated with the specified item.
     * @param item A shared pointer to the item to remove from the tray.
     */
    void RemoveTrayItems(std::shared_ptr<Item> item);

    /**
     * Subtracts the specified amount of time from the scoreboard.
     * @param seconds The number of seconds to subtract.
     */
    void SubtractTimeFromScoreboard(double seconds);

    /**
     * Adds container letters to the game.
     * @param letter A shared pointer to the letter to add.
     */
    void AddContainerLetters(std::shared_ptr<Letter> letter);

    /**
     * Retrieves the current word as a vector of integers.
     * @return A vector representing the current word.
     */
    std::vector<int> GetWord() { return mWord; }

    /**
     * Retrieves the user's current guess as a vector of integers.
     * @return A vector representing the user's guess.
     */
    std::vector<int> GetUserGuess() { return mUserGuess; }

    /**
     * Sets the user's guess at the specified index.
     * @param index The index in the guess vector to set.
     * @param value The value to set at the specified index.
     */
    void SetUserGuess(int index, int value) { mUserGuess[index] = value; }

    /**
     * Resizes the user's guess vector to the specified size.
     * @param size The new size for the user's guess vector. New elements will be set to -1.
     */
    void ResizeUserGuess(int size) { mUserGuess.resize(size, -1); }

    /**
     * Clears the current word.
     */
    void ClearWord() { mWord.clear(); }

    /**
     * Clears the user's current guess.
     */
    void ClearGuessedWord() { mUserGuess.clear(); }

    /**
     * Retrieves the list of given objects.
     * @return A vector of shared pointers to Given objects.
     */
    std::vector<std::shared_ptr<Given>> GetGivens() { return mGivens; }

    /**
     * Clears the list of given objects.
     */
    void ClearGivens() { mGivens.clear(); }

    /**
     * Adds a given object to the list.
     * @param given A shared pointer to the Given object to add.
     */
    void AddGiven(std::shared_ptr<Given> given) { mGivens.push_back(given); }

};

#endif // GAME_H