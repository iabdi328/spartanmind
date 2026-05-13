/**
 * @file Letter.cpp
 * @author Daniel Conti, Raj Ambekar, Terrance Zackery
 */

#include "pch.h"
#include "Letter.h"

/// Location for the image resources.
const std::wstring loc = L"images/";

/**
 * Constructor
 * @param game instance
 * @param value of letter
 * @param filename image
 */
Letter::Letter(Game *game, int value, std::wstring &filename) : Item(game, loc + filename)
{
    mValue = value;
}