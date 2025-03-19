/**
 * @file Scoreboard.h
 * @author Ismail Abdi
 *
 *
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <wx/graphics.h>
#include "memory"

// Define the scoreboard constants.
const int ScoreboardTextSize = 50;
const wxPoint ScoreboardTopLeft(10, 10);

class Scoreboard {
public:
 Scoreboard();

 // Update the elapsed time (deltaSeconds is the time elapsed since the last update).
 void Update(double deltaSeconds);

 // Draw the scoreboard (elapsed time in MM:SS format) using the provided graphics context.
 void Draw(std::shared_ptr<wxGraphicsContext> gc) const;

 // Optionally, get the elapsed time (in seconds).
 double GetElapsedTime() const;

private:
 double mElapsedTime; // Total elapsed time in seconds.

};

#endif //SCOREBOARD_H
