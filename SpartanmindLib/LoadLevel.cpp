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
 * Constructor for loading in levels
 * @param game instance
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
    mGame->ClearGuessedWord();
    mGame->ClearWord();
    wxXmlDocument xmlDoc;

    if(!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Game file");
        return;
    }

    Clear();

    auto root = xmlDoc.GetRoot();
    auto rootName = root->GetName();

    int width;
    int height;
    int tileWidth;
    int tileHeight;

    root->GetAttribute(L"width").ToInt(&width);
    root->GetAttribute(L"height").ToInt(&height);
    root->GetAttribute(L"tilewidth").ToInt(&tileWidth);
    root->GetAttribute(L"tileheight").ToInt(&tileHeight);

    mGame->SetWidth(width);
    mGame->SetHeight(height);
    mGame->SetTileWidth(tileWidth);
    mGame->SetTileHeight(tileHeight);

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
        if (name == L"game")
        {
            auto solution = child->GetNodeContent().ToStdString();
            int solutionCol,solutionRow,solutionLength;
            child->GetAttribute(L"col").ToInt(&solutionCol);
            child->GetAttribute(L"row").ToInt(&solutionRow);
            child->GetAttribute(L"length").ToInt(&solutionLength);
            wxString input = child->GetNodeContent();
            std::stringstream ss(input.ToStdString());
            int number;
            while (ss >> number) {

                mGame->AddAnswer(number);
            }
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
 * Loads in the Tray
 * @param node xml tray node
 */
void LoadLevel::TrayNode(wxXmlNode *node)
{
    auto tagName = node->GetName();

    auto id = node->GetAttribute(L"id");

    int capacity;
    node->GetAttribute(L"capacity").ToInt(&capacity);

    auto image = node->GetAttribute(L"image").ToStdWstring();

    auto root = node->GetParent()->GetParent();

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
                    itemsChild->GetAttribute(L"col").ToDouble(&col);
                    itemsChild->GetAttribute(L"row").ToDouble(&row);
                    itemsChild->GetAttribute(L"height").ToDouble(&height);

                    if(tagName == L"tray")
                    {
                        shared_ptr<Item> tray;
                        tray = std::make_shared<Tray>(mGame, capacity, image);
                        tray->SetLocation((col*mGame->GetTileHeight()),(row)*mGame->GetTileWidth());
                        mGame->Add(tray);
                    }
                }

            }
        }
    }
}

/**
 * Loads in the background
 * @param node xml background node
 */
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

/**
 * Loads in the letter and givens declarations and items
 * @param node xml letter node
 */
void LoadLevel::LetterNode(wxXmlNode *node)
{
    auto tagName = node->GetName();
    auto id = node->GetAttribute(L"id");

    int value = 0;
    node->GetAttribute(L"value").ToInt(&value);

    auto image = node->GetAttribute(L"image").ToStdWstring();
    if (image.empty())
    {
        image = id.substr(2) + L".png";
    }

    auto parent = node->GetParent();
    double col = 0, row = 0;


    if (parent->GetName() == "container")
    {
        if (tagName == L"letter")
        {
            double containerLetterCol = 0;
            double containerLetterRow = 0;
            node->GetAttribute(L"col").ToDouble(&containerLetterCol);
            node->GetAttribute(L"row").ToDouble(&containerLetterRow);
            wxScopedCharBuffer valueAscii = node->GetAttribute("id").substr(2, 3).ToAscii();
            int value = int(valueAscii[0]) - 97;
            cout << int(valueAscii[0]) << endl;
            shared_ptr<Letter> letter = make_shared<Letter>(mGame, value, image);
            letter->SetLocation(containerLetterCol * mGame->GetTileHeight(), containerLetterRow * mGame->GetTileWidth());
            mGame->Add(letter);
            mGame->AddContainerLetters(letter);
        }
    }
    else
    {
        auto root = parent->GetParent();
        if (root)
        {
            auto child = root->GetChildren();
            for (; child; child = child->GetNext())
            {
                if (child->GetName() == L"items")
                {
                    auto itemsChild = child->GetChildren();
                    for (; itemsChild; itemsChild = itemsChild->GetNext())
                    {
                        if (itemsChild->GetAttribute(L"id") == id)
                        {
                            itemsChild->GetAttribute(L"col").ToDouble(&col);
                            itemsChild->GetAttribute(L"row").ToDouble(&row);

                            if(tagName == L"letter")
                            {
                                shared_ptr<Item> letter = make_shared<Letter>(mGame, value, image);
                                letter->SetLocation(col * mGame->GetTileHeight(), row * mGame->GetTileWidth());
                                mGame->Add(letter);
                            }
                            else if (tagName == L"given")
                            {
                                shared_ptr<Given> given = make_shared<Given>(mGame, value, image);
                                given->SetLocation(col * mGame->GetTileHeight(), row * mGame->GetTileWidth());
                                mGame->Add(given);
                                mGame->AddGiven(given);
                            }
                        }
                    }
                }
            }
        }
    }
}


/**
 * Loads in the player declarations and items
 * @param node xml player node
 */
void LoadLevel::PlayerNode(wxXmlNode * node)
{
    // Define the path to images
    const wstring loc = L"images/";

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
                    player->SetStartingLocation(col * mGame->GetTileHeight(),row * mGame->GetTileWidth());

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

/**
 * Loads in the Container declarations and items
 * @param node xml Node to container
 */
void LoadLevel::ContainerNode(wxXmlNode *node)
{
    const wstring loc = L"images/";

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

                    wxXmlNode* letters = itemsChild->GetChildren();

                    for(; letters; letters=letters->GetNext())
                    {
                        auto name = letters->GetAttribute("id").ToStdWstring();
                        LetterNode(letters);
                    }

                    shared_ptr<Item> presentFront = make_shared<Item>(mGame, loc + L"present-front.png", loc + L"present-front.png");
                    presentFront->SetLocation(col * mGame->GetTileWidth(), row * mGame->GetTileHeight() - 30);
                    mGame->Add(presentFront);

                }
            }
        }
    }
}