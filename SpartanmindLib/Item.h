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
#include <wx/xml/xml.h>

class Game;
class LoadLevel;

class Item {
protected:
    wxString levelFile;
    LoadLevel* mLevel;
    std::string mId;
    double mCol;
    double mRow;
    std::unique_ptr<wxImage> mItemImage;
    std::unique_ptr<wxBitmap> mItemBitmap;

public:
    /// Constructor
    Item(LoadLevel* level);
    /// Default constructor (disabled)
    Item() = delete;
    /// Copy constructor (disabled)
    Item(const Item &) = delete;
    /// Assignment operator
    void operator=(const Item &) = delete;
    //~Item();


    virtual void XmlLoad(wxXmlNode *node);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    virtual void Update(double elapsedTime);


    double GetX() const { return mCol; }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mRow; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y) { mCol = x; mRow = y; }




};

#endif //ITEM_H