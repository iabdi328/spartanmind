/**
 * @file Scoreboard.cpp
 * @author Ismail Abdi
 */

#include "pch.h"
#include "Scoreboard.h"
#include <wx/font.h>
#include <wx/colour.h>

/// Scoreboard Text Size
const int ScoreboardTextSize = 50;

/**
 * Location of scoreboard on g
 * @return (doxygen thinks this is a function)
 */
const wxPoint ScoreboardTopLeft(10, 10);

/**
 * Scoreboard Constructor
 */
Scoreboard::Scoreboard()
{
}

/**
 * Update scoreboard
 * @param deltaSeconds time
 */
void Scoreboard::Update(double deltaSeconds) {
    mElapsedTime += deltaSeconds;
}

/**
 * Draw the scoreboard in the game
 * @param gc game graphics context
 */
void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> gc) const {
    wxFont font(ScoreboardTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
    gc->SetFont(font, *wxWHITE);

    int minutes = (int)(mElapsedTime) / 60;
    int seconds = (int)(mElapsedTime) % 60;
    wxString timeStr = wxString::Format("%d:%02d", minutes, seconds);

    gc->DrawText(timeStr, ScoreboardTopLeft.x, ScoreboardTopLeft.y);
}
