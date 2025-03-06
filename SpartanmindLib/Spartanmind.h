/**
 * @file Spartanmind.h
 * @author Raj Ambekar
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
#define PROJECT1_SPARTANMINDLIB_SPARTANMIND_H

/**
 * Detailing the General Base App
 */
class Spartanmind
{
private:
    /// Background image to use
    std::unique_ptr<wxBitmap> mBackground;

public:
    Spartanmind();
    void OnDraw(wxDC *dc);

};

#endif //PROJECT1_SPARTANMINDLIB_SPARTANMIND_H
