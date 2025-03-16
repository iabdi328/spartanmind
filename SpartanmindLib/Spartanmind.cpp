/**
* @file Spartanmind.cpp
 * @author Raj Ambekar, Emmanuel Koshy
 *
 *
 */
#include "pch.h"
#include "Spartanmind.h"

#include "Given.h"
#include "Letter.h"
#include "Sparty.h"  // Include Sparty header

/**
 * Spartanmind Constructor
 */
Spartanmind::Spartanmind()
{
	mBackground = std::make_unique<wxBitmap>(L"resources/images/background.png", wxBITMAP_TYPE_ANY);
	mPlayer = new Sparty(this);  // Initialize Sparty (the player character)
}

/**
 * Spartanmind Destructor
 */
Spartanmind::~Spartanmind() {
	delete mPlayer;  // Clean up Sparty instance when Spartanmind is destroyed
}

/**
 * Draw the Game
 * @param dc The device context to draw on
 */
void Spartanmind::OnDraw(wxDC *dc)
{
	// Clear the entire area
	dc->Clear();

	// Draw the background bitmap at (0,0).
	if (mBackground && mBackground->IsOk())
	{
		dc->DrawBitmap(*mBackground, 0, 0, false);
	}

	// Create a wxGraphicsContext from the wxDC
	wxGraphicsContext* gc = wxGraphicsContext::Create(dc);

	if (gc)
	{
		// Draw Sparty on top of the background using wxGraphicsContext
		mPlayer->Draw(gc);  // Ensure Sparty is drawn after the background
		delete gc;  // Clean up the wxGraphicsContext
	}
}

/**
 * Update the Game State
 * @param elapsedTime The time elapsed since the last frame
 */
void Spartanmind::Update(double elapsedTime)
{
	mPlayer->Update(elapsedTime);  // Update Sparty’s state (movement, actions)
}

/**
 * Set the background image for the game
 * @param imagePath The path to the new background image
 */
void Spartanmind::SetBackground(const wxString& imagePath)
{
	mBackground = std::make_unique<wxBitmap>(imagePath, wxBITMAP_TYPE_ANY);
}

void Spartanmind::AddLetter(Letter* letter)
{
	mLetters.push_back(letter);
}

void Spartanmind::ClearLetters()
{
	mLetters.clear();
}

void Spartanmind::AddGiven(Given* given)
{
	mGivens.push_back(given);
}

void Spartanmind::ClearGivens()
{
	mGivens.clear();
}
void Spartanmind::AddTray(Tray* tray)
{
    mTray.push_back(tray);
}
void Spartanmind::ClearTrays()
{
    mTray.clear();
}
void Spartanmind::AddContainer(Container* container)
{
    mContainer.push_back(container);
}
void Spartanmind::ClearContainers()
{
    mGivens.clear();
}