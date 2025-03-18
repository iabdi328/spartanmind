/**
 * @file LLetter.cpp
 * @author Terrance Zackery
 */

#include "LLetter.h"

using namespace std;

/// Location for the image resources.
const wstring loc = L"../images/";


LLetter::LLetter(Game *game, int value, std::wstring &filename)
    : Letter(game, value, loc + filename)
{
}