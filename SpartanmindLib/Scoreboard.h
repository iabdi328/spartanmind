/**
 * @file Scoreboard.h
 * @author Ismail Abdi
 *
 * Scoreboard class to display time
 */

#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <wx/graphics.h>
#include "memory"

/**
 * Scoreboard class to display time
 */
class Scoreboard {
private:
    /// Total elapsed time in seconds.
    double mElapsedTime;

public:
    Scoreboard();
    void Update(double deltaSeconds);
    void Draw(std::shared_ptr<wxGraphicsContext> gc) const;
    void Reset();
    void SubtractTime(double seconds);

    /**
     * Get the elapsed amount of time
     * @return elapsed time
     */
    double GetElapsedTime() const { return mElapsedTime; };





};

#endif //SCOREBOARD_H
