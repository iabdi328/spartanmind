/**
 * @file Game.cpp
 * @author Ismail Abdi
 * @brief Implementation of the Game class.
 *
 */

#include "pch.h"
#include "Game.h"
#include <algorithm>
#include <wx/log.h>
#include <wx/graphics.h>

Game::Game()
    : mScale(1.0),
      mXOffset(0),
      mYOffset(0),
      mVirtualWidth(1150),   // Updated default width.
      mVirtualHeight(800)    // Updated default height.
{
    Initialize();
}

void Game::Initialize() {
    // (You can add additional initialization here if needed.)
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
}

void Game::OnLeftDown(int x, int y) {
    // Convert screen coordinates to virtual coordinates.
    double virtualX = (x - mXOffset) / mScale;
    double virtualY = (y - mYOffset) / mScale;
    wxLogMessage("Mouse clicked at virtual coordinates: (%.2f, %.2f)", virtualX, virtualY);
}

void Game::UpdateScoreboard(double deltaSeconds) {
    mScoreboard.Update(deltaSeconds);
}
