/**
 * @file Letter.cpp
 * @author Daniel Conti
 */

#include "pch.h"
#include "Letter.h"

using namespace std;

/// Location for the image resources.
const wstring loc = L"../images/";

Letter::Letter(Game * game,int value, const std::wstring &
filename) : Item(game, filename)
{
    mValue = value;
}
