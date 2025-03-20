/**
 * @file LoadLevel.cpp
 * @author Terrance Zackery, Raj Ambekar
 */

#include "pch.h"
#include "Given.h"
#include "Player.h"
#include "Letter.h"
#include "Tray.h"
#include "Container.h"
#include "LoadLevel.h"
#include "Item.h"
#include <sstream>
#include <string>
#include <memory>
#include <wx/xml/xml.h>

using namespace std;

/**
 * Constructor
 * @param game
 */
LoadLevel::LoadLevel(Game *game): mGame(game)
{

}

/**
 * Load the game from the xml file
 * @param filename
 */
void LoadLevel::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }

    Clear();

    // Get the root node (Level)
    auto root = xmlDoc.GetRoot();
    auto rootName = root->GetName();

    // variables
    int width;
    int height;
    int tileWidth;
    int tileHeight;



    // Extract window sizing from level xml node
    root->GetAttribute(L"width").ToInt(&width);
    root->GetAttribute(L"height").ToInt(&height);
    root->GetAttribute(L"tilewidth").ToInt(&tileWidth);
    root->GetAttribute(L"tileheight").ToInt(&tileHeight);

    mGame->SetWidth(width);
    mGame->SetHeight(height);
    mGame->SetTileWidth(tileWidth);
    mGame->SetTileHeight(tileHeight);

    


//     Iterate through Levels data
    auto child = root->GetChildren();
    for (; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"declarations")
        {
            auto decChild = child->GetChildren();
            for(; decChild; decChild=decChild->GetNext())
            {
                auto decName = decChild->GetName();
                if (decName == L"given" || decName == L"letter")
                {
                    LetterNode(decChild);
                }

                if (decName == "tray")
                {
                    TrayNode(decChild);
                }

                if (decName == "background")
                {
                    BackgroundNode(decChild);
                }

                if (decName == "player")
                {
                    PlayerNode(decChild);
                }

                if (decName == "container")
                {
                    ContainerNode(decChild);
                }

            }
        }
        if(name == L"game"){
            auto solution = child->GetNodeContent().ToStdString();
            int solutionCol,solutionRow;
            child->GetAttribute(L"col").ToInt(&solutionCol);
            child->GetAttribute(L"row").ToInt(&solutionRow);
            std::stringstream iss( solution );
        }
    }
}

/**
 * Clear the game
 */
void LoadLevel::Clear()
{
    mGame->Clear();
}

/**
 * Container XML node constructor
 * @param node Container node form XML file
 */
void LoadLevel::TrayNode(wxXmlNode *node)
{
    // A pointer for the item we are loading
    auto tagName = node->GetName();

    auto id = node->GetAttribute(L"id");

    int capacity;
    node->GetAttribute(L"capacity").ToInt(&capacity);


    auto image = node->GetAttribute(L"image").ToStdWstring();

    // Level node to iterating into items
    auto root = node->GetParent()->GetParent();

    // iterate  items
    auto child = root->GetChildren();
    for (; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"items")
        {
            double col, row, height;
            auto itemsChild = child->GetChildren();
            for(; itemsChild; itemsChild=itemsChild->GetNext())
            {

                if (itemsChild->GetAttribute(L"id") == id)
                {
                    // set coordinates
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);
                    itemsChild->GetAttribute(L"height").ToDouble(&height);

                    if(tagName == L"tray")
                    {
                        shared_ptr<Item> tray;
                        tray = std::make_shared<Tray>(mGame, capacity, image);
                        tray->SetLocation((col*mGame->GetTileHeight()),
                                          (row)*mGame->GetTileWidth());
                        mGame->Add(tray);
                    }
                }

            }
        }
    }
}

void LoadLevel::BackgroundNode(wxXmlNode * node)
{

    auto id = node->GetAttribute(L"id");

    auto image = node->GetAttribute(L"image").ToStdWstring();

    auto root = node->GetParent()->GetParent();
    // iterate into item
    auto child = root->GetChildren();
    for (; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"items")
        {
            double col;
            double row;
            double height;

            auto itemsChild = child->GetChildren();
            for(; itemsChild; itemsChild = itemsChild->GetNext())
            {
                // node with the same id
                if(itemsChild->GetAttribute(L"id") == id)
                {
                    mGame->SetBackground(image);
                }
            }
        }
    }
}

void LoadLevel::LetterNode(wxXmlNode *node)
{
    // item we are loading
    auto tagName = node->GetName();

    auto id = node->GetAttribute(L"id");

    int value = 0;
    node->GetAttribute(L"value").ToInt(&value);

    auto image = node->GetAttribute(L"image").ToStdWstring();
    auto root = node->GetParent()->GetParent();
    // iterate into item
    auto child = root->GetChildren();
    for (; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"items")
        {
            double col, row;
            auto itemsChild = child->GetChildren();
            for(; itemsChild; itemsChild=itemsChild->GetNext())
            {
                if (itemsChild->GetAttribute(L"id") == id)
                {
                    // set coordinates
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);

                    // setting and adding given items
                    if(tagName == L"given")
                    {
                        shared_ptr<Item> given;
                        given = std::make_shared<Given>(mGame, value, image);
                        given->SetLocation((col*mGame->GetTileHeight()), ((row)
                            *mGame->GetTileWidth()));
                        mGame->Add(given);
                    }
                    // setting and adding letter items
                    if(tagName == L"letter")
                    {
                        shared_ptr<Item> letter;
                        letter = make_shared<Letter>(mGame, value, image);
                        letter->SetLocation((col*mGame->GetTileHeight()), ((row)
                            *mGame->GetTileWidth()));
                        mGame->Add(letter);
                    }

                }
            }

        }
    }
}

void LoadLevel::PlayerNode(wxXmlNode * node)
{
    // Define the path to images
    const wstring loc = L"../images/";

    // Get the player ID
    auto id = node->GetAttribute(L"id");

    // Get the image paths - properly combining with the base path
    auto image1 = loc + node->GetAttribute(L"image1").ToStdWstring();
    auto image2 = loc + node->GetAttribute(L"image2").ToStdWstring();

    // Get all animation parameters
    double headPivotAngle = std::stod(node->GetAttribute(L"head-pivot-angle").ToStdString());
    double headPivotX = std::stod(node->GetAttribute(L"head-pivot-x").ToStdString());
    double headPivotY = std::stod(node->GetAttribute(L"head-pivot-y").ToStdString());
    double mouthPivotAngle = std::stod(node->GetAttribute(L"mouth-pivot-angle").ToStdString());
    double mouthPivotX = std::stod(node->GetAttribute(L"mouth-pivot-x").ToStdString());
    double mouthPivotY = std::stod(node->GetAttribute(L"mouth-pivot-y").ToStdString());
    double targetX = std::stod(node->GetAttribute(L"target-x").ToStdString());
    double targetY = std::stod(node->GetAttribute(L"target-y").ToStdString());

    // Get the root node
    auto root = node->GetParent()->GetParent();

    // Find the player item in the items section
    auto child = root->GetChildren();
    for (; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"items")
        {
            double col, row;
            auto itemsChild = child->GetChildren();
            for(; itemsChild; itemsChild = itemsChild->GetNext())
            {
                if(itemsChild->GetAttribute(L"id") == id)
                {
                    // Get the player's position
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);

                    // Create the player with both images
                    std::shared_ptr<Player> player = std::make_shared<Player>(mGame, image1, image2);

                    // Set initial position
                    player->SetStartingLocation(col * mGame->GetTileHeight(),
                                                row * mGame->GetTileWidth());

                    // Set all animation parameters
                    player->SetHeadPivotAngle(headPivotAngle);
                    player->SetHeadPivotX(headPivotX);
                    player->SetHeadPivotY(headPivotY);
                    player->SetMouthPivotAngle(mouthPivotAngle);
                    player->SetMouthPivotX(mouthPivotX);
                    player->SetMouthPivotY(mouthPivotY);
                    player->SetTargetX(targetX);
                    player->SetTargetY(targetY);

                    // Add the player to the game
                    mGame->SetPlayer(player);
                    return;  // Exit once we've found and set up the player
                }
            }
        }
    }
}

void LoadLevel::ContainerNode(wxXmlNode *node)
{
    const wstring loc = L"../images/";

    // A pointer for the item we are loading
    auto tagName = node->GetName();

    auto id = node->GetAttribute(L"id");

    // 2 images in container
    auto image = node->GetAttribute(L"image").ToStdWstring();
    auto frontImage = node->GetAttribute(L"front").ToStdWstring();

    // Level node
    auto root = node->GetParent()->GetParent();
    // iterate into item
    auto child = root->GetChildren();
    for (; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"items")
        {
            double col, row;
            auto itemsChild = child->GetChildren();
            for(; itemsChild; itemsChild=itemsChild->GetNext())
            {

                if (itemsChild->GetAttribute(L"id") == id)
                {
                    // set coordinates
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);

                    // shared ptr for container items
                    shared_ptr<Container> container;
                    container = make_shared<Container>(mGame);

                    // setting background to first item in container vectorr
                    shared_ptr<Item> backImage;
                    backImage = make_shared<Item>(mGame,
                                                  loc+image);
                    backImage->SetLocation((col*mGame->GetTileHeight()), (
                        (row-4)*mGame->GetTileWidth()));
                    container->Add(backImage);

                }

            }
        }
    }
}