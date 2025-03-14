/**
 * @file Chest.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "Chest.h"

/// Path to Chest Image
const wxString chestBodyImage = L"resources/images/chest.png";
/// Path to Chest Lid Image
const wxString chestLidImage = L"resources/images/chest-lid.png";

/**
 * Constructor
 * @param gameWorld game the Chest is member of
 */
Chest::Chest(Spartanmind* gameWorld) : Player(gameWorld, chestBodyImage, chestLidImage)
{
    mBasePivot = wxPoint2DDouble(40, 86);
    mAuxPivot = wxPoint2DDouble(95, 40);
    mLocation = wxPoint2DDouble(800, 100);
}

/**
 * Move the chest (inactive placer)
 * @param x position
 * @param y position
 */
/*
void Chest::move(int x, int y) {
    // Directly set Chest's position to the clicked coordinates
    mLocation = wxPoint2DDouble(x, y);
}
*/

/**
 *
 */
void Chest::Headbutt() {
    if (!mIsTilting) {
        mIsTilting = true;
        mTiltTimer = TiltDuration;
        mBaseAngle = TiltAngle;
    }
}

/**
 * Handle Chest Eat event
 */
void Chest::Eat() {
    if (!mIsOpening) {
        mIsOpening = true;
        mOpeningTimer = OpeningDuration;
        mAuxAngle = OpeningAngle;
    }
}

/**
 * Update chest animation
 * @param elapsedTime time
 */
void Chest::Update(double elapsedTime) {
    // Call the base class Update method for movement logic
    Player::Update(elapsedTime);

    // Handle Tilt Animation (Chest Tilting)
    if (mIsTilting) {
        mTiltTimer -= elapsedTime;
        if (mTiltTimer > 0) {
            mTiltAngle = TiltAngle * (mTiltTimer / TiltDuration);  // Tilt chest during the animation
        } else {
            mTiltAngle = 0;  // Reset chest position after tilt
            mIsTilting = false;
        }
    }

    // Handle Opening Animation (Lid Opening)
    if (mIsOpening) {
        mOpeningTimer -= elapsedTime;
        if (mOpeningTimer > 0) {
            mAuxAngle = OpeningAngle * (1 - mOpeningTimer / OpeningDuration);  // Open lid during animation
        } else {
            mAuxAngle = 0;  // Reset lid angle after opening
            mIsOpening = false;
        }
    }
}

/**
 * Draw the chest in the game
 * @param graphics
 */
void Chest::Draw(wxGraphicsContext* graphics) {
    // First, apply rotation for the entire chest (using the base pivot for tilt)
    graphics->PushState();

    // Apply base pivot for tilt animation (rotate entire chest)
    graphics->Translate(mBasePivot.m_x, mBasePivot.m_y);  // Move to pivot point
    graphics->Rotate(mTiltAngle);  // Rotate around base pivot
    graphics->Translate(-mBasePivot.m_x, -mBasePivot.m_y);  // Move back after rotation

    // Translate to Chest's current position
    graphics->Translate(mLocation.m_x, mLocation.m_y);

    // Draw image1 (chest body) at (0, 0)
    wxBitmap bmp1(mImage1, wxBITMAP_TYPE_PNG);
    if (bmp1.IsOk()) {
        graphics->DrawBitmap(bmp1, 0, 0, 96, 96);  // Width and height of 96px (as specified in XML)
    }

    // Now, apply the lid animation (with auxiliary pivot)
    graphics->PushState();
    graphics->Translate(mAuxPivot.m_x, mAuxPivot.m_y);  // Move to the lid pivot point on right side
    graphics->Rotate(mAuxAngle);  // Rotate around the lid pivot (for opening animation)
    graphics->Translate(-mAuxPivot.m_x, -mAuxPivot.m_y);  // Move back after rotation

    // Draw image2 (lid)
    wxBitmap bmp2(mImage2, wxBITMAP_TYPE_PNG);
    if (bmp2.IsOk()) {
        graphics->DrawBitmap(bmp2, 0, 0, 96, 96);  // Drawing width and height of 96px
    }

    // Restore the graphics state
    graphics->PopState();

    // Restore the overall graphics state
    graphics->PopState();
}

