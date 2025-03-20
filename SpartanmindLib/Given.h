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
     * Get the value of this given item
     * @return The value
     */
    int GetValue() const { return mValue; }
};



#endif //GIVEN_H
