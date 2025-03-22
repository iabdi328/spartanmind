/**
* @file SpartanmindView.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 */


#include "pch.h"
#include "ids.h"
#include "SpartanmindView.h"
#include "Player.h"
#include "LoadLevel.h"
#include <wx/dcbuffer.h>
#include <wx/xml/xml.h>
#include <wx/wfstream.h>
#include <wx/graphics.h>
#include <memory>
#include "TrayVisitor.h"
#include <cmath>
#include <wx/tokenzr.h>
#include "Given.h"
#include <map>
#include <set>


using namespace std;

/**
 * Initialize the Spartanmind view class.
 * @param parent The parent window for this class
 */
void SpartanmindView::Initialize(wxFrame *parent)
{
    Create(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE);
    // Set the background style for smooth painting
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    // Bind our event handlers
    Bind(wxEVT_PAINT, &SpartanmindView::OnPaint, this);
    Bind(wxEVT_KEY_DOWN, &SpartanmindView::OnKeyDown, this);
    Bind(wxEVT_LEFT_DOWN, &SpartanmindView::OnMouseClick, this);


    // Bind functions from MainFrame
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanmindView::OnLevelZero, this,
                 IDM_LEVEL0);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &SpartanmindView::OnLevelOne, this,
                 IDM_LEVEL1);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,  &SpartanmindView::OnLevelTwo, this,
                 IDM_LEVEL2);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,  &SpartanmindView::OnLevelThree, this,
                 IDM_LEVEL3);

    mStopWatch.Start();
    const wxString filename = L"../levels/level1.xml";

    LoadLevel load(&mGame);
    load.Load(filename);
    mGame.ShowLevelBeginPopup(mGame.GetLevel());


    // Create & start the timer for ~60 FPS
    mGameTimer = new wxTimer(this);
    Bind(wxEVT_TIMER, &SpartanmindView::OnTimer, this);
    mGameTimer->Start(16);
}

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void SpartanmindView::OnPaint(wxPaintEvent& event)
{
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxBLACK);
    dc.SetBackground(background);
    dc.Clear();

    std::shared_ptr<wxGraphicsContext> gc(wxGraphicsContext::Create(dc));
    if (!gc) return;

    wxRect rect = GetRect();
    // 1. Draw the game world (background, scoreboard, etc.)
    mGame.Update(elapsed);
    mGame.OnDraw(gc, rect.GetWidth(), rect.GetHeight());


    TrayVisitor visitor;
    mGame.Accept(&visitor);
    bool isFull = visitor.IsFull();
    if(isFull)
    {
        double currentTime = mStopWatch.Time() * 0.001;
        double secondsSinceMessage = currentTime - mAllTime;
        if(secondsSinceMessage < 3)
        {
            mGame.FullMessage(gc);
        }
        else
        {
            // After 3 seconds, the message phase is over, so we mark it as such and move on
            isFull = false;
        }
    }

    if(mInvalidPlace)
    {
        std::cout << "invalid place" << std::endl;
        double currentTime = mStopWatch.Time() * 0.001;
        double secondsSinceMessage = currentTime - mAllTime;
        if(secondsSinceMessage < 3)
        {
            mGame.ThereMessage(gc, secondsSinceMessage);
        }
        else
        {
            // After 3 seconds, the message phase is over, so we mark it as such and move on
            mInvalidPlace = false;
        }
    }
}

/**
 * Timer event, updates the game logic and scoreboard.
 * @param event Timer event
 */
void SpartanmindView::OnTimer(wxTimerEvent& event)
{
//    if (!mGame) return;

    // Get elapsed time in milliseconds since the stopwatch was started.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;

    // Update game logic and scoreboard using the actual elapsed time.
    mGame.Update(elapsed);
    mGame.UpdateScoreboard(elapsed);

    // Move Sparty
    std::shared_ptr<Player> player(mGame.GetPlayer());

    if (player != nullptr)
    {
        player->Update(elapsed);
    }

    Refresh();
}

/**
 * Handles the mouse single click event
 * @param event mouse click
 */
void SpartanmindView::OnMouseClick(wxMouseEvent& event)
{

    // Get the clicked screen coordinates
    wxPoint pos = event.GetPosition();

    // Get player
    std::shared_ptr<Player> player(mGame.GetPlayer());
    if(event.GetX() - 60 > mGame.GetXOffset() && event.GetX() < mGame.GetXOffset()
        + mGame.GetPixelWidth() * mGame.GetScale())
    {
        if(event.GetY() - 10 > mGame.GetYOffset() && event.GetY() < mGame
            .GetYOffset() + mGame.GetPixelHeight() * mGame.GetScale())
        {
            if(player != nullptr)
            {
                player->SetLocation(pos.x, pos.y);
            }
        }

    }
}

/**
 * Key down event - handles SHIFT or SPACE keys for actions.
 * @param event Key event
 */
void SpartanmindView::OnKeyDown(wxKeyEvent& event)
{
    //    if (!mGame) return;
    auto player = mGame.GetPlayer();
    if (!player) return;

    if (event.GetKeyCode() == WXK_SHIFT)
    {
        player->Headbutt();
    }
    else if (event.GetKeyCode() == WXK_SPACE)
    {
        // if (player->GetX() > 1070 && player->GetX() < 1200)
        // {
        //     return;
        // }
        player->Eat();
        mGrabbedItem = mGame.HitTest((player->GetX() + 70),
                                     (player->GetY() + 70));
        if (mGrabbedItem == nullptr)
        {
            return;
        }
        if ((mGrabbedItem->GetX() > 1000 && mGrabbedItem->GetX() < 1300) && ((mGrabbedItem->GetY() > 500 && mGrabbedItem->GetY() < 800)))
        {
            std::cout << "you're hitting the present mate" << std::endl;
            return;
        }

        if(mGrabbedItem != nullptr)
        {
            TrayVisitor visitor2;
            TrayVisitor visitor;
            mAllTime = mStopWatch.Time() * 0.001;
            mGame.Accept(&visitor2);
            mGrabbedItem->Accept(&visitor);
            bool isLetter = visitor.IsFound();
            if(mGrabbedItem != nullptr && isLetter && !visitor2.GetTray()
                ->IsFull())
            {
                mGame.ItemToTray(mGrabbedItem);
            }
        }
    }

    // if any letter between A or Z is pressed
    if (event.GetKeyCode() >= 65 && event.GetKeyCode() <= 90 || event.GetKeyCode() == 45)
    {
        mAllTime = mStopWatch.Time() * 0.001;
        if (mGrabbedItem == nullptr)
        {
            return;
        }
        /// Get letter as its 0 indexed value (a = 0, b = 1, ...etc.)
        int letterPressed = event.GetKeyCode() - 65;
        std::shared_ptr<Item> item = mGame.HitTest(player->GetX() + 70, player->GetY() + 70);

        /// Get the location clicked as its grid value 0 indexed
        double gridPosX = floor((player->GetX() + 96) / 48);
        double gridPosY = floor((player->GetY() + 96) / 48);

        /// Print sparty location for testing
        std::cout << "Sparty Location: " << gridPosX << ", " << gridPosY << std::endl;

        /// Do eating animation
        player->Eat();

        /// Call visitor function
        TrayVisitor visitor;
        mGame.Accept(&visitor);
        std::vector<std::shared_ptr<Item>> trayItems = visitor.GetLetters();
        std::vector<std::shared_ptr<Given>> givens = mGame.GetGivens();

        int level = mGame.GetLevel();
        cout << endl << "level: " << level << endl;


        switch (level) {
            case 0:
                // if (std::find(mLevelZeroSlots.begin(), mLevelZeroSlots.end(), std::make_pair(gridPosX, gridPosY)) == mLevelZeroSlots.end()) {
                //     return;
                // }
                mGame.ResizeUserGuess(6);
                break;
            case 1:
                // if (std::find(mLevelOneSlots.begin(), mLevelOneSlots.end(), std::make_pair(gridPosX, gridPosY)) == mLevelOneSlots.end()) {
                //     return;
                // }
                mGame.ResizeUserGuess(6);
                break;
            case 2:
                // if (std::find(mLevelTwoSlots.begin(), mLevelTwoSlots.end(), std::make_pair(gridPosX, gridPosY)) == mLevelTwoSlots.end()) {
                //     return;
                // }
                mGame.ResizeUserGuess(8);
                break;
            case 3:
                // if (std::find(mLevelThreeSlots.begin(), mLevelThreeSlots.end(), std::make_pair(gridPosX, gridPosY)) == mLevelThreeSlots.end()) {
                //     return;
                // }
                mGame.ResizeUserGuess(6);
                break;
            default:
                return;
        }

        // mGame.SetUserGuess(0, 19);
        // mGame.SetUserGuess(1, 20);
        // mGame.SetUserGuess(2, 17);
        // mGame.SetUserGuess(3, 8);
        // mGame.SetUserGuess(4, 13);
        // mGame.SetUserGuess(5, 6);

        /// Create the solution and user guess variables
        vector<int> mWord = mGame.GetWord();
        vector<int> mUserGuess = mGame.GetUserGuess();

        std::cout << "Word: ";
        for (auto letter : mWord)
        {
            std::cout << letter;
        }

        std::cout << "User Guess: " << endl;
        for (auto letter : mUserGuess)
        {
            std::cout << letter;
        }

        // looping through tray items
        for(auto item : trayItems)
        {
            Letter* letter = dynamic_cast<Letter*>(item.get());
            if(letter->GetValue() == letterPressed)
            {
                if (item != nullptr)
                {
                    mInvalidPlace = true;
                    cout << endl << "Letter is already there!" << endl << endl;
                    return;
                }
                double x = player->GetX();
                double y = player->GetY();
                std::tuple<int,int> cell = mGame.Cords2Cell(x, y);
                int col = std::get<0>(cell);
                int row = std::get<1>(cell);
                if (!mGame.CellOccupied(col * mGame.GetTileHeight() + mGame
                    .GetPlayer()->GetWidth(), (row + 1) * mGame.GetTileHeight()+ mGame
                    .GetPlayer()->GetHeight()))
                {
                    mGame.RemoveTrayItems(item);

                    double x = col * mGame.GetTileHeight() + mGame
                        .GetPlayer()->GetWidth();
                    double y = (row + 1) * mGame.GetTileHeight()+ mGame
                        .GetPlayer()->GetHeight();
                    cout << "level: " << level << endl;
                    switch (level)
                    {
                        case 0:
                        {
                            for (auto item : givens)
                            {
                                cout << endl << "item" << endl;
                                double givenPosX= floor(((*item).GetX() + 96) / 48) - 2;
                                double givenPosY = floor(((*item).GetY() + 96) / 48) - 2;
                                int givenValue = (*item).GetValue();
                                cout << endl << "givenValue: " << givenValue << endl;
                                cout << endl << "givenPosX: " << givenPosX << endl;
                                cout << endl << "givenPosY: " << givenPosY << endl;
                                auto index = std::find(mLevelZeroSlots.begin(), mLevelZeroSlots.end(), std::make_pair(givenPosX, givenPosY));
                                if (index != mLevelZeroSlots.end())
                                {
                                    std::cout << "distance: " << std::distance(mLevelZeroSlots.begin(), index) << std::endl;
                                    mGame.SetUserGuess(std::distance(mLevelZeroSlots.begin(), index), givenValue);
                                } else
                                {
                                    std::cout << "This is not a valid location!" << std::endl;
                                }

                                cout << "Given value x: " << givenPosX << endl;
                                cout << "Given value y: " << givenPosY << endl;
                            }
                            for (auto item : givens)
                            {
                                double givenPosX= floor(((*item).GetX() + 96) / 48);
                                double givenPosY = floor(((*item).GetY() + 96) / 48);
                                int givenValue = (*item).GetValue();
                                auto index = std::find(mLevelZeroSlots.begin(), mLevelZeroSlots.end(), std::make_pair(givenPosX, givenPosY));
                                if (index != mLevelZeroSlots.end())
                                {
                                    // std::cout << std::distance(mLevelZeroSlots.begin(), index) << std::endl;
                                    mGame.SetUserGuess(std::distance(mLevelZeroSlots.begin(), index), givenValue);
                                } else
                                {
                                    std::cout << "This is not a valid location!" << std::endl;
                                }

                                cout << "Given value x: " << givenPosX << endl;
                                cout << "Given value y: " << givenPosY << endl;
                            }
                            auto index = std::find(mLevelZeroSlots.begin(), mLevelZeroSlots.end(), std::make_pair(gridPosX, gridPosY));
                            if (index != mLevelZeroSlots.end())
                            {
                                // std::cout << std::distance(mLevelZeroSlots.begin(), index) << std::endl;
                                mGame.SetUserGuess(std::distance(mLevelZeroSlots.begin(), index), letterPressed);
                            } else
                            {
                                std::cout << "This is not a valid location!" << std::endl;
                            }
                        }
                            break;
                        case 1:
                        {
                            for (auto item : givens)
                            {
                                cout << endl << "item" << endl;
                                double givenPosX= floor(((*item).GetX() + 96) / 48) - 2;
                                double givenPosY = floor(((*item).GetY() + 96) / 48) - 2;
                                int givenValue = (*item).GetValue();
                                cout << endl << "givenValue: " << givenValue << endl;
                                cout << endl << "givenPosX: " << givenPosX << endl;
                                cout << endl << "givenPosY: " << givenPosY << endl;
                                auto index = std::find(mLevelOneSlots.begin(), mLevelOneSlots.end(), std::make_pair(givenPosX, givenPosY));
                                if (index != mLevelOneSlots.end())
                                {
                                    std::cout << "distance: " << std::distance(mLevelOneSlots.begin(), index) << std::endl;
                                    mGame.SetUserGuess(std::distance(mLevelOneSlots.begin(), index), givenValue);
                                } else
                                {
                                    std::cout << "This is not a valid location!" << std::endl;
                                }

                                cout << "Given value x: " << givenPosX << endl;
                                cout << "Given value y: " << givenPosY << endl;
                            }
                            auto index = std::find(mLevelOneSlots.begin(), mLevelOneSlots.end(), std::make_pair(gridPosX, gridPosY));
                            if (index != mLevelOneSlots.end())
                            {
                                // std::cout << std::distance(mLevelOneSlots.begin(), index) << std::endl;
                                mGame.SetUserGuess(std::distance(mLevelOneSlots.begin(), index), letterPressed);
                            } else
                            {
                                std::cout << "This is not a valid location!" << std::endl;
                            }
                        }
                            break;
                        case 2:
                        {
                            for (auto item : givens)
                            {
                                cout << endl << "item" << endl;
                                double givenPosX = floor(((*item).GetX() + 96) / 48) - 2;
                                double givenPosY = floor(((*item).GetY() + 96) / 48) - 2;
                                int givenValue = (*item).GetValue();
                                cout << endl << "givenValue: " << givenValue << endl;
                                cout << endl << "givenPosX: " << givenPosX << endl;
                                cout << endl << "givenPosY: " << givenPosY << endl;
                                auto index = std::find(mLevelTwoSlots.begin(), mLevelTwoSlots.end(), std::make_pair(givenPosX, givenPosY));
                                if (index != mLevelTwoSlots.end())
                                {
                                    std::cout << "distance: " << std::distance(mLevelTwoSlots.begin(), index) << std::endl;
                                    mGame.SetUserGuess(std::distance(mLevelTwoSlots.begin(), index), givenValue);
                                }
                                else
                                {
                                    std::cout << "This is not a valid location!" << std::endl;
                                }

                                cout << "Given value x: " << givenPosX << endl;
                                cout << "Given value y: " << givenPosY << endl;
                            }
                            auto index = std::find(mLevelTwoSlots.begin(), mLevelTwoSlots.end(), std::make_pair(gridPosX, gridPosY));
                            if (index != mLevelTwoSlots.end())
                            {
                                mGame.SetUserGuess(std::distance(mLevelTwoSlots.begin(), index), letterPressed);
                            }
                            else
                            {
                                std::cout << "This is not a valid location!" << std::endl;
                            }
                        }
                            break;
                        case 3:
                        {
                            for (auto item : givens)
                            {
                                cout << endl << "item" << endl;
                                double givenPosX= floor(((*item).GetX() + 96) / 48) - 2;
                                double givenPosY = floor(((*item).GetY() + 96) / 48) - 2;
                                int givenValue = (*item).GetValue();
                                cout << endl << "givenValue: " << givenValue << endl;
                                cout << endl << "givenPosX: " << givenPosX << endl;
                                cout << endl << "givenPosY: " << givenPosY << endl;
                                auto index = std::find(mLevelThreeSlots.begin(), mLevelThreeSlots.end(), std::make_pair(givenPosX, givenPosY));
                                if (index != mLevelThreeSlots.end())
                                {
                                    std::cout << "distance: " << std::distance(mLevelThreeSlots.begin(), index) << std::endl;
                                    mGame.SetUserGuess(std::distance(mLevelThreeSlots.begin(), index), givenValue);
                                } else
                                {
                                    std::cout << "This is not a valid location!" << std::endl;
                                }
                            }
                            auto index = std::find(mLevelThreeSlots.begin(), mLevelThreeSlots.end(), std::make_pair(gridPosX, gridPosY));
                            if (index != mLevelThreeSlots.end())
                            {
                                // std::cout << std::distance(mLevelThreeSlots.begin(), index) << std::endl;
                                mGame.SetUserGuess(std::distance(mLevelThreeSlots.begin(), index), letterPressed);
                            } else
                            {
                                std::cout << "This is not a valid location!" << std::endl;
                            }
                        }
                            break;
                        default:
                            return;
                    }

                    letter->SetLocation(gridPosX * 48, gridPosY * 48);
                    mUserGuess = mGame.GetUserGuess();
                    std::cout << endl;
                    cout << "User Guess: ";
                    for (auto letter : mUserGuess)
                    {
                        std::cout << letter;
                    }
                    cout << endl;
                    if (mWord == mUserGuess)
                    {
                        std::cout << "You Win!" << std::endl;
                        LoadNextLevel();
                    }
                    break;
                }
            }
        }
    }

    event.Skip(); // Let other key events process
}

/**
 * Event handler for selecting Level Zero.
 * Loads the first level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelZero(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level0.xml";
    NewLevel(filename, 0);

}


/**
 * Event handler for selecting Level One.
 * Loads the first level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelOne(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level1.xml";
    NewLevel(filename, 1);
}

/**
 * Event handler for selecting Level Two.
 * Loads the second level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelTwo(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level2.xml";
    NewLevel(filename, 2);
}

/**
 * Event handler for selecting Level Three.
 * Loads the third level of the game.
 *
 * @param event Command event object.
 */
void SpartanmindView::OnLevelThree(wxCommandEvent& event)
{
    const wxString filename = L"../levels/level3.xml";
    NewLevel(filename, 3);

}

/**
 * Loads in new level
 * @param filename level xml file
 * @param levelNumber number of level
 */
void SpartanmindView::NewLevel(const wxString& filename, int levelNumber)
{
    mGame.ResetScoreboard();
    mStopWatch.Start();
    mTime = 0;

    mGame.Clear();
    mGameIsActive = false;
    mNewLevel = true;

    mGame.SetLevel(levelNumber);

    LoadLevel area(&mGame);
    area.Load(filename);

    mGame.ShowLevelBeginPopup(levelNumber);
}

/**
 * Loads in the next level on game completion
 */
void SpartanmindView::LoadNextLevel()
{
    // current level number
    int currLevel = mGame.GetLevel();

    // next level number
    int nextLevel = currLevel + 1;

    // Load the new level directly without using events
    wxString filename;
    switch (nextLevel)
    {
        case 1:
            filename = L"../levels/level1.xml";
            NewLevel(filename, 1);
            break;
        case 2:
            filename = L"../levels/level2.xml";
            NewLevel(filename, 2);
            break;
        case 3:
            filename = L"../levels/level3.xml";
            NewLevel(filename, 3);
            break;
        default:
            break;
    }

}

/**
 * Remove 10 seconds from the game level3 feature
 */
void SpartanmindView::Remove10Seconds()
{
    mGame.SubtractTimeFromScoreboard(10.0);
    Refresh();
    Update();
}

/**
 * Destructor for the gameview
 */
SpartanmindView::~SpartanmindView()
{
    if (mGameTimer)
    {
        mGameTimer->Stop();
        delete mGameTimer;
        mGameTimer = nullptr;
    }
}

/**
 * Solve the game
 */
void SpartanmindView::OnSolveGame()
{

    auto solution = mGame.GetWord();
    if (solution.empty()) {
        return;
    }

    std::vector<std::pair<int, int>> slots;
    switch (mGame.GetLevel()) {
        case 0: slots = mLevelZeroSlots; break;
        case 1: slots = mLevelOneSlots; break;
        case 2: slots = mLevelTwoSlots; break;
        case 3: slots = mLevelThreeSlots; break;
    }

    if (slots.size() != solution.size()) {
        return;
    }

    // Step 1: Track "givens" so we don't touch them
    std::map<std::pair<int, int>, int> givenMap;
    for (auto& given : mGame.GetGivens()) {
        int col = static_cast<int>((given->GetX() + 96) / 48) - 2;
        int row = static_cast<int>((given->GetY() + 96) / 48) - 2;
        givenMap[{col, row}] = given->GetValue();
    }

    // Step 2: Build a letter pool (value -> items)
    std::multimap<int, std::shared_ptr<Item>> letterPool;
    std::set<std::shared_ptr<Item>> used;

    auto allItems = mGame.GetAllItems();
    for (auto& item : allItems) {
        if (item && item->IsLetter()) {
            letterPool.emplace(item->GetValue(), item);
        }
    }

    mGame.ResizeUserGuess(solution.size());

    // Step 3: Place each letter
    for (size_t i = 0; i < solution.size(); ++i)
    {
        auto [col, row] = slots[i];
        int targetValue = solution[i];

        // Skip if it's a "given" slot
        if (givenMap.find({col, row}) != givenMap.end()) {
            mGame.SetUserGuess(i, targetValue);
            continue;
        }

        // Remove anything already in the slot
        auto existing = mGame.GetItems(col * 48, row * 48);
        if (existing && existing->IsLetter()) {
            mGame.ItemToTray(existing);
        }

        // Find a letter that matches and isn't used
        auto range = letterPool.equal_range(targetValue);
        bool placed = false;
        for (auto it = range.first; it != range.second; ++it) {
            auto& letter = it->second;
            if (!letter || used.count(letter)) continue;

            // Force it onto the board
            mGame.ItemToTray(letter);        // detach from container or slot
            mGame.RemoveTrayItems(letter);   // detach from tray
            letter->SetLocation(col * 48, row * 48);
            mGame.SetUserGuess(i, targetValue);
            used.insert(letter);
            placed = true;
            break;
        }

    }
}