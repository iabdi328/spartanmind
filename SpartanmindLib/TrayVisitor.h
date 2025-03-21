/**
 * @file TrayVisitor.h
 * @author Terrance Zackery
 *
 *
 */

#include "ItemVisitor.h"
#include "Tray.h"
#include "Item.h"

#ifndef PROJECT1_SPARTANMINDLIB_TRAYVISITOR_H
#define PROJECT1_SPARTANMINDLIB_TRAYVISITOR_H

class TrayVisitor : public ItemVisitor
{
private:
    /// Tray object ptr
    Tray* mTray = nullptr;
    /// is letter found
    bool isFound = false;
    ///List of items in Tray
    std::vector<std::shared_ptr<Item>> mLetters;

public:
    Tray* GetTray() const { return mTray; }

    virtual void VisitTray(Tray* tray) override;

    virtual void VisitLetter(Letter* letter) override;

    /**
     * Is item found
     * @return bool
     */
    bool IsFound() { return isFound; }

    /**
     * Get the letter items
     * @return letters
     */
    std::vector<std::shared_ptr<Item>> GetLetters() { return mLetters; }

    bool IsFull();

};

#endif //PROJECT1_SPARTANMINDLIB_TRAYVISITOR_H
