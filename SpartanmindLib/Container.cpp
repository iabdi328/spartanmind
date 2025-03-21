/**
 * @file Container.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "Container.h"

using namespace std;

/// Location of images
const std::wstring loc = L"images/";

/**
 * Container constructor
 * @param game The game this container is a part of.
 */
Container::Container(Game * game) : Item(game)
{

}

/**
 * Add to Container
 * @param item Item to add
 */
void Container::Add(std::shared_ptr<Item> item)
{
    std::cout << "Here is one containere letter: " << item;
    mContainedItems.push_back(item);
    for (auto item : mContainedItems)
    {
        std::cout << "Here is one containere letter: " << item;
    }
}