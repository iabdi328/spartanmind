/**
 * @file Game.h
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 *
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <wx/graphics.h>
#include <wx/bitmap.h>
#include <wx/string.h>
#include "Scoreboard.h"
#include "Given.h"
#include "Tray.h"
#include "Container.h"

class Letter;
class Sparty;

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
    std::unique_ptr<wxBitmap> mBackground; ///< Background image for the level.

    // Game components
    Scoreboard mScoreboard;  ///< The scoreboard instance.
    Sparty* mPlayer;         ///< The player character (Sparty)

    // Game elements collections
    std::vector<Letter*> mLetters;     ///< Collection of letters in the game
    std::vector<Given*> mGivens;       ///< Collection of given letters/clues
    std::vector<Tray*> mTray;          ///< Collection of letter trays
    std::vector<Container*> mContainer; ///< Collection of containers

public:
    /// Constructor and Destructor
    Game();
    ~Game();

    /**
     * Initialize the game components
     */
    void Initialize();

    /**
     * Update the Game State
     * @param deltaSeconds The time elapsed since the last frame
     */
    void Update(double deltaSeconds);

    /**
     * This function draws the background image (or a fallback red rectangle if unavailable)
     * based on calculated scale factors and offsets to center the virtual playing area.
     *
     * @param gc Graphics context to draw on.
     * @param width Width of the window.
     * @param height Height of the window.
     */
    void OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    /**
     * Set Virtual Pixels
     * @param virtualWidth Virtual width (e.g., level width in tiles * tile width).
     * @param virtualHeight Virtual height (e.g., level height in tiles * tile height).
     */
    void SetVirtualDimensions(int virtualWidth, int virtualHeight);

    /**
     * Set the background image using a file path.
     * @param imagePath File path to the background image.
     */
    void SetBackground(const wxString& imagePath);

    /**
     * Updates the scoreboard number
     * @param deltaSeconds
     */
    void UpdateScoreboard(double deltaSeconds);

    /**
     * Get the player character
     * @return Pointer to the Sparty object
     */
    Sparty* GetPlayer() { return mPlayer; }

    // Letter management methods
    std::vector<Letter*> GetLetters() { return mLetters; }
    void AddLetter(Letter* letter);
    void ClearLetters();

    // Given management methods
    std::vector<Given*> GetGivens() { return mGivens; }
    void AddGiven(Given* given);
    void ClearGivens();

    // Tray management methods
    std::vector<Tray*> GetTray() { return mTray; }
    void AddTray(Tray* tray);
    void ClearTrays();

    // Container management methods
    std::vector<Container*> GetContainer() { return mContainer; }
    void AddContainer(Container* container);
    void ClearContainers();
};

#endif // GAME_H