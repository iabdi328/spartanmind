/**
* @file Item.h
 * @author Daniel Conti
 * @author Raj Ambekar
 *
 */

#ifndef ITEM_H
#define ITEM_H
#include <string>
#include <wx/image.h>
#include <memory>


class Spartanmind;
class Game;

class Item {

private:
    /// The game this item is contained in
    Game* mGame;
    /// The first image
    bool mFirstImage = true;
    bool mSecondImage = false;

     /// The underlying item image
     std::unique_ptr<wxImage> mItemImage;
     std::unique_ptr<wxImage> mItemImage2;

     /// The bitmap we can display for this item
     std::unique_ptr<wxBitmap> mItemBitmap;
     std::unique_ptr<wxBitmap> mItemBitmap2;

     /// Item location in the spartanmind
     double  mX;     ///< X location for the center of the item
     double  mY;     ///< Y location for the center of the item
     double mImageHeight; ///< The height of the image
     double mImageWidth; ///< The width of the image


public:

     /// Default constructor (disabled)
     Item() = delete;
     /// Copy constructor (disabled)
     Item(const Item &) = delete;
     /// Assignment operator
     void operator=(const Item &) = delete;
     /// Constructor
     Item(Game *game, const std::wstring &filename1 = L"None", const std::wstring
     &filename2 = L"None");

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

     double GetImageHeight() { return mImageHeight;};

     /**
     * Get the Width of the item
     * @return double Image Width
     */

    double GetImageWidth() { return mImageWidth;};
    /**
    * Set the location of the item
    */
    void SetLocation(double x, double y);


     /**
      * Test this item to see if it has been clicked on
      * @param x X location on the spartanmind to test in pixels
      * @param y Y location on the spartanmind to test in pixels
      * @return true if clicked on
      */
     bool HitTest(int x, int y);

     /**
      * Draw this item
      * @param dc Device context to draw on
      */
     virtual void Draw(const std::shared_ptr<wxGraphicsContext>& );
        virtual void Update(double elapsed) {}
        /**
         * Get the game
         * @return The game
         */
        Game * GetGame() {return mGame;}
};

#endif //ITEM_H