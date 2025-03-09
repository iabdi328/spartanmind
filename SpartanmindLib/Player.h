/**
 * @file Player.h
 * @author Emmanuel Koshy
 *
 *
 */
 
#ifndef PLAYER_H
#define PLAYER_H
#pragma once
#include <wx/graphics.h>
#include <string>
class Spartanmind;

class Player {
protected:
    Spartanmind* mGameWorld;  //  Pointer to the game world
    double mX, mY;            //  Position
    double mTargetX, mTargetY;
    double mWidth, mHeight;

    std::wstring mFilename;  //  Character image file

public:
    Player(Spartanmind* gameWorld, const std::wstring& filename);

    virtual ~Player() {}

    virtual void Update(double elapsedTime);
    virtual void Draw(wxGraphicsContext* graphics);
    virtual void SetTarget(double x, double y);
    virtual void Headbutt() = 0;
    virtual void Eat() = 0;
};



#endif //PLAYER_H
