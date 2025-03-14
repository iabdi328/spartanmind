/**
 * @file Chest.h
 * @author Raj Ambekar
 *
 * Class for the Chest Player
 */

#ifndef PROJECT1_SPARTANMINDLIB_CHEST_H
#define PROJECT1_SPARTANMINDLIB_CHEST_H

#include "Player.h"

class Spartanmind;

/**
 * Class for the Chest Player
 */
class Chest : public Player
{
private:
    /// Chest tilt angle for headbutt-like animation
    double mTiltAngle = 0;
    /// Angle for lid rotation (opening)
    double mLidAngle = 0;
    /// Timer for tilt animation
    double mTiltTimer = 0;
    /// Is tilt in progress?
    bool mIsTilting = false;
    /// Opening angle for lid rotation
    double mOpeningAngle = 0;
    /// Is opening animation in progress
    bool mIsOpening = false;
    /// Timer for opening animation
    double mOpeningTimer = 0;
    /// Pivot for lid
    wxPoint2DDouble mAuxPivot;
    /// Aux angle for lid rotation
    double mAuxAngle = 0;
    /// Pivot for whole chest during tilt
    wxPoint2DDouble mBasePivot;
    /// Base angle for tilt
    double mBaseAngle = 0;
    /// Tilt duration (seconds)
    const double TiltDuration = 0.5;
    /// Max angle for tilt
    const double TiltAngle = 0.5;
    /// Opening lasts 0.5s
    const double OpeningDuration = 0.5;
    /// Max lid open angle (negative for counterclockwise)
    const double OpeningAngle = -1.5;

public:
    Chest(Spartanmind* gameWorld);
    //void move(int x, int y);

    void Update(double elapsedTime) override;
    void Headbutt() override;
    void Eat() override;
    void Draw(wxGraphicsContext* graphics) override;

};

#endif //PROJECT1_SPARTANMINDLIB_CHEST_H
