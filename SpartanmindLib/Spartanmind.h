/**
 * @file Spartanmind.h
 * @author Raj Ambekar, Emmanuel Koshy
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMIND_H

#include "Given.h"
#include "Tray.h"
#include "Container.h"

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
    std::vector<Tray*> mTray;
    std::vector<Container*> mContainer;
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
    std::vector<Tray*> GetTray() { return mTray; }
    std::vector<Container*> GetContainer() { return mContainer; }
    void AddLetter(Letter* letter);
    void ClearLetters();
    void AddGiven(Given* given);
    void ClearGivens();
    void AddTray(Tray* tray);
    void ClearTrays();
    void AddContainer(Container* container);
    void ClearContainers();
};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
