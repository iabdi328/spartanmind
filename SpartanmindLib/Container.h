/**
 * @file Container.h
 * @author Terrance Zackery
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_CONTAINER_H
#define PROJECT1_SPARTANMINDLIB_CONTAINER_H

#include "Item.h"

class Container : public Item
{
private:
    wxString mId;
    wxString mWidth;
    wxString mHeight;
    wxString mImagePath;
    wxString mValue;
    wxString mCol;
    wxString mRow;
    /// List of images contained within this container.
    std::vector<std::shared_ptr<Item>> mImages;
    /// List of items contained within this container.
    std::vector<std::shared_ptr<Item>> mContainedItems;

public:

    Container(Spartanmind* spartanmind, const std::wstring& filename,
    const wxString& id, wxString width, wxString height,
    const wxString& image, wxString value, wxString col, wxString row);
};

#endif //PROJECT1_SPARTANMINDLIB_CONTAINER_H
