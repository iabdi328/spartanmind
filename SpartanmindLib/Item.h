/**
 * @file Item.h
 * @author Daniel Conti
 * @author Raj Ambekar
 *
 * Base Item Class
 */

#ifndef ITEM_H
#define ITEM_H

#include "ItemVisitor.h"
#include <string>
#include <wx/image.h>
#include <memory>

class Game;

/**
 * Base Item Class
 */
class Item {

private:
     /// The game this item is contained in
     Game* mGame;
     /// The first image
     bool mFirstImage = true;
     /// Second image
     bool mSecondImage = false;

     /// The underlying item image for image 1
     std::unique_ptr<wxImage> mItemImage;
     /// The underlying item image for image 2
     std::unique_ptr<wxImage> mItemImage2;

     /// The bitmap we can display for the image 1
     std::unique_ptr<wxBitmap> mItemBitmap;
     /// The bitmap we can display for the image 1
     std::unique_ptr<wxBitmap> mItemBitmap2;

     /// Item location in the spartanmind
     double  mX;     ///< X location for the center of the item
     double  mY;     ///< Y location for the center of the item


protected:
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
     Item(Game *game, const std::wstring &filename1 = L"None", const std::wstring &filename2 = L"None");

     virtual ~Item();

     bool HitTest(int x, int y);

     virtual void Draw(const std::shared_ptr<wxGraphicsContext>& gc);

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
      * Get the Height of the item
      * @return double Image Height
      */
     double GetImageHeight() { return mImageHeight;};

     /**
      * Get the Width of the item
      * @return double Image Width
      */
     double GetImageWidth() { return mImageWidth;};

     /**
      * Set location of item
      * @param x position
      * @param y position
      */
     void SetLocation(double x, double y) { mX = x; mY = y; };

      /**
       * Base update class
       * @param elapsed time
       */
      virtual void Update(double elapsed) {}

      /**
       * Get the game
       * @return The game
       */
      Game* GetGame() { return mGame; }

      /**
       * Accept a visitor for all items
       * @param visitor The accepted visitor
       */
      virtual void Accept(ItemVisitor* visitor){};

};

#endif //ITEM_H