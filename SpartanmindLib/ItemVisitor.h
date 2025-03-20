/**
 * @file ItemVisitor.h
 * @author Terrance Zackery
 *
 * ItemVisitor class for all Items
 */

class Letter;
class Given;
class Player;
class Container;
class Tray;


#ifndef PROJECT1_SPARTANMINDLIB_ITEMVISITOR_H
#define PROJECT1_SPARTANMINDLIB_ITEMVISITOR_H

/**
 * ItemVisitor class for all Items
 */
class ItemVisitor
{
private:

protected:
    ItemVisitor() {}

public:
    virtual ~ItemVisitor() {}

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
     * Visit Player
     * @param player Player we are visiting
     */
    virtual void VisitPlayer(Player* player) {}

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
