/**
 * @file Game.h
 * @author Ismail Abdi
 *
 */

#ifndef GAME_H
#define GAME_H

#include <memory>
#include <wx/graphics.h>
#include <wx/bitmap.h>
#include <wx/string.h>
#include "Scoreboard.h"

/**
 * This class is responsible for drawing the game world using a virtual coordinate system,
 * scaling the view appropriately, and handling mouse input.
 */
class Game
{
private:
    double mScale;         ///< Scale factor from virtual to screen coordinates.
    double mXOffset;       ///< X offset (screen pixels) to center the playing area.
    double mYOffset;       ///< Y offset (screen pixels) to center the playing area.
    int mVirtualWidth;     ///< Virtual width (e.g., level width in tiles * tile width).
    int mVirtualHeight;    ///< Virtual height (e.g., level height in tiles * tile height).
    std::unique_ptr<wxBitmap> mBackground; ///< Background image for the level.

    Scoreboard mScoreboard;  // The scoreboard instance.

public:
    /// Constructor
    Game();

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
     * This function converts screen coordinates to virtual coordinates and logs the click.
     * @param x X location of the mouse click.
     * @param y Y location of the mouse click.
     */
    void OnLeftDown(int x, int y);

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

};

#endif // GAME_H
