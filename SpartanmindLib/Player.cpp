/**
 * @file Player.cpp
 * @author Emmanuel Koshy
 */
 
#include "Player.h"


///  Constructor takes `Spartanmind*`
Player::Player(Spartanmind* gameWorld, const std::wstring& filename)
    : mGameWorld(gameWorld), mFilename(filename), mX(0), mY(0), mWidth(96), mHeight(96),
      mTargetX(0), mTargetY(0) {}

void Player::Update(double elapsedTime) {
    //  Move towards target
    double dx = mTargetX - mX;
    double dy = mTargetY - mY;
    double distance = sqrt(dx * dx + dy * dy);

    if (distance > 1) {
        double moveX = (dx / distance) * 400.0 * elapsedTime;
        double moveY = (dy / distance) * 400.0 * elapsedTime;
        mX += moveX;
        mY += moveY;
    }
}

void Player::Draw(wxGraphicsContext* graphics) {
    wxBitmap characterBitmap(mFilename, wxBITMAP_TYPE_PNG);

    if (characterBitmap.IsOk()) {
        graphics->DrawBitmap(characterBitmap, mX, mY, mWidth, mHeight);
    } else {
        printf("Failed to load image: %ls\n", mFilename.c_str());
    }
}

void Player::SetTarget(double x, double y) {
    mTargetX = x;
    mTargetY = y;
}