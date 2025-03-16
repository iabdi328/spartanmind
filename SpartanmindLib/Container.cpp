/**
 * @file Container.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "Container.h"

Container::Container(Spartanmind* spartanmind, const std::wstring& filename,
           const wxString& id, wxString width, wxString height,
           const wxString& image, wxString value, wxString col, wxString row)
    : Item(spartanmind, filename), // Call the base class constructor
      mId(id), mWidth(width), mHeight(height),
      mImagePath(image), mValue(value), mCol(col), mRow(row)
{
    //std::cout << "Container created: " << std::endl;
}