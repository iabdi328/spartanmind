/**
 * @file DeclarationPlayer.cpp
 * @author Raj Ambekar
 */

#include "DeclarationPlayer.h"
#include <wx/wxcrt.h>
DeclarationPlayer::DeclarationPlayer(LoadLevel *level) : Declaration(level)
{

}


void DeclarationPlayer::XmlLoad(wxXmlNode *node)
{
    mId = node->GetAttribute(L"id");
    mWidth = node->GetAttribute("width").ToInt(&mWidth);
    mHeight = node->GetAttribute("height").ToInt(&mHeight);
    mFront = node->GetAttribute("front").ToInt(&mFront);

    mHeadPivotAngle = node->GetAttribute("head-pivot-angle").ToDouble(&mHeadPivotAngle);
    mHeadPivotX = node->GetAttribute("head-pivot-x").ToDouble(&mHeadPivotX);
    mHeadPivotY = node->GetAttribute("head-pivot-y").ToDouble(&mHeadPivotY);

    mImage1 = node->GetAttribute("image1");
    mImage2 = node->GetAttribute("image2");

    mMouthPivotAngle = node->GetAttribute("mouth-pivot-angle").ToDouble(&mMouthPivotAngle);
    mMouthPivotX = node->GetAttribute("mouth-pivot-x").ToDouble(&mMouthPivotX);
    mMouthPivotY = node->GetAttribute("mouth-pivot-y").ToDouble(&mMouthPivotY);

    mTargetX = node->GetAttribute("target-x").ToDouble(&mTargetX);
    mTargetY = node->GetAttribute("target-y").ToDouble(&mTargetY);

}
