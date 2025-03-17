/**
 * @file Tray.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "Tray.h"

Tray::Tray(Game* game, const std::wstring& filename,
               const wxString& id, wxString width, wxString height,
               const wxString& image, wxString value, wxString col, wxString row)
    : Item(game, filename), // Call the base class constructor
      mId(id), mWidth(width), mHeight(height),
      mImagePath(image), mValue(value), mCol(col), mRow(row)
{
    //std::cout << "Tray created: " << mValue << std::endl;
}