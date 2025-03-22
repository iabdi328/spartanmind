/**
 * @file Given.h
 * @author Terrance Zackery, Raj Ambekar
 *
 * Given Class
 */
 
#ifndef GIVEN_H
#define GIVEN_H

#include "Game.h"
#include "Item.h"


class Game;

/**
 * Given Class
 */
class Given : public Item
{

private:
    /// Letter value
    int mValue;

public:
    /// Constructor
    Given(Game *game, int value, std::wstring &filename);
    /// Default constructor (disabled)
    Given() = delete;
    /// Copy constructor (disabled)
    Given(const Given &) = delete;
    /// Assignment operator
    void operator=(const Given &) = delete;

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitGiven(this); }
    /**
     * Tells the program that this is a container
     * @return mValue
     */
    int GetValue() const override { return mValue; }
};



#endif //GIVEN_H
