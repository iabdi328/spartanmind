/**
 * @file Letter.h
 * @author Daniel Conti
 *
 *
 */
 
#ifndef LETTER_H
#define LETTER_H

#include "Item.h"

class Letter : public Item {
public:
    Letter(Game* game, const std::wstring& filename,
               const wxString& id, wxString width, wxString height,
               const wxString& image, wxString value, wxString col, wxString row);

private:
    wxString mId;
    wxString mWidth;
    wxString mHeight;
    wxString mImagePath;
    wxString mValue;
    wxString mCol;
    wxString mRow;
};



#endif //LETTER_H
