/**
* @file Sparty.cpp
 * @author Emmanuel Koshy
 */
#include "pch.h"
#include "Sparty.h"
#include <cstdio>



Sparty::Sparty(Game* gameWorld)
    : Player(gameWorld, L"resources/images/sparty.png", L"resources/images/sparty-mouth.png") {
    // Initialize any Sparty-specific properties
    mBasePivot = wxPoint2DDouble(40, 86);  // Example base pivot (can be adjusted based on XML data)
    mAuxPivot = wxPoint2DDouble(30, 65);
    mLocation = wxPoint2DDouble(100, 100);

    mAuxAngle = 0; //initialize to zero
}
void Sparty::move(int x, int y) {
    // Directly set Sparty's position to the clicked coordinates
    mLocation = wxPoint2DDouble(x, y);
}

void Sparty::Headbutt() {
    if (!mIsHeadbutting) {
        mIsHeadbutting = true;
        mHeadbuttTimer = HeadbuttDuration;
        mBaseAngle = HeadbuttAngle;
        printf("Sparty is headbutting! Head tilting to %.2f radians\n", HeadbuttAngle);
    }
}


void Sparty::Eat() {
    if (!mIsEating) {
        mIsEating = true;
        mEatingTimer = EatingDuration;
        mAuxAngle = EatingAngle;  // Rotate the mouth to the max open position
        printf("Sparty is eating! Mouth opening to %.2f radians\n", EatingAngle);
    }
}

void Sparty::Update(double elapsedTime) {
    // Call the base class Update method for movement logic
    Player::Update(elapsedTime);

    // Handle Headbutt Animation (Head Tilting)
    if (mIsHeadbutting) {
        mHeadbuttTimer -= elapsedTime;
        if (mHeadbuttTimer > 0) {
            mHeadAngle = HeadbuttAngle * (mHeadbuttTimer / HeadbuttDuration);  // Tilt head during the headbutt
        } else {
            mHeadAngle = 0;  // Reset head position after headbutt
            mIsHeadbutting = false;
        }
    }

    // Handle Eating Animation (Mouth Opening)
    if (mIsEating) {
        mEatingTimer -= elapsedTime;
        if (mEatingTimer > 0) {
            mEatingAngle = EatingAngle * (1 - mEatingTimer / EatingDuration);  // Open mouth during eating
        } else {
            mEatingAngle = 0;  // Reset mouth angle after eating
            mIsEating = false;
            mAuxAngle = 0; // Reset mouth to the closed position after eating
        }
    }
}
void Sparty::Draw(wxGraphicsContext* graphics) {
    // First, apply rotation for the entire character (using the base pivot for headbutt)
    graphics->PushState();

    // Apply base pivot for headbutt animation (rotate entire character)
    graphics->Translate(mBasePivot.m_x, mBasePivot.m_y);  // Move to pivot point
    graphics->Rotate(mHeadAngle);  // Rotate around base pivot
    graphics->Translate(-mBasePivot.m_x, -mBasePivot.m_y);  // Move back after rotation

    // Translate to Sparty's current position
    graphics->Translate(mLocation.m_x, mLocation.m_y);

    // Draw image1 (head) at (0, 0)
    wxBitmap bmp1(mImage1, wxBITMAP_TYPE_PNG);
    if (bmp1.IsOk()) {
        graphics->DrawBitmap(bmp1, 0, 0, 96, 96);  // Width and height of 96px (as specified in XML)
    }

    // Now, apply the mouth animation (with auxiliary pivot)
    graphics->PushState();
    graphics->Translate(mAuxPivot.m_x, mAuxPivot.m_y);  // Move to the mouth pivot point
    graphics->Rotate(mAuxAngle);  // Rotate around the mouth pivot (for eating animation or lid opening)
    graphics->Translate(-mAuxPivot.m_x, -mAuxPivot.m_y);  // Move back after rotation

    // Draw image2 (mouth/lid)
    wxBitmap bmp2(mImage2, wxBITMAP_TYPE_PNG);
    if (bmp2.IsOk()) {
        graphics->DrawBitmap(bmp2, 0, 0, 96, 96);  // Drawing width and height of 96px
    }

    // Restore the graphics state
    graphics->PopState();

    // Restore the overall graphics state
    graphics->PopState();
}
bool Sparty::HitTest(int x, int y) const {
    // To test for a hit, we reverse the transformations applied in Draw().
    // Forward transformation:
    //    p_world = mLocation + R(mHeadAngle) * (p_local + mBasePivot) - mBasePivot
    // We invert this process.

    // lol Compute the vector from Sparty's position (world space) to the hit point.
    double qx = x - mLocation.m_x;
    double qy = y - mLocation.m_y;

    // Apply the inverse rotation: R(-mHeadAngle)
    // Note: cos(-a) = cos(a) and sin(-a) = -sin(a)
    double cosAngle = cos(mHeadAngle);
    double sinAngle = sin(mHeadAngle);

    // Shift the point by mBasePivot before rotating, then undo the pivot shift
    double localX = cosAngle * (qx + mBasePivot.m_x) + sinAngle * (qy + mBasePivot.m_y) - mBasePivot.m_x;
    double localY = -sinAngle * (qx + mBasePivot.m_x) + cosAngle * (qy + mBasePivot.m_y) - mBasePivot.m_y;

    // Now check if the resulting local coordinates lie within the head image's rectangle
    // (assumed to be at (0,0) with width and height 96)
    if (localX >= 0 && localX <= 96 && localY >= 0 && localY <= 96) {
        return true;
    }
    return false;
}