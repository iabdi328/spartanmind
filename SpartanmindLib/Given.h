/**
 * @file Given.h
 * @author Daniel Conti
 *
 *
 */
 
#ifndef GIVEN_H
#define GIVEN_H

#include "Letter.h"
#include "Game.h"


class Game;

class Given : public Letter
{

private:
public:
    /// Default constructor (disabled)
    Given() = delete;

    /// Copy constructor (disabled)
    Given(const Given &) = delete;

    /// Assignment operator
    void operator=(const Given &) = delete;

    Given(Game *game, int value, std::wstring &
    filename);
};



#endif //GIVEN_H
