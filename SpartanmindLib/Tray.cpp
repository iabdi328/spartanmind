/**
 * @file Tray.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "Tray.h"
#include "Game.h"
#include <random>

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

void Tray::Add(std::shared_ptr<Item> item)
{
    std::uniform_real_distribution<> distribution(0, 80);
    auto trayX = this->GetX() + distribution(this->GetGame()->GetRandom
        ())*this->GetGame()->GetScale();
    auto trayY =  this->GetY() + distribution(this->GetGame()->GetRandom
        ())*this->GetGame()->GetScale();
    item->SetLocation(trayX, trayY);
    mTrayItems.push_back(item);
}

void Tray::Draw(const std::shared_ptr<wxGraphicsContext>& graphics) {

    Item::Draw(graphics);

    for(auto item : mTrayItems)
    {
        item->Draw(graphics);
    }

}