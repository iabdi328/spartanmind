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
    /// Value of letter
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
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitLetter(this); }
    int GetValue() { return mValue; }

    bool IsLetter() override { return true; }
};



#endif //LETTER_H
