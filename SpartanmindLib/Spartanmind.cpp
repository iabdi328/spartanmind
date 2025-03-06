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
    dc->DrawBitmap(*mBackground, 0, 0);

}