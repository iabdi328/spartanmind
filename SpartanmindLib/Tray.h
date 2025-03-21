/**
 * @file Tray.h
 * @author Terrance Zackery
 *
 * Tray Class
 */

#ifndef PROJECT1_SPARTANMINDLIB_TRAY_H
#define PROJECT1_SPARTANMINDLIB_TRAY_H

#include "Item.h"

/**
 * Tray Class
 */
class Tray : public Item
{
private:
    /// Tray Items
    std::vector<std::shared_ptr<Item>> mTrayItems;

    /// Capacity of xray
    int mCapacity = 0;

public:
    /**
     * Constructor
     * @param game The game this character is a member of
     * @param capacity The capacity of the xray
     * @param filename The image for the xray
     */
    Tray(Game * game, int capacity, std::wstring &filename);

    /// Default constructor (disabled)
    Tray() = delete;

    /// Copy constructor (disabled)
    Tray(const Tray &) = delete;

    /// Assignment operator
    void operator=(const Tray &) = delete;

    void Add(std::shared_ptr<Item> item) override;
    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitTray(this); }

    /**
     * Retrieves all items contained in the tray.
     * @return A vector of shared pointers to items in the tray.
     */
    std::vector<std::shared_ptr<Item>> GetrayItems() { return mTrayItems; }

    /**
     * Checks whether the tray is full.
     * @return True if the tray is full (i.e., the number of items is equal to or exceeds the capacity), false otherwise.
     */
    bool IsFull()
    {
        if(mTrayItems.size() < mCapacity) return false;
        return true;
    }

    //draws the graphics
    void Draw(const std::shared_ptr<wxGraphicsContext> &graphics) override;
    //removes letters from tray
    void Remove(std::shared_ptr<Item> item);
};

#endif //PROJECT1_SPARTANMINDLIB_TRAY_H
