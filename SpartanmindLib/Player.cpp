/**
 * @file Player.cpp
 * @author  Emmanuel Koshy, Terrance Zackery, Raj Ambekar
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

/**
 * Player Constructor
 * @param game Player in the game
 * @param headImage head image file path
 * @param mouthImage mouth image file path
 */
Player::Player(Game *game, std::wstring headImage, std::wstring mouthImage)
    : Item(game, headImage),
        mEatSound("sounds/eat.wav"),
        mHeadbuttSound("sounds/headbut.wav")
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

    mPlayerImage = std::make_unique<wxBitmap>(headImage, wxBITMAP_TYPE_ANY);
    mMouthImage = std::make_unique<wxBitmap>(mouthImage, wxBITMAP_TYPE_ANY);

    wid = mPlayerImage->GetWidth();
    hit = mPlayerImage->GetHeight();

    mHeadPivotAngle = 0;
    mHeadPivotX = 0;
    mHeadPivotY = 0;
    mMouthPivotAngle = 0;
    mMouthPivotX = 0;
    mMouthPivotY = 0;
    mTargetX = 0;
    mTargetY = 0;
}

/**
 * Update player action
 * @param elapsedTime time
 */
void Player::Update(double elapsedTime) {
    if (mMoving)
    {
        // Existing movement logic remains unchanged
        mDirectionX = mDestX - mX;
        mDirectionY = mDestY - mY;
        mDirection = atan2(mDirectionY, mDirectionX);
        mSpeed = mMaxSpeed;
        mX += mSpeed * cos(mDirection) * elapsedTime;
        mY += mSpeed * sin(mDirection) * elapsedTime;
        double distanceToDestination = sqrt(mDirectionX * mDirectionX + mDirectionY * mDirectionY);
        if (distanceToDestination < mTargetY) {
            mMoving = false;
            mX = mDestX;
            mY = mDestY;
        }
    }
    else
    {
        mSpeed = 0;
    }

    // Handle eating animation regardless of movement
    if (mEating)
    {
        mEatingTimer += elapsedTime;
        if (mEatingTimer >= EatingDuration)  // EatingDuration = 0.5
        {
            mEating = false;
            mEatingTimer = 0;
        }
    }

    // Handle headbutt animation regardless of movement
    if (mHeadbutt)
    {
        mHeadbuttTimer += elapsedTime;
        if (mHeadbuttTimer >= HeadbuttDuration)  // HeadbuttDuration = 0.5
        {
            mHeadbutt = false;
            mHeadbuttTimer = 0;
        }
    }
}

/**
 * Set the initial location
 * @param x location
 * @param y location
 */
void Player::SetStartingLocation(double x, double y){
    mX = x;
    mY = y;
}

/**
 * Draw the player in the game
 * @param graphics context
 */
void Player::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{

    int headWid = mPlayerImage->GetWidth();
    int headHit = mPlayerImage->GetHeight();
    int mouthWid = mMouthImage->GetWidth();
    int mouthHit = mMouthImage->GetHeight();

    // Save the current graphics state
    graphics->PushState();

    // Draw the player's body
    if (mPlayerImage != nullptr && !mHeadbutt)
    {
        // Normal state - draw the body at the current position
        graphics->DrawBitmap(*mPlayerImage, mX, mY, headWid, headHit);
    }

    // Draw the player's mouth
    if (mMouthImage != nullptr && !mEating && !mHeadbutt)
    {
        // Normal state - draw the mouth at the same position as the body
        graphics->DrawBitmap(*mMouthImage, mX, mY, mouthWid, mouthHit);
    }
    else if (mMouthImage != nullptr && mEating)
    {
        // Eating animation - apply mouth pivot transformation
        graphics->PushState();
        graphics->Translate(mX + mMouthPivotX, mY + mMouthPivotY);
        graphics->Rotate(mMouthPivotAngle);
        graphics->DrawBitmap(*mMouthImage, -mMouthPivotX, -mMouthPivotY, mouthWid, mouthHit);
        graphics->PopState();
    }

    // Handle headbutt animation
    if (mPlayerImage != nullptr && mHeadbutt)
    {
        // Headbutt animation - apply head pivot transformation
        graphics->PushState();
        graphics->Translate(mX + mHeadPivotX, mY + mHeadPivotY);
        graphics->Rotate(mHeadPivotAngle);
        graphics->DrawBitmap(*mPlayerImage, -mHeadPivotX, -mHeadPivotY, headWid, headHit);

        // Draw mouth in headbutt position too
        if (mMouthImage != nullptr)
        {
            graphics->DrawBitmap(*mMouthImage, -mHeadPivotX, -mHeadPivotY, mouthWid, mouthHit);
        }
        graphics->PopState();
    }

    // Restore the graphics state
    graphics->PopState();
}

/**
 * Set Location of Player
 * @param x X location in pixels
 * @param y Y location in pixels
*/
void Player::SetLocation(double x, double y)
{
    mDestX = ((x - mGameWorld->GetXOffset() )/
        mGameWorld->GetScale()) - mPlayerImage->GetWidth();
    mDestY = ((y - mGameWorld->GetYOffset()) / mGameWorld->GetScale()) - mPlayerImage
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

/**
 * Set Position of the Player
 * @param x location
 * @param y location
 */
void Player::SetPosition(double x, double y) {
    mLocation = wxPoint2DDouble(x, y);  // Set the current position of the player
}

/**
 * Headbutt Function
 */
void Player::Headbutt() {

    if (mHeadbuttSound.IsOk())
        mHeadbuttSound.Play(wxSOUND_ASYNC);


    if (!mHeadbutt)
    {
        mHeadbutt = true;
        mHeadbuttTimer = 0;  // Start at 0, not HeadbuttDuration
        mBaseAngle = HeadbuttAngle;
        printf("Sparty is headbutting! Head tilting to %.2f radians\n", HeadbuttAngle);
        std::shared_ptr<Item> letter = mGameWorld->GetItems(mX, mY);
        if (!letter) return;
        std::cout << mX << ", " << mY << std::endl;
        if (mX > 1100 && mX < 1300 && letter->IsLetter() && letter)
        {
            mGameWorld->ScatterLetters();
        }
    }
}

/**
 * Eat Function
 */
void Player::Eat() {
    if (!mEating) {
        mEating = true;
        mEatingTimer = 0;  // Start at 0, not EatingDuration
        mAuxAngle = EatingAngle;
        printf("Sparty is eating! Mouth opening to %.2f radians\n", EatingAngle);
        if (mEatSound.IsOk())
            mEatSound.Play(wxSOUND_ASYNC);
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
