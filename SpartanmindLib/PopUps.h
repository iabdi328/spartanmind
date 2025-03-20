/**
 * @file PopUps.h
 * @author Emmanuel Koshy
 *
 *
 */
 
#ifndef POPUPS_H
#define POPUPS_H

#include <wx/graphics.h>
#include <string>
#include <memory>

/**
 * @class PopUps
 * @brief Handles on-screen pop-up messages, such as the “level begins” message.
 */
class PopUps
{
private:
    /// Whether the popup is currently visible
    bool mVisible = false;

    /// The message text for this popup
    std::wstring mMessage;

    /// Time in seconds that this popup should remain on screen
    double mDuration = 3.0;

    /// Elapsed time since the popup became visible
    double mElapsed = 0.0;

public:
    PopUps() = default;
    virtual ~PopUps() = default;

    /**
     * @brief Show a popup with the specified message and duration.
     * @param message The text to display.
     * @param duration How many seconds to display.
     */
    void ShowPopup(const std::wstring& message, double duration = 3.0);

    /**
     * @brief Update the popup’s timer.
     * @param elapsed Time in seconds since last update.
     */
    void Update(double elapsed);

    /**
     * @brief Draw the popup if it is visible.
     * @param gc Graphics context to draw on.
     * @param width The width of the drawing area.
     * @param height The height of the drawing area.
     */
    void Draw(std::shared_ptr<wxGraphicsContext> gc, int width, int height);

    /**
     * @brief Check if the popup is currently visible.
     * @return True if visible, false otherwise.
     */
    bool IsVisible() const { return mVisible; }
};

#endif // POPUPS_H
