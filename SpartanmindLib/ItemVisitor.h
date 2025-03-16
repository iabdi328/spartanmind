/**
 * @file ItemVisitor.h
 * @author Terrance Zackery
 *
 *
 */

class Letter;
class Given;
class Chest;
class Container;
class Tray;
class Sparty;


#ifndef PROJECT1_SPARTANMINDLIB_ITEMVISITOR_H
#define PROJECT1_SPARTANMINDLIB_ITEMVISITOR_H

class ItemVisitor
{
private:

protected:
    ItemVisitor() {}

public:
    virtual ~ItemVisitor() {}

    /**
     * Visit Sparty
     * @param sparty Sparty we are visiting
     */
    virtual void VisitSparty(Sparty* sparty) {}

    /**
     * Visit DigitNumber
     * @param digitNumber DigitNumber we are visiting
     */
    virtual void VisitChest(Chest* chest) {}

    /**
     * Visit Letter
     * @param letter Letter we are visiting
     */

    virtual void VisitLetter(Letter* letter) {}
    /**
     * Visit Given
     * @param given Givens we are visiting
     */
    virtual void VisitGiven(Given* given) {}

    /**
     * Visit Tray
     * @param tray Tray we are visiting
     */
    virtual void VisitTray(Tray* tray) {}

    /**
     * Visit Container
     * @param container Container we are visiting
     */
    virtual void VisitContainer(Container * container) {}

};

#endif //PROJECT1_SPARTANMINDLIB_ITEMVISITOR_H
