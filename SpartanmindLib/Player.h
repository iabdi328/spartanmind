/**
 * @file Player.h
 * @author  Emmanuel Koshy, Raj Ambekar
 *
 * Player class defines Sparty and Chest
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Item.h"
#include <wx/geometry.h>
#include <string>
#include <wx/graphics.h>

class Game;

/**
 * Player class defines Sparty and Chest
 */
class Player : public Item {
private:
    /// Game
    Game* mGameWorld;

    /// Current position of the player
    wxPoint2DDouble mLocation;
    /// Target position of the player
    wxPoint2DDouble mTarget;

    /// Movement speed in pixels per second
    const double MaxSpeed = 400.0;

    /// Is player eating?
    bool mEating = false;
    /// Is player moving?
    bool mMoving = false;
    /// Is player headbutting?
    bool mHeadbutt = false;

    /// How long has player been eating?
    double mEatingTimer = 0;
    /// How long has player been headbutting?
    double mHeadbuttTimer = 0;

    /// Direction of player
    double mDirection = 0;
    /// Speed of player
    double mSpeed;

    std::wstring mImage1; ///< Image files for the player body
    std::wstring mImage2; ///< Image files for the player mouth/lid
    std::unique_ptr<wxBitmap> mPlayerImage; ///< The bitmap we can display for player
    std::unique_ptr<wxBitmap> mMouthImage; ///< The bitmap we can display for player mouth/lid

    // Target offsets (from XML attributes)
    double mTargetXOffset = 0; ///< Offset for Target X position
    double mTargetYOffset = 0; ///< Offset for Target Y position

    /// X location of player
    double mX = 0;
    /// Y location of player
    double mY = 0;
    /// X destination of sparty given
    double mDestX = 0;
    /// Y destination of party given
    double mDestY = 0;
    /// X direction of sparty
    double mDirectionX = 0;
    /// Y direction of sparty
    double mDirectionY = 0;
    /// width of sparty
    double wid = 96;
    /// height of sparty
    double hit = 96;

    wxPoint2DDouble mBasePivot;  ///< Base pivot for headbutt rotation
    double mBaseAngle = 0;  ///< Headbutt angle

    wxPoint2DDouble mAuxPivot;  ///< Auxiliary pivot for the mouth or lid animation
    double mAuxAngle = 0;   ///< Auxiliary angle

    /// Pivot angle of sparty
    double mHeadPivotAngle= 0.8;
    /// X Pivot point of head
    double mHeadPivotX= 30;
    /// Y Pivot point of head
    double mHeadPivotY= 86;
    /// Pivot angle of mouth
    double mMouthPivotAngle= 1;

    /// Target X location of sparty
    double mTargetX= 72;
    /// Target Y location of sparty
    double mTargetY= 24;

    double mMouthPivotX= 90; ///< Pivot point of mouth (X)
    double mMouthPivotY= 7; ///< Pivot point of mouth (Y)

    double mHeadAngle = 0;     ///< Head rotation angle for headbutt
    double mMouthAngle = 0.5;    ///< Angle for mouth rotation (eating)

    const double HeadbuttDuration = 0.5; ///< Headbutt duration (seconds)
    const double HeadbuttAngle = 0.5; ///< Max angle for headbutt

    const double EatingDuration = 0.5;  ///< Eating lasts 0.5s
    const double EatingAngle = 1;  ///< Max mouth open angle

public:
    Player(Game *game, std::wstring headImage, std::wstring mouthImage);
    virtual ~Player() {}

    void SetLocation(double x, double y) override;
    void Update(double elapsedTime) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    void Eat();
    void Headbutt();
    wxRealPoint ComputePosition();

    void SetPosition(double x, double y);
    void SetStartingLocation(double x, double y);

    double GetX() const { return mX; }

    /**
     * Get Y
     * @return mY
     */
    double GetY() const { return mY; }
    /**
     * Get Width
     * @return Mouth image width
     */
    int GetWidth(){return mMouthImage->GetWidth();}

    /**
     * Get Height
     * @return Mouth image height
     */
    int GetHeight(){return mMouthImage->GetHeight();}

    /**
     * Set Head Pivot Angle
     * @param angle
     */
    void SetHeadPivotAngle(double angle) { mHeadPivotAngle = angle; }

    /**
     * Set Head Pivot X
     * @param x
     */
    void SetHeadPivotX(double x) { mHeadPivotX = x; }

    /**
     * Set Head Pivot Y
     * @param y
     */
    void SetHeadPivotY(double y) { mHeadPivotY = y; }
    /**
     * Set Mouth Pivot Angle
     * @param angle
     */
    void SetMouthPivotAngle(double angle) { mMouthPivotAngle = angle; }

    /**
     * Set Mouth Pivot X
     * @param x
     */
    void SetMouthPivotX(double x) { mMouthPivotX = x; }

    /**
     * Set Mouth Pivot Y
     * @param y
     */
    void SetMouthPivotY(double y) { mMouthPivotY = y; }

    /**
     * Set Target X
     * @param x
     */
    void SetTargetX(double x) { mTargetX = x; }

    /**
     * Set Target Y
     * @param y
     */
    void SetTargetY(double y) { mTargetY = y; }

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(ItemVisitor* visitor) override { visitor->VisitPlayer(this); }
};

#endif // PLAYER_H
