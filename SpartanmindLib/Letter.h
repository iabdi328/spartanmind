/**
 * @file Letter.h
 * @author Daniel Conti, Raj Ambekar, Terrance Zackery
 *
 * Letter Class
 */
 
#ifndef LETTER_H
#define LETTER_H


#include "Item.h"

/**
 * Letter Class
 */
class Letter : public Item
{
private:

    int mValue;

public:
    /// Constructor
    Letter(Game * game , int Value, std::wstring &filename);
    /// Default constructor (disabled)
    Letter() = delete;
    /// Copy constructor (disabled)
    Letter(const Letter &) = delete;
    /// Assignment operator
    void operator=(const Letter &) = delete;

    /**
     * Get the value of this letter
     * @return The value
     */
    int GetValue() const { return mValue; }

};



#endif //LETTER_H
