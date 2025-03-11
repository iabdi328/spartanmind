/**
 * @file Spartanmind.h
 * @author Raj Ambekar, Emmanuel Koshy
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMIND_H

class Sparty;

/**
 * Detailing the General Base App
 */
class Spartanmind
{
private:
    /// Background image to use
    std::unique_ptr<wxBitmap> mBackground;

    Sparty* mPlayer;

public:
    Spartanmind();
    ~Spartanmind();
    Sparty* GetPlayer() { return mPlayer; }  // Getter for Sparty

    void OnDraw(wxDC *dc);
    void Update(double elapsedTime);

    void SetBackground(const wxString& imagePath);

};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
