/**
 * @file TrayVisitor.cpp
 * @author Terrance Zackery
 */

#include "pch.h"
#include "TrayVisitor.h"

/**
 * Visit tray
 * @param tray Tray we are visiting
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
 * @param letter Given Letter we are visiting
 */
void TrayVisitor::VisitLetter(Letter *letter)
{
    isFound = true;
}

/**
 * Is the Tray full
 *
 * @return
 */
bool TrayVisitor::IsFull()
{
    return mTray->IsFull();
}
