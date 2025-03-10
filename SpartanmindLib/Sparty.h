#ifndef SPARTY_H
#define SPARTY_H
#pragma once
#include "Player.h"
#include "Spartanmind.h"

class Sparty : public Player {
private:
    double mHeadAngle = 0;     // Head rotation angle for headbutt
    double mHeadbuttTimer = 0; // Timer for headbutt animation
    bool mIsHeadbutting = false;

    static constexpr double HeadbuttDuration = 0.5; // Headbutt lasts 0.5s
    static constexpr double HeadbuttAngle = 0.5; // Max head tilt angle

public:
    Sparty(Spartanmind* gameWorld);

    void Update(double elapsedTime) override;  // Update Sparty movement and headbutt
    void Headbutt() override;  // Perform headbutt action
    void Draw(wxGraphicsContext* graphics) override;  // Draw Sparty
};

#endif // SPARTY_H
