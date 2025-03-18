/**
 * @file GameArea.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "SpartanmindView.h"
#include "Given.h"
#include "Sparty.h"
#include "Player.h"
#include "LLetter.h"
#include "Tray.h"
#include "Container.h"
#include "LoadLevel.h"
#include "Item.h"
#include <sstream>
#include <vector>
#include <string>
#include <memory>
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>

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
    int width, height, tileWidth, tileHeight;



    // Extract window sizing from level xml node
    root->GetAttribute(L"width").ToInt(&width);
    root->GetAttribute(L"height").ToInt(&height);
    root->GetAttribute(L"tilewidth").ToInt(&tileWidth);
    root->GetAttribute(L"tileheight").ToInt(&tileHeight);

    mGame->SetWidth(width);
    mGame->SetHeight(height);
    mGame->SetTileWidth(tileWidth);
    mGame->SetTileHeight(tileHeight);


//     Iterate through Level's Child XML nodes:
//     declarations, game, items
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
                    SpartyNode(decChild);
                }
//
//                if (decName == "container")
//                {
//                    ContainerNode(decChild);
//                }


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
    // name of the tag
    auto tagName = node->GetName();
    // id of the element
    auto id = node->GetAttribute(L"id");
    //Value of the number
    int capacity;
    node->GetAttribute(L"capacity").ToInt(&capacity);
    // image

    auto image = node->GetAttribute(L"image").ToStdWstring();
    // Go up to Level node to iterating into items
    auto root = node->GetParent()->GetParent();
    // iterate into item
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
                // find the node with the same id. there can be multiple
                if (itemsChild->GetAttribute(L"id") == id)
                {
                    // set coordinates
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);
                    itemsChild->GetAttribute(L"height").ToDouble(&height);

                    // working so far.
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
    // id of the element
    auto id = node->GetAttribute(L"id");
    // image
    auto image = node->GetAttribute(L"image").ToStdWstring();
    // Go up to Level node to iterating into items
    auto root = node->GetParent()->GetParent();
    // iterate into item
    auto child = root->GetChildren();
    for (; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"items")
        {
            double col, row, height;
            auto itemsChild = child->GetChildren();
            for(; itemsChild; itemsChild = itemsChild->GetNext())
            {
                // find the node with the same id. there can be multiple
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
    // A pointer for the item we are loading
    // name of the tag
    auto tagName = node->GetName();
    // id of the element
    auto id = node->GetAttribute(L"id");
    //Value of the number
    int value = 0;
    node->GetAttribute(L"value").ToInt(&value);
    // image
    auto image = node->GetAttribute(L"image").ToStdWstring();
    // Go up to Level node to iterating into items
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
                // find the node with the same id. there can me multiple
                if (itemsChild->GetAttribute(L"id") == id)
                {
                    // set coordinates
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);

                    // working so far.
                    if(tagName == L"given")
                    {
                        shared_ptr<Item> given;
                        given = std::make_shared<Given>(mGame, value, image);
                        given->SetLocation((col*mGame->GetTileHeight()), ((row)
                            *mGame->GetTileWidth()));
                        mGame->Add(given);
//                        wxLogMessage("Given Letter set: %s", col);
                    }

                    if(tagName == L"letter")
                    {
                        shared_ptr<Item> letter;
                        letter = make_shared<LLetter>(mGame, value, image);
                        letter->SetLocation((col*mGame->GetTileHeight()), ((row)
                            *mGame->GetTileWidth()));
                        mGame->Add(letter);
//                        wxLogMessage("Given Letter set: %s", row);
                    }

                }
            }

        }
    }
}
void LoadLevel::SpartyNode(wxXmlNode * node)
{
    // id of the element
    auto id = node->GetAttribute(L"id");
    // image
    auto image1 = node->GetAttribute(L"image1").ToStdWstring();
    auto image2 = node->GetAttribute(L"image2").ToStdWstring();

    ////<sparty id="i250" width="96" height="96" front="1" head-pivot-angle="1.5" head-pivot-x="40" head-pivot-y="86" image1="sparty-3.png" image2="sparty-4.png" mouth-pivot-angle="0.5" mouth-pivot-x="30" mouth-pivot-y="65" target-x="72" target-y="24" />
    auto headPivotAngle = node->GetAttribute(L"head-pivot-angle");
    auto headPivotX = node->GetAttribute(L"head-pivot-x");
    auto headPivotY = node->GetAttribute(L"head-pivot-y");
    auto mouthPivotAngle = node->GetAttribute(L"mouth-pivot-angle");
    auto mouthPivotX = node->GetAttribute(L"mouth-pivot-x");
    auto mouthPivotY = node->GetAttribute(L"mouth-pivot-y");
    auto targetX = node->GetAttribute(L"target-x");
    auto targetY = node->GetAttribute(L"target-y");

    // Go up to Level node to iterating into items
    auto root = node->GetParent()->GetParent();

    // iterate into item
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
                // find the node with the same id. there can be multiple
                if(itemsChild->GetAttribute(L"id") == id)
                {
                    // set coordinates
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);

                    std::shared_ptr<Player> player;
                    player = std::make_shared<Player>(mGame, image1, image2);
                    player->SetStartingLocation((col*mGame->GetTileHeight()), ((row)
                        *mGame->GetTileWidth()));
                    player->SetHeadPivotAngle(std::stod(headPivotAngle.ToStdString()));
                    player->SetHeadPivotX(std::stod(headPivotX.ToStdString()));
                    player->SetHeadPivotY(std::stod(headPivotY.ToStdString()));
                    player->SetMouthPivotAngle(std::stod(mouthPivotAngle.ToStdString()));
                    player->SetMouthPivotX(std::stod(mouthPivotX.ToStdString()));
                    player->SetMouthPivotY(std::stod(mouthPivotY.ToStdString()));
                    player->SetTargetX(std::stod(targetX.ToStdString()));
                    player->SetTargetY(std::stod(targetY.ToStdString()));
                    mGame->SetPlayer(player);

                }
            }
        }
    }
}
//void LoadLevel::ContainerNode(wxXmlNode *node)
//{
//    const wstring loc = L"../images/";
//    // A pointer for the item we are loading
//    // name of the tag
//    auto tagName = node->GetName();
//    // id of the element
//    auto id = node->GetAttribute(L"id");
//    // 2 images
//    auto image = node->GetAttribute(L"image").ToStdWstring();
//    auto frontImage = node->GetAttribute(L"front").ToStdWstring();
//    // Go up to Level node to iterating into items
//    auto root = node->GetParent()->GetParent();
//    // iterate into item
//    auto child = root->GetChildren();
//    for (; child; child=child->GetNext())
//    {
//        auto name = child->GetName();
//        if (name == L"items")
//        {
//            double col, row;
//            auto itemsChild = child->GetChildren();
//            for(; itemsChild; itemsChild=itemsChild->GetNext())
//            {
//                // find the node with the same id. there can me multiple
//                if (itemsChild->GetAttribute(L"id") == id)
//                {
//                    // set coordinates
//                    itemsChild->GetAttribute(L"col").ToDouble(&col);
//                    itemsChild->GetAttribute(L"row").ToDouble(&row);
//
//                    // construct Container. It only makes a vector of items
//                    // and draws them separately.
//                    shared_ptr<Container> container;
//                    container = make_shared<Container>(mGame);
//
//                    // make the background image as the first element in the
//                    // list of container items
//                    shared_ptr<Item> backImage;
//                    backImage = make_shared<Item>(mGame,
//                                                  loc+image);
//                    backImage->SetLocation((col*mGame->GetTileHeight()), (
//                        (row-4)*mGame->GetTileWidth()));
//                    container->Add(backImage);
//
//
//                }
//
//            }
//        }
//    }
//}