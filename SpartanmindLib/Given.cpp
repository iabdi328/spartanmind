/**
 * @file Given.cpp
 * @author Terrance Zackery, Raj Ambekar
 */

#include "pch.h"
#include "Given.h"
#include <iostream>

/// Location of images
const std::wstring loc = L"images/";

/**
 * Given constructor
 *
 * @param game The game this item is a part of
 * @param value The value of this given item
 * @param filename The filename for the item image
 */
Given::Given(Game *game, int value, std::wstring &filename) : Item(game, loc+filename)
{
    mValue = value;
}