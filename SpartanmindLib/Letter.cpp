/**
 * @file Letter.cpp
 * @author Daniel Conti
 */
 
#include "Letter.h"



Letter::Letter(Spartanmind* spartanmind, const std::wstring& filename,
               const wxString& id, wxString width, wxString height,
               const wxString& image, wxString value, wxString col, wxString row)
    : Item(spartanmind, filename), // Call the base class constructor
      mId(id), mWidth(width), mHeight(height),
      mImagePath(image), mValue(value), mCol(col), mRow(row)
{
    //std::cout << "Letter created: " << mValue << std::endl;
}
