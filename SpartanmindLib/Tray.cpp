/**
 * @file Tray.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "Tray.h"

/// Location of images
const std::wstring loc = L"../images/";

/**
 * Constructor
 * @param game The game this character is a member of
 * @param capacity The capacity of the xray
 * @param filename The image for the xray
 */
Tray::Tray(Game *game, int capacity, std::wstring &filename) : Item (game,
                                                                     loc+filename)
{
    mCapacity = capacity;
}