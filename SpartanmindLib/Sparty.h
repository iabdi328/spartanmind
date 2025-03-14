/**
* @file Sparty.h
* @author Emmanuel Koshy
*/


#ifndef PROJECT1_SPARTANMINDLIB_SARTY_H
#define SPARTY_H
#pragma once
#include "Player.h"
#include "Spartanmind.h"
class Spartanmind;

class Sparty : public Player
{
private:
    double mHeadAngle = 0;     // Head rotation angle for headbutt
    double mMouthAngle = 0.5;    // Angle for mouth rotation (eating)
    double mHeadbuttTimer = 0; // Timer for headbutt animation
    bool mIsHeadbutting = false; // Is headbutt in progress?

    double mEatingAngle = 1; // Eating angle for mouth rotation
    bool mIsEating = false;  // Is eating animation in progress
    double mEatingTimer = 0; // Timer for eating animation

    wxPoint2DDouble mAuxPivot;   // Pivot for mouth
    double mAuxAngle = 0;   // Aux angle for mouth rotation
    wxPoint2DDouble mBasePivot;  // Pivot for whole character during headbutt
    double mBaseAngle = 0;  // Base angle for headbutt

    const double HeadbuttDuration = 0.5; // Headbutt duration (seconds)
    const double HeadbuttAngle = 0.5; // Max angle for headbutt

    const double EatingDuration = 0.5;  // Eating lasts 0.5s
    const double EatingAngle = 1;  // Max mouth open angle
public:
    Sparty(Spartanmind* gameWorld);
    void move(int x, int y);

    void Update(double elapsedTime) override;  // Update Sparty movement and headbutt
    void Headbutt() override;  // Perform headbutt action
    void Eat() override;      // Perform eating action
    void Draw(wxGraphicsContext* graphics) override;  // Draw Sparty
};


#endif // SPARTY_H
