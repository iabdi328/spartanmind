/**
 * @file LLetter.h
 * @author Terrance Zackery
 *
 *
 */



#ifndef PROJECT1_SPARTANMINDLIB_LLETTER_H
#define PROJECT1_SPARTANMINDLIB_LLETTER_H

#include "Letter.h"

class LLetter : public Letter
{
private:

public:
    LLetter() = delete;

    /// Copy constructor (disabled)
    LLetter(const LLetter &) = delete;

    /// Assignment operator
    void operator=(const LLetter &) = delete;

    LLetter(Game * game, int value, std::wstring &
    filename);

};

#endif //PROJECT1_SPARTANMINDLIB_LLETTER_H
