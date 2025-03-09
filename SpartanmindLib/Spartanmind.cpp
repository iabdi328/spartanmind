/**
 * @file Spartanmind.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "Spartanmind.h"

/**
 * Spartanmind Constructor
 */
Spartanmind::Spartanmind()
{
    mBackground = std::make_unique<wxBitmap>(L"resources/images/background.png", wxBITMAP_TYPE_ANY);
}

/**
 * Draw the aquarium
 * @param dc The device context to draw on
 */
void Spartanmind::OnDraw(wxDC *dc)
{
	// Clear the entire area
	dc->Clear();

	// Draw the background bitmap at (0,0).
	// If your background image is smaller than the window, it might not cover all of it.
	// For a quick fix, ensure your background images match the level dimensions,
	// or use a fill color to cover any gaps.
	if (mBackground && mBackground->IsOk())
	{
		dc->DrawBitmap(*mBackground, 0, 0, false);
	}
	// Additional drawing code...
}

void Spartanmind::SetBackground(const wxString& imagePath)
{
	mBackground = std::make_unique<wxBitmap>(imagePath, wxBITMAP_TYPE_ANY);
}