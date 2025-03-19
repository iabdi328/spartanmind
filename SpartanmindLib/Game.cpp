/**
 * @file Game.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 *
 */

#include "pch.h"
#include "Game.h"
#include "Player.h"
#include <algorithm>
#include <wx/log.h>
#include <wx/graphics.h>
#include "Item.h"

Game::Game()
{
    mBackground = std::make_unique<wxBitmap>(L"images/background.png", wxBITMAP_TYPE_ANY);
//    mScoreboard = std::make_shared<Scoreboard>();
}




void Game::Update(double deltaSeconds) {
    UpdateScoreboard(deltaSeconds);
    if (mPlayer != nullptr) {
        mPlayer->Update(deltaSeconds);
    }
    for (auto item : mItems)
    {
        item->Update(deltaSeconds);
    }

}

void Game::SetVirtualDimensions(int virtualWidth, int virtualHeight) {
    mVirtualWidth = virtualWidth;
    mVirtualHeight = virtualHeight;
}

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height) {

    int pixelWidth =  mWidth * mTileWidth;
    int pixelHeight = mHeight * mTileHeight;

    // Automatic Scaling
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    gc->PushState();

    gc->Translate(mXOffset, mYOffset);
    gc->Scale(mScale, mScale);


    //
    // Draw in virtual pixels on the graphics context
    //
    if (!mBackground->IsNull())
    {
        // I am not sure what needs to be done with pixelWidth and pixelHeight.
        // I think this is taken care in the Load function.
        gc->DrawBitmap(*mBackground, 0, 0, pixelWidth, pixelHeight);
    }

    // drawing scoreboard and each item for the game

    mScoreboard.Draw(gc);

    for (auto item : mItems)
    {
        item->Draw(gc);
    }

    mPlayer->Draw(gc);

    gc->PopState();

}

void Game::UpdateScoreboard(double deltaSeconds) {
    mScoreboard.Update(deltaSeconds);
}

void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

void Game::Clear()
{
    mItems.clear();
}