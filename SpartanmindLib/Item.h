/**
* @file Item.h
 * @author Daniel Conti
 *
 *
 */

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <wx/image.h>
#include <memory>


class wxDC;
class Spartanmind;

class Item {
protected:
    Item(Spartanmind* spartanmind, const std::wstring &filename);


private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;

    // The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mItemBitmap;

    /// The spartanmind this item is contained in
    Spartanmind   *mSpartanmind;

    // Item location in the aquarium
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item
public:



    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    /// Assignment operator
    void operator=(const Item &) = delete;
    virtual ~Item();

    /**
       * The X location of the item
       * @return X location in pixels
       */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mX = x; mY = y; }

    /**
   * Test this item to see if it has been clicked on
   * @param x X location on the aquarium to test in pixels
   * @param y Y location on the aquarium to test in pixels
   * @return true if clicked on
   */
    bool HitTest(int x, int y);

    /**
    * Draw this item
    * @param dc Device context to draw on
    */
    void Draw(wxDC *dc);
};



#endif //ITEM_H
