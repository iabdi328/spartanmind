/**
 * @file Chest.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "Chest.h"

/// Path to Chest Image
const wxString chestBodyImage = L"resources/images/chest.png";
/// Path to Chest Lid Image
const wxString chestLidImage = L"resources/images/chest-lid.png";

/**
 * Constructor
 * @param gameWorld game the Chest is member of
 */
Chest::Chest(Game* gameWorld) : Player(gameWorld, chestBodyImage, chestLidImage)
{

}

