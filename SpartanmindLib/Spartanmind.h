/**
 * @file Spartanmind.h
 * @author Raj Ambekar, Emmanuel Koshy
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
#include "Letter.h"
#include "Given.h"
#include "Player.h"

class Sparty;
class Chest;

/**
 * Detailing the General Base App
 */
class Spartanmind
{
private:
    /// Background image to use
    std::unique_ptr<wxBitmap> mBackground;
    std::vector<Letter*> mLetters;
    std::vector<Given*> mGivens;
    Sparty* mPlayer;
    Chest* mChestPlayer;

public:
    Spartanmind();
    ~Spartanmind();
    Sparty* GetPlayer() { return mPlayer; }  // Getter for Sparty
    Chest* GetChest() { return mChestPlayer; }

    void OnDraw(wxDC *dc);
    void Update(double elapsedTime);

    void SetBackground(const wxString& imagePath);
    std::vector<Letter*> GetLetters() { return mLetters; }
    std::vector<Given*> GetGivens() { return mGivens; }
    void AddLetter(Letter* letter);
    void ClearLetters();
    void AddGiven(Given* given);
    void ClearGivens();
    std::shared_ptr<Player> CreatePlayer(int level);
};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
