/**
 * @file DeclarationPlayer.h
 * @author Raj Ambekar
 *
 *
 */

#ifndef PROJECT1_SPARTANMINDLIB_DECLARATIONPLAYER_H
#define PROJECT1_SPARTANMINDLIB_DECLARATIONPLAYER_H

#include "Declaration.h"

class DeclarationPlayer : public Declaration
{
private:
    wxString mId;
    int mWidth = 0;
    int mHeight = 0;
    int mFront = 0;
    double mHeadPivotAngle = 0.0;
    double mHeadPivotX = 0.0;
    double mHeadPivotY = 0.0;
    wxString mImage1;
    wxString mImage2;
    double mMouthPivotAngle = 0.0;
    double mMouthPivotX = 0.0;
    double mMouthPivotY = 0.0;
    double mTargetX = 0.0;
    double mTargetY = 0.0;

public:
    DeclarationPlayer(LoadLevel *level);
    void XmlLoad(wxXmlNode* node) override;

    wxString GetImageHeadName() const { return mImage1; }
    wxString GetImageMouthName() const { return mImage2; }

};

#endif //PROJECT1_SPARTANMINDLIB_DECLARATIONPLAYER_H
