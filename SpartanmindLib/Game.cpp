/**
 * @file Game.cpp
 * @author Raj Ambekar, Ismail Abdi, Emmanuel Koshy
 *
 */

#include "pch.h"
#include "Game.h"
#include "Player.h"
#include <algorithm>
#include <wx/log.h>
#include <wx/graphics.h>
#include <wx/tokenzr.h>
#include "Item.h"
#include "PopUps.h"
#include "TrayVisitor.h"
#include <cstdlib>  // For rand()
using namespace std;


/**
 * Game Constructor
 */
Game::Game()
{
    mBackground = std::make_unique<wxBitmap>(L"images/background.png", wxBITMAP_TYPE_ANY);
}

/**
 * Update game view
 * @param deltaSeconds time
 */
void Game::Update(double deltaSeconds) {
    UpdateScoreboard(deltaSeconds);
    mPopUps.Update(deltaSeconds);
    if (mPlayer != nullptr) {
        mPlayer->Update(deltaSeconds);
    }
    for (auto item : mItems)
    {
        item->Update(deltaSeconds);
    }
}

/**
 * Sets the virtual dimensions for items
 * @param virtualWidth
 * @param virtualHeight
 */
void Game::SetVirtualDimensions(int virtualWidth, int virtualHeight) {
    mVirtualWidth = virtualWidth;
    mVirtualHeight = virtualHeight;
}

/**
 * Draw the game context
 * @param gc context
 * @param width of game
 * @param height of game
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> gc, int width, int height) {

    int pixelWidth =  mWidth * mTileWidth;
    int pixelHeight = mHeight * mTileHeight;

    // Automatic Scaling
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    gc->PushState();

    gc->Translate(mXOffset, mYOffset);
    gc->Scale(mScale, mScale);

    //
    // Draw in virtual pixels on the graphics context
    //
    if (!mBackground->IsNull())
    {
        // I am not sure what needs to be done with pixelWidth and pixelHeight.
        // I think this is taken care in the Load function.
        gc->DrawBitmap(*mBackground, 0, 0, pixelWidth, pixelHeight);
    }

    // drawing scoreboard and each item for the game

    mScoreboard.Draw(gc);

    for (auto item : mItems)
    {
        item->Draw(gc);
    }

    mPlayer->Draw(gc);

    mPopUps.Draw(gc, width, height);

    gc->PopState();
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}


/**
 * Update the scoreboard
 * @param deltaSeconds
 */
void Game::UpdateScoreboard(double deltaSeconds) {
    mScoreboard.Update(deltaSeconds);
}

/**
 * Add items to item list
 * @param item
 */
void Game::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

/**
 * Appends to the word solution list
 * @param number the letter
 */
void Game::AddAnswer(int number)
{
    mWord.push_back(number);
}

/**
 * Remove all items when loading new level
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * Class to display pop up on new level
 * @param levelNumber int level
 */
void Game::ShowLevelBeginPopup(int levelNumber)
{
    std::wstring message = L"Level " + std::to_wstring(levelNumber) + L" Begins!";
    mPopUps.ShowPopup(message, 1.0);
}

std::shared_ptr<Item> Game::GetItems(double mX, double mY)
{
    cout << "x: " << mX << endl;
    cout << "y: " << mY << endl;
    mX += 96;
    mY += 96;
    for (auto item : mItems)
    {
        double itemX = item->GetX();
        double itemY = item->GetY();
        double itemWidth = 48;
        double itemHeight = 48;

        if ((mX >= itemX) && (mX <= itemX + itemWidth) && (mY >= itemY) && (mY <= itemY + itemHeight))
        {
            cout << "Item Location: (" << itemX << ", " << itemY << ")" << endl;
            return item;
        }
    }
    // std::cout << "this is not the issue" << std::endl;
    return nullptr;
}

/**
 * visitor for item collection
 * @param *visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor *visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

/**
 * Moves the letter items to the tray
 * @param item smart pointer
 */
void Game::ItemToTray(std::shared_ptr<Item> item)
{
    auto loc = find(std::begin(mItems), std::end(mItems), item);
    if (loc != std::end(mItems))
    {
        mItems.erase(loc);
    }
    TrayVisitor visitor;
    this->Accept(&visitor);
    if(visitor.GetTray() != nullptr ){
        visitor.GetTray()->Add(item);
    }
}

/**
 * Removes the item from the tray
 * @param item smart pointer
 */
void Game::RemoveTrayItems(std::shared_ptr<Item> item)
{
    TrayVisitor visitor;
    this->Accept(&visitor);
    if(visitor.GetTray() != nullptr){
        visitor.GetTray()->Remove(item);
    }
    Add(item);
}

/**
 * Reset Scoreboard on new level to 0
 */
void Game::ResetScoreboard() {
    mScoreboard.Reset();
}

/**
 * Message for when tray is full
 * @param graphics
 */
void Game::FullMessage(std::shared_ptr<wxGraphicsContext> graphics)
{
    // Constants for easier adjustments
    const int rectWidth = 400, rectHeight = 150, rectX = (mWidth * mTileWidth - rectWidth) / 2, rectY = (mHeight * mTileHeight - rectHeight) / 2;;
    const int levelFontSize = 80, instructionFontSize = 35;
    const double spacing = 10;  // Adjust this to change spacing between instruction lines

    // Draw a filled rectangle
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    graphics->DrawRectangle(rectX, rectY, rectWidth, rectHeight);

    // Function to simplify text drawing
    auto drawTextCentered = [&](const wxString& text, int fontSize, const wxColour& color) {
        wxFont font(fontSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, color);

        double textWidth, textHeight;
        graphics->GetTextExtent(text, &textWidth, &textHeight);

        double xPos = rectX + (rectWidth - textWidth) / 2;  // Centered horizontally
        double yPos = rectY + (rectHeight - textHeight) / 2;  // Centered vertically

        graphics->DrawText(text, xPos, yPos);  // Draw the text
    };

    // Draw instructions with adjusted spacing and checking for overflow
    wxStringTokenizer tokenizer("I'm Full", "\n");
    while (tokenizer.HasMoreTokens()) {
        wxString instruction = tokenizer.GetNextToken();
        drawTextCentered(instruction, instructionFontSize, *wxBLACK);
    }
}

/**
 * Message for when tray is full
 * @param graphics
 */
void Game::ThereMessage(std::shared_ptr<wxGraphicsContext> graphics, double currentTime)
{
    std::cout << "ThereMessage" << std::endl;
    std::cout << currentTime << std::endl;
    double movingY =  (currentTime * 600);
    int startingY = 800 - movingY;
    // Constants for easier adjustments
    const int rectWidth = 600, rectHeight = 50, rectX = (mWidth * mTileWidth - rectWidth) / 2, rectY = startingY;;
    const int levelFontSize = 80, instructionFontSize = 35;
    const double spacing = 10;  // Adjust this to change spacing between instruction lines

    // Draw a filled rectangle
    graphics->SetBrush(*wxBLACK_BRUSH);
    graphics->DrawRectangle(rectX - 10, rectY - 10, rectWidth + 20, rectHeight + 20);
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    graphics->DrawRectangle(rectX, rectY, rectWidth, rectHeight);

    // Function to simplify text drawing
    auto drawTextCentered = [&](const wxString& text, int fontSize, const wxColour& color) {
        wxFont font(fontSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, color);

        double textWidth, textHeight;
        graphics->GetTextExtent(text, &textWidth, &textHeight);

        double xPos = rectX + (rectWidth - textWidth) / 2;  // Centered horizontally
        double yPos = startingY;  // Centered vertically

        graphics->DrawText(text, xPos, yPos);  // Draw the text
    };

    // Draw instructions with adjusted spacing and checking for overflow
    wxStringTokenizer tokenizer("Something is already there!", "\n");
    while (tokenizer.HasMoreTokens()) {
        wxString instruction = tokenizer.GetNextToken();
        drawTextCentered(instruction, instructionFontSize, *wxRED);
    }
}

void Game::CheckSolutionPopup(std::shared_ptr<wxGraphicsContext> graphics, double currentTime, int matched, int existing)
{
    // Constants for easier adjustments
    const int rectWidth = 400, rectHeight = 300, rectX = (mWidth * mTileWidth - rectWidth) / 2, rectY = (mHeight * mTileHeight - rectHeight) / 2;
    const int levelFontSize = 80, instructionFontSize = 35;
    const double spacing = 10;  // Adjust this to change spacing between instruction lines

    // Draw a filled rectangle
    graphics->SetBrush(*wxWHITE_BRUSH);
    graphics->SetPen(*wxTRANSPARENT_PEN);
    graphics->DrawRectangle(rectX, rectY, rectWidth, rectHeight);

    // Function to simplify text drawing
    auto drawTextCentered = [&](const wxString& text, int fontSize, const wxColour& color, double& yPos) {
        wxFont font(fontSize, wxFONTFAMILY_SWISS, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);
        graphics->SetFont(font, color);

        double textWidth, textHeight;
        graphics->GetTextExtent(text, &textWidth, &textHeight);

        double xPos = rectX + (rectWidth - textWidth) / 2;  // Centered horizontally

        graphics->DrawText(text, xPos, yPos);  // Draw the text

        // Move yPos down for the next line
        yPos += textHeight + spacing;
    };

    // Draw "Incorrect!" text first
    double yPos = rectY + (rectHeight - instructionFontSize) / 2;  // Start from the center
    wxStringTokenizer tokenizer("You're incorrect!", "\n");
    while (tokenizer.HasMoreTokens()) {
        wxString instruction = tokenizer.GetNextToken();
        drawTextCentered(instruction, instructionFontSize, *wxBLACK, yPos);
    }

    // Draw "Matched letters: " below "You're incorrect!"
    wxString matchedLettersText = wxString::Format("Matched letters: %d", matched);
    drawTextCentered(matchedLettersText, instructionFontSize, *wxBLACK, yPos);

    // Draw "Existing letters: " below "Matched letters: "
    wxString existingLettersText = wxString::Format("Existing letters: %d", existing);
    drawTextCentered(existingLettersText, instructionFontSize, *wxBLACK, yPos);
}

/**
 * Game coordinates
 * @param x position
 * @param y position
 * @return tuple
 */
std::tuple<int,int> Game::Cords2Cell(double x, double y){
    int col = std::floor((x / mTileWidth));
    int row = std::floor((y / mTileHeight));
    return std::make_tuple(col, row);
}

/**
 * See if the cell already has a letter
 * @param x position
 * @param y position
 * @return true if yes else false
 */
bool Game::CellOccupied(double x, double y){
    for (auto item : mItems)
    {
        if (item->GetX() == x && item->GetY() == y)
        {
            std::cout << "Found in cell Row: " << x << " Col: " << y << std::endl;
            return true;
        }
    }
    return false;
}

/**
 * Subtract time for level3 feature
 * @param seconds time
 */
void Game::SubtractTimeFromScoreboard(double seconds)
{
    mScoreboard.SubtractTime(seconds);
}

/**
 * Add letters to the container
 * @param letter smart pointer
 */
void Game::AddContainerLetters(std::shared_ptr<Letter> letter)
{
    cout << "Pushed back: " << letter << endl;
    mContainerLetters.push_back(letter);
}

/**
 * Scatters letters when present is headbutted
 */
void Game::ScatterLetters()
{
    for (auto item : mContainerLetters)
    {
        int randomX = 1050 + std::rand() % (1300 - 1050);
        int randomY = 200 + std::rand() % (417 - 162);
        item->SetLocation(randomX, randomY);
    }
}