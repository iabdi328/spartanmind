/**
* @file Scoreboard.cpp
 * @author Ismail Abdi
 */

#include "pch.h"
#include "Scoreboard.h"
#include <wx/font.h>
#include <wx/colour.h>

Scoreboard::Scoreboard()
{
}

void Scoreboard::Update(double deltaSeconds) {
 mElapsedTime += deltaSeconds;
}

void Scoreboard::Draw(std::shared_ptr<wxGraphicsContext> gc) const {
 // Set up a bold font for the scoreboard.
 wxFont font(ScoreboardTextSize, wxFONTFAMILY_DEFAULT, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
 gc->SetFont(font, *wxWHITE);

 // Convert elapsed time into minutes and seconds.
 int minutes = static_cast<int>(mElapsedTime) / 60;
 int seconds = static_cast<int>(mElapsedTime) % 60;
 wxString timeStr = wxString::Format("%d:%02d", minutes, seconds);

 // Draw the time at the fixed virtual position (ScoreboardTopLeft).
 gc->DrawText(timeStr, ScoreboardTopLeft.x, ScoreboardTopLeft.y);
}

double Scoreboard::GetElapsedTime() const {
 return mElapsedTime;
}

