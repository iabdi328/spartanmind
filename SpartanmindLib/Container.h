/**
 * @file Container.h
 * @author Terrance Zackery
 *
 * Container Class
 */

#ifndef PROJECT1_SPARTANMINDLIB_CONTAINER_H
#define PROJECT1_SPARTANMINDLIB_CONTAINER_H

#include "Item.h"

/**
 * Container Class, displays present box
 */
class Container : public Item
{
private:
    /// List of images contained within this container.
    std::vector<std::shared_ptr<Item>> mImages;
    /// List of items contained within this container.
    std::vector<std::shared_ptr<Item>> mContainedItems;

public:
    /// Default constructor (disabled to prevent misuse).
    Container() = delete;

    /// Copy constructor (disabled to prevent misuse).
    Container(const Container &) = delete;

    /// Assignment operator (disabled to prevent misuse).
    void operator=(const Container &) = delete;

    Container(Game * game);

    void Add(std::shared_ptr<Item> item) override;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitContainer(this); }

    /**
     * Tells the program that this is a container
     * @return true
     */
    bool IsContainer() override {return true;};

};

#endif //PROJECT1_SPARTANMINDLIB_CONTAINER_H
