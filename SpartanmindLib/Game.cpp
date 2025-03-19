/**
 * @file Game.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 *
 */

#include "pch.h"
#include "Game.h"
#include "LoadLevel.h"
#include <algorithm>
#include <wx/log.h>
#include <wx/graphics.h>
#include "Sparty.h"

Game::Game()
    : mScale(1.0),
      mXOffset(0),
      mYOffset(0),
      mVirtualWidth(1150),   // Updated default width.
      mVirtualHeight(800),   // Updated default height.
      mPlayer(nullptr)
{
    Initialize();
}

Game::~Game() {
    delete mPlayer;  // Clean up Sparty instance when Game is destroyed
}

void Game::Initialize() {
    mBackground = std::make_unique<wxBitmap>(L"resources/images/background.png", wxBITMAP_TYPE_ANY);
    mPlayer = new Sparty(this);  // Initialize Sparty (the player character)
}

void Game::Update(double deltaSeconds) {
    mPlayer->Update(deltaSeconds);  // Update Sparty's state (movement, actions)
    UpdateScoreboard(deltaSeconds);
}

void Game::SetVirtualDimensions(int virtualWidth, int virtualHeight) {
    mVirtualWidth = virtualWidth;
    mVirtualHeight = virtualHeight;
}

void Game::SetBackground(const wxString& imagePath) {
    mBackground = std::make_unique<wxBitmap>(imagePath, wxBITMAP_TYPE_ANY);
    if (mBackground && !mBackground->IsOk()) {
        wxLogError("Failed to load background image: %s", imagePath);
    }
}

bool Game::LoadLvl(const wxString &filename)
{
    LoadLevel *mLevel = new LoadLevel;
    mLevel->LoadFromXML(filename);

}

void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height) {
    // Calculate scale factors based on the virtual dimensions.
    double scaleX = static_cast<double>(width) / mVirtualWidth;
    double scaleY = static_cast<double>(height) / mVirtualHeight;
    mScale = std::min(scaleX, scaleY);

    // Calculate offsets to center the virtual playing area.
    mXOffset = (width - mVirtualWidth * mScale) / 2.0;
    mYOffset = (height - mVirtualHeight * mScale) / 2.0;

    gc->PushState();
    gc->Translate(mXOffset, mYOffset);
    gc->Scale(mScale, mScale);

    // Draw the background image if available.
    if (mBackground && mBackground->IsOk()) {
        gc->DrawBitmap(*mBackground, 0, 0, mVirtualWidth, mVirtualHeight);
    }
    else {
        // Fallback: draw a red rectangle.
        wxBrush brush(*wxRED);
        gc->SetBrush(brush);
        gc->DrawRectangle(0, 0, mVirtualWidth, mVirtualHeight);
    }
    gc->PopState();

    mScoreboard.Draw(gc);
    LoadLevel *mLevel = new LoadLevel;
    mLevel->OnDraw(gc);
}



void Game::UpdateScoreboard(double deltaSeconds) {
    mScoreboard.Update(deltaSeconds);
}

// Letter management methods
void Game::AddLetter(Letter* letter) {
    mLetters.push_back(letter);
}

void Game::ClearLetters() {
    mLetters.clear();
}

// Given management methods
void Game::AddGiven(Given* given) {
    mGivens.push_back(given);
}

void Game::ClearGivens() {
    mGivens.clear();
}

// Tray management methods
void Game::AddTray(Tray* tray) {
    mTray.push_back(tray);
}

void Game::ClearTrays() {
    mTray.clear();
}

// Container management methods
void Game::AddContainer(Container* container) {
    mContainer.push_back(container);
}

void Game::ClearContainers() {
    mContainer.clear();  // Note: Fixed from original where it was clearing mGivens instead
}