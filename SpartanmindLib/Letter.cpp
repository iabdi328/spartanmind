/**
 * @file Letter.cpp
 * @author Daniel Conti, Raj Ambekar, Terrance Zackery
 */

#include "pch.h"
#include "Letter.h"

/// Location for the image resources.
const std::wstring loc = L"../images/";

Letter::Letter(Game *game, int value, std::wstring &filename) : Item(game, loc + filename)
{
    mValue = value;
}