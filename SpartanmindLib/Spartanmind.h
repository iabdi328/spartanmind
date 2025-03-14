/**
 * @file Spartanmind.h
 * @author Raj Ambekar, Emmanuel Koshy
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
#include "Given.h"

class Letter;
class Sparty;

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

public:
    Spartanmind();
    ~Spartanmind();
    Sparty* GetPlayer() { return mPlayer; }  // Getter for Sparty

    void OnDraw(wxDC *dc);
    void Update(double elapsedTime);

    void SetBackground(const wxString& imagePath);
    std::vector<Letter*> GetLetters() { return mLetters; }
    std::vector<Given*> GetGivens() { return mGivens; }
    void AddLetter(Letter* letter);
    void ClearLetters();
    void AddGiven(Given* given);
    void ClearGivens();
};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
