/**
 * @file Item.cpp
 * @author Daniel Conti
 * @author Raj Ambekar
 */

#include "pch.h"
#include "Item.h"

using namespace std;

/**
 * Constructor
 * @param spartanmind The spartanmind this item is a member of
 */
Item::Item(LoadLevel* level)
{
    mLevel = level;
}




/**
 * Draw this item
 * @param dc Device context to draw on
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    /*
    // cout << "Drawing letters" << endl;
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    //graphics->DrawBitmap(*mItemBitmap,
    //    int(GetX() - wid / 2), int(GetY() - hit / 2));
    */
    if (mItemImage != nullptr)
    {
        int wid = mItemImage->GetWidth();
        int hit = mItemImage->GetHeight();

        int pX = 0;
        int pY = 0;

        graphics->DrawBitmap(*mItemBitmap, pX, pY, wid, hit);
    }


}


void Item::XmlLoad(wxXmlNode *node)
{

}
void Item::Update(double elapsedTime)
{

}
