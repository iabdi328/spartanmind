/**
 * @file Letter.h
 * @author Daniel Conti
 *
 *
 */
 
#ifndef LETTER_H
#define LETTER_H

#include "Game.h"
#include "Item.h"

class Letter : public Item
{
private:

    int mValue;

public:
    Letter(Game * game , int Value, const std::wstring&
    filename);


};



#endif //LETTER_H
