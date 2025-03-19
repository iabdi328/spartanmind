/**
 * @file Item.cpp
 * @author Daniel Conti
 * @author Raj Ambekar
 */

#include "pch.h"
#include "Item.h"

using namespace std;

Item::~Item()
{

}




/**
 * Constructor
 * @param game The game this item is a member of
 */
Item::Item(Game *game, const std::wstring &filename, const std::wstring &filename2) : mGame (game)
{
    if (filename != L"None")
    {
        mFirstImage = true;
        mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
        mItemBitmap = make_unique<wxBitmap>(*mItemImage);}

    if (filename2 != L"None"){
        mSecondImage = true;
        mItemImage2 = std::make_unique<wxImage>(filename2, wxBITMAP_TYPE_ANY);
        mItemBitmap2 = std::make_unique<wxBitmap>(*mItemImage2);
    }
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to theimage top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mItemImage->IsTransparent((int)testX, (int)testY);
}

/**
 * Draw this item
 * @param dc Device context to draw on
 */
void Item::Draw(const std::shared_ptr<wxGraphicsContext>& gc)
{
    // cout << "Drawing letters" << endl;
//    double mImageWidth = mItemBitmap->GetWidth();
//    double mImageHeight = mItemBitmap->GetHeight();
//    gc->DrawBitmap(*mItemBitmap, GetX(), GetY(), mImageWidth, mImageHeight);

    if(mFirstImage)
    {
        double mImageWidth = mItemBitmap->GetWidth();
        double mImageHeight = mItemBitmap->GetHeight();
        gc->DrawBitmap(*mItemBitmap, GetX(), GetY(), mImageWidth, mImageHeight);

    }

    if(mSecondImage){
        double wid2 = mItemBitmap2->GetWidth();
        double hit2 = mItemBitmap2->GetHeight();
        gc->DrawBitmap(*mItemBitmap2, int(GetX()), int(GetY()), wid2,
                             hit2);
    }
}

void Item::SetLocation(double x, double y) {
    mX = x;
    mY = y;
}