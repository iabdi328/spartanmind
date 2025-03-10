/**
* @file Player.cpp
 * @author  Emmanuel Koshy
 *
 *
 */
#include "Player.h"
#include <wx/graphics.h>
#include <wx/geometry.h>
#include <cstdio>

Player::Player(Spartanmind* gameWorld, const std::wstring& image1, const std::wstring& image2)
    : mGameWorld(gameWorld), mImage1(image1), mImage2(image2), mLocation(0, 0), mTarget(0, 0) {
    // Initialize target offsets, pivots, angles, etc.
    mTargetXOffset = 72;  // Example value, based on XML attributes
    mTargetYOffset = 24;  // Example value, based on XML attributes
    mBasePivot = wxPoint2DDouble(40, 86);  // Example base pivot for headbutt (you can modify as per XML)
    mAuxPivot = wxPoint2DDouble(30, 65);   // Example mouth pivot
}

// Update method
void Player::Update(double elapsedTime) {
    // Calculate the vector from the current position to the target
    wxPoint2DDouble direction = mTarget - mLocation;

    // Calculate the distance to the target manually using std::sqrt
    double distanceToTarget = std::sqrt(direction.m_x * direction.m_x + direction.m_y * direction.m_y);

    // If there's distance left to the target
    if (distanceToTarget > 0) {
        // Calculate how far Sparty should move this frame (based on max speed and elapsed time)
        double moveLength = MaxSpeed * elapsedTime;

        // If the move length is greater than or equal to the distance to the target, just move to the target
        if (moveLength >= distanceToTarget) {
            mLocation = mTarget;  // Set the player at the target position directly
        } else {
            // Otherwise, move towards the target by the calculated move length
            direction.Normalize();  // Normalize direction to get a unit vector
            mLocation += direction * moveLength;  // Move Sparty in the direction towards the target
        }
    }
}



void Player::Draw(wxGraphicsContext* graphics) {
    // First, apply rotation for the headbutt (using the base pivot)
    graphics->PushState();
    
    // Apply rotation around the base pivot
    graphics->Translate(mBasePivot.m_x, mBasePivot.m_y);
    graphics->Rotate(mBaseAngle);  // mBaseAngle is the current headbutt angle
    graphics->Translate(-mBasePivot.m_x, -mBasePivot.m_y);
    
    // Translate to the current position of the player
    graphics->Translate(mLocation.m_x, mLocation.m_y);
    
    // Draw image1 (the main body/head) at (0, 0)
    wxBitmap bmp1(mImage1, wxBITMAP_TYPE_PNG);
    if (bmp1.IsOk()) {
        graphics->DrawBitmap(bmp1, 0, 0, 96, 96);  // Drawing width and height of 96px (as specified)
    }

    // Now, apply the mouth (or lid) animation (with auxiliary pivot)
    graphics->PushState();
    graphics->Translate(mAuxPivot.m_x, mAuxPivot.m_y);
    graphics->Rotate(mAuxAngle);  // Rotate around the mouth/lid pivot
    graphics->Translate(-mAuxPivot.m_x, -mAuxPivot.m_y);

    // Draw image2 (the mouth or lid)
    wxBitmap bmp2(mImage2, wxBITMAP_TYPE_PNG);
    if (bmp2.IsOk()) {
        graphics->DrawBitmap(bmp2, 0, 0, 96, 96);  // Drawing width and height of 96px (as specified)
    }
    graphics->PopState();

    // Restore graphics state
    graphics->PopState();
}

void Player::SetTarget(double x, double y) {
    // Adjust the target based on target-x and target-y offsets
    mTarget = wxPoint2DDouble(x - mTargetXOffset, y + (mLocation.m_y - mTargetYOffset));
}

void Player::SetPosition(double x, double y) {
    mLocation = wxPoint2DDouble(x, y);  // Set the current position of the player
}
void Player::Eat() {
    // Base implementation (if any)
    // In this case, we might leave it empty, assuming Sparty will handle the eating logic
}