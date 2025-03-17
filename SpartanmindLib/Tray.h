/**
 * @file Tray.h
 * @author Terrance Zackery
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_TRAY_H
#define PROJECT1_SPARTANMINDLIB_TRAY_H

#include "Item.h"

class Tray : public Item
{
private:
    wxString mId;
    wxString mWidth;
    wxString mHeight;
    wxString mImagePath;
    wxString mValue;
    wxString mCol;
    wxString mRow;

public:
    Tray(Game* game, const std::wstring& filename,
    const wxString& id, wxString width, wxString height,
    const wxString& image, wxString value, wxString col, wxString row);

};

#endif //PROJECT1_SPARTANMINDLIB_TRAY_H
