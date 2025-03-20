/**
* @file Player.cpp
 * @author  Emmanuel Koshy, Terrance Zackery
 *
 *
 */
#include "pch.h"
#include "Player.h"
#include "Game.h"
#include <wx/graphics.h>
#include <wx/geometry.h>
#include <cstdio>


/// Character speed in pixels per second
const double mMaxSpeed = 400.00;

/// The time for an eating cycles in seconds
const double EatingTime = 0.5;

/// The time for a headbutt cycle in seconds
const double HeadbuttTime = 0.5;

Player::Player(Game *game, std::wstring headImage, std::wstring mouthImage ) : Item(game, headImage, mouthImage)
{
    mGameWorld = game;
    mEating = false;
    mHeadbutt = false;
    mEatingTimer = 0;
    mHeadbuttTimer = 0;
    mDirection = 0;
    mSpeed = 0;
    mX = 0;
    mY = 0;
    const std::wstring loc = L"../images/";
    mSpartyImage = std::make_unique<wxBitmap>(loc+headImage, wxBITMAP_TYPE_ANY);
    mMouthImage = std::make_unique<wxBitmap>(loc+mouthImage, wxBITMAP_TYPE_ANY);

}

// Update method
void Player::Update(double elapsedTime) {

    if (mMoving)
    {
        // Update the direction of Sparty
        mDirectionX = mDestX - mX;
        mDirectionY = mDestY - mY;
        mDirection = atan2(mDirectionY, mDirectionX);

        // Update the speed of Sparty
        mSpeed = mMaxSpeed;

        // Update the location of Sparty
        mX += mSpeed * cos(mDirection) * elapsedTime;
        mY += mSpeed * sin(mDirection) * elapsedTime;

        double distanceToDestination = sqrt(mDirectionX * mDirectionX + mDirectionY * mDirectionY);
        if (distanceToDestination < mTargetY) { // You can adjust the threshold as needed
            mMoving = false;
            mX = mDestX;
            mY = mDestY;
        }
    } else if(mEating) //mouth animation
    {
        mEatingTimer += elapsedTime/EatingTime;
        if (mEatingTimer > EatingTime)
        {
            mEating = false;
            mEatingTimer = 0;
        }
    } else if(mHeadbutt) //headbutt animation
    {
        mHeadbuttTimer += elapsedTime/HeadbuttTime;
        if (mHeadbuttTimer > HeadbuttTime)
        {
            mHeadbutt = false;
            mHeadbuttTimer = 0;
        }
    }

    else {
        mSpeed = 0;
    }
}

void Player::SetStartingLocation(double x, double y){
    mX = x;
    mY = y;
}

void Player::Draw(std::shared_ptr<wxGraphicsContext> graphics) {
    auto position = ComputePosition();
    // Draw player
    if (mSpartyImage != nullptr && !mHeadbutt)
    {
        graphics->DrawBitmap(*mSpartyImage, mX, mY, wid, hit);
    }
    // Draw player mouth
    if (mMouthImage != nullptr && !mEating && !mHeadbutt)
    {
        graphics->DrawBitmap(*mMouthImage, mX, mY, wid, hit);
    }
    if (mMouthImage != nullptr && mEating)
    {
        graphics->Translate(position.x + mMouthPivotX , position.y +  mMouthPivotY);
        graphics->Rotate(1);
        graphics->DrawBitmap(*mMouthImage, 0, 0, wid, hit);
        graphics->PopState();

    }
    if(mSpartyImage != nullptr && mHeadbutt && !mEating)
    {
        //Make player headbutt
        graphics->Translate(position.x + mTargetX , position.y );
        graphics->Rotate(1);
        //Draw playeer
        graphics->DrawBitmap(*mSpartyImage, 0, 0,wid, hit);
        //Draw mouth
        graphics->DrawBitmap(*mMouthImage, 0, 0, wid, hit);
        graphics->PopState();
    }
    graphics->PushState();
}

/**
* Set Location of Player
 * @param x X location in pixels
 * @param y Y location in pixels
*/
void Player::SetLocation(double x, double y)
{
    mDestX = ((x - mGameWorld->GetXOffset() )/
        mGameWorld->GetScale()) - mSpartyImage->GetWidth();
    mDestY = ((y - mGameWorld->GetYOffset()) / mGameWorld->GetScale()) - mSpartyImage
        ->GetHeight();
    if (mX == mDestX && mY == mDestY)
    {
        mMoving = false;
    }
    else
    {
        mMoving = true;
    }
}

void Player::SetTarget(double x, double y) {
    // Adjust the target based on target-x and target-y offsets
    mTarget = wxPoint2DDouble(x - mTargetXOffset, y - mTargetYOffset);
}

void Player::SetPosition(double x, double y) {
    mLocation = wxPoint2DDouble(x, y);  // Set the current position of the player
}


void Player::Headbutt() {
    if (!mHeadbutt) {
        mHeadbutt = true;
        mHeadbuttTimer = HeadbuttDuration;
        mBaseAngle = HeadbuttAngle;
        printf("Sparty is headbutting! Head tilting to %.2f radians\n", HeadbuttAngle);
    }
}


void Player::Eat() {
    if (!mEating) {
        mEating = true;
        mEatingTimer = EatingDuration;
        mAuxAngle = EatingAngle;  // Rotate the mouth to the max open position
        printf("Sparty is eating! Mouth opening to %.2f radians\n", EatingAngle);
    }
}

/**
* Compute position
 * @return position of playeer
**/
wxRealPoint Player::ComputePosition()
{
    wxRealPoint pos(mX,mY);
    return pos;
}

//bool Sparty::HitTest(int x, int y) const {
//    // To test for a hit, we reverse the transformations applied in Draw().
//    // Forward transformation:
//    //    p_world = mLocation + R(mHeadAngle) * (p_local + mBasePivot) - mBasePivot
//    // We invert this process.
//
//    // lol Compute the vector from Sparty's position (world space) to the hit point.
//    double qx = x - mLocation.m_x;
//    double qy = y - mLocation.m_y;
//
//    // Apply the inverse rotation: R(-mHeadAngle)
//    // Note: cos(-a) = cos(a) and sin(-a) = -sin(a)
//    double cosAngle = cos(mHeadAngle);
//    double sinAngle = sin(mHeadAngle);
//
//    // Shift the point by mBasePivot before rotating, then undo the pivot shift
//    double localX = cosAngle * (qx + mBasePivot.m_x) + sinAngle * (qy + mBasePivot.m_y) - mBasePivot.m_x;
//    double localY = -sinAngle * (qx + mBasePivot.m_x) + cosAngle * (qy + mBasePivot.m_y) - mBasePivot.m_y;
//
//    // Now check if the resulting local coordinates lie within the head image's rectangle
//    // (assumed to be at (0,0) with width and height 96)
//    if (localX >= 0 && localX <= 96 && localY >= 0 && localY <= 96) {
//        return true;
//    }
//    return false;
//}