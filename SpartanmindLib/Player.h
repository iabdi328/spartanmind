#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <wx/geometry.h>
#include <string>
#include <wx/graphics.h>

#include "Spartanmind.h"

class Player {
protected:
    Spartanmind* mGameWorld;
    wxPoint2DDouble mLocation;  // Current position of the player
    wxPoint2DDouble mTarget;    // Target position of the player
    const double MaxSpeed = 400.0;  // Movement speed in pixels per second

    // Image files for the player
    std::wstring mImage1; // e.g., "sparty.png"
    std::wstring mImage2; // e.g., "sparty-mouth.png"

    // Target offsets (from XML attributes)
    double mTargetXOffset = 0;
    double mTargetYOffset = 0;

    // Pivot points for headbutt and mouth (or lid)
    wxPoint2DDouble mBasePivot;  // Base pivot for headbutt rotation
    double mBaseAngle = 0;  // Headbutt angle

    wxPoint2DDouble mAuxPivot;  // Auxiliary pivot for the mouth or lid animation
    double mAuxAngle = 0;   // Auxiliary angle

public:
    Player(Spartanmind* gameWorld, const std::wstring& image1, const std::wstring& image2);
    virtual ~Player() {}

    virtual void Update(double elapsedTime);  // Updates position based on movement
    virtual void Draw(wxGraphicsContext* graphics) = 0;  // Pure virtual for drawing player
    virtual void Headbutt() = 0;  // Method to perform headbutt animation

    // Movement methods
    void SetTarget(double x, double y);  // Set the target position
    void SetPosition(double x, double y);  // Set the current position of the player
};

#endif // PLAYER_H
