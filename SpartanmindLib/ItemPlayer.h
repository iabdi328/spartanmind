/**
 * @file ItemPlayer.h
 * @author Raj Ambekar
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_ITEMPLAYER_H
#define PROJECT1_SPARTANMINDLIB_ITEMPLAYER_H

#include "Item.h"
#include "DeclarationPlayer.h"

class ItemPlayer : public Item
{
private:
    DeclarationPlayer *mDeclarationPlayer;

    const double MaxSpeed = 400.0;
    const double GrabbingTime = 0.5;
    const double HeadbuttTime = 0.5;

    wxString mHeadImageName;
    wxString mMouthImageName;
    std::shared_ptr<wxImage> mImageHead;
    std::shared_ptr<wxImage> mImageMouth;
    std::unique_ptr<wxBitmap> mBitmapHead;
    std::unique_ptr<wxBitmap> mBitmapMouth;

    wxPoint2DDouble mLocation;
    wxPoint2DDouble mTarget;


    double mX = 0;
    double mY = 0;
    double mSpeedX = 0;
    double mSpeedY = 0;
    double mTargetX = 0;
    double mTargetY = 0;

    wxPoint2DDouble mMouthPivot;
    wxPoint2DDouble mBasePivot;

public:
    ItemPlayer(LoadLevel *level);
    void XmlLoad(wxXmlNode* node) override;
    void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    void Update(double elapsedTime) override;

};

#endif //PROJECT1_SPARTANMINDLIB_ITEMPLAYER_H
