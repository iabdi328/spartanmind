/**
 * @file ItemPlayer.cpp
 * @author Raj Ambekar
 */

#include "pch.h"
#include "ItemPlayer.h"
#include "LoadLevel.h"

const double MaxSpeed = 400.0;
const double GrabbingTime = 0.5;
const double HeadbuttTime = 0.5;


ItemPlayer::ItemPlayer(LoadLevel *level) : Item(level)
{

}

void ItemPlayer::XmlLoad(wxXmlNode *node)
{
    double col = wxAtof(node->GetAttribute("col"));
    double row = wxAtof(node->GetAttribute("row"));

    mX = col * (mLevel->GetTileWidth());
    mY = row * (mLevel->GetTileHeight());

    mTargetX = mX;
    mTargetY = mY;

    SetLocation(mTargetX, mTargetY);

}

void ItemPlayer::Draw(std::shared_ptr<wxGraphicsContext> graphics)
{
    if (mImageHead == nullptr || mImageMouth == nullptr)
    {
        wxString headFileName = mDeclarationPlayer->GetImageHeadName();
        wxString mouthFileName = mDeclarationPlayer->GetImageMouthName();

        wxString resources = L"resources/images/";

        wxString headImageFile = resources + headFileName;
        wxString mouthImageFile = resources + mouthFileName;

        mImageHead = std::make_unique<wxImage>(headImageFile, wxBITMAP_TYPE_ANY);
        mBitmapHead = std::make_unique<wxBitmap>(*mImageHead);

        mImageMouth = std::make_unique<wxImage>(mouthImageFile, wxBITMAP_TYPE_ANY);
        mBitmapMouth = std::make_unique<wxBitmap>(*mImageHead);
    }


    int headWid = mImageHead->GetWidth();
    int headHit = mImageHead->GetHeight();
    int mouthWid = mImageMouth->GetWidth();
    int mouthHit = mImageMouth->GetHeight();

    int pixelX = mCol * mLevel->GetTileWidth();
    int pixelY = mRow * mLevel->GetTileHeight();

    graphics->DrawBitmap(*mBitmapHead, pixelX, pixelY, headWid, headHit);
    graphics->DrawBitmap(*mBitmapMouth, pixelX, pixelY, mouthWid, mouthHit);


}

void ItemPlayer::Update(double elapsedTime)
{

}


