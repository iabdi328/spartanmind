/**
 * @file TrayVisitor.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "TrayVisitor.h"

/**
 * Visit Xray
 * @param xray Xray we are visiting
 */
void TrayVisitor::VisitTray(Tray* tray)
{
    mTray = tray;
    if(tray->GetrayItems().size())
    {
        mLetters = mTray->GetrayItems();
    }
}


/**
 * Visit Given Number
 * @param givenNumber Given Number we are visiting
 */
void TrayVisitor::VisitLetter(Letter *letter)
{
    isFound = true;
}

/**
 * Is the Xray full
 * @return
 */
bool TrayVisitor::IsFull()
{
    return mTray->IsFull();
}
