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
#include "PopUps.h"

/**
 * Game Constructor
 */
Game::Game()
{
    mBackground = std::make_unique<wxBitmap>(L"images/background.png", wxBITMAP_TYPE_ANY);
}

/**
 * Update game view
 * @param deltaSeconds time
 */
void Game::Update(double deltaSeconds) {
    UpdateScoreboard(deltaSeconds);
    mPopUps.Update(deltaSeconds);
    if (mPlayer != nullptr) {
        mPlayer->Update(deltaSeconds);
    }
    for (auto item : mItems)
    {
        item->Update(deltaSeconds);
    }
}

/**
 * Sets the virtual dimensions for items
 * @param virtualWidth
 * @param virtualHeight
 */
void Game::SetVirtualDimensions(int virtualWidth, int virtualHeight) {
    mVirtualWidth = virtualWidth;
    mVirtualHeight = virtualHeight;
}

/**
 * Draw the game context
 * @param gc context
 * @param width of game
 * @param height of game
 */
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

    mPopUps.Draw(gc, width, height);

    gc->PopState();
}

/**
 * Update the scoreboard
 * @param deltaSeconds
 */
void Game::UpdateScoreboard(double deltaSeconds) {
    mScoreboard.Update(deltaSeconds);
}

/**
 * Add items to item list
 * @param item
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Appends to the word solution list
 * @param number the letter
 */
void Game::AddAnswer(int number)
{
    mWord.push_back(number);
}

/**
 * Remove all items when loading new level
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Class to display pop up on new level
 * @param levelNumber int level
 */
void Game::ShowLevelBeginPopup(int levelNumber)
{
    std::wstring message = L"Level " + std::to_wstring(levelNumber) + L" Begins!";
    mPopUps.ShowPopup(message, 3.0);
}