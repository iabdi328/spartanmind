/**
 * @file Given.cpp
 * @author Daniel Conti
 */

#include "pch.h"
#include "Given.h"
#include <iostream>

using namespace std;

/// Location of images
const wstring loc = L"../images/";

/**
 * Given Number constructor
 *
 * @param game
 * @param value
 * @param filename
 */
Given::Given(Game *game, int value,
                         std::wstring &filename) : Letter
                                                       (game, value, loc+filename)
{
}
