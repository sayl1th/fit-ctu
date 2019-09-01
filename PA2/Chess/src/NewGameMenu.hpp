//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_NEWGAMEMENU_HPP
#define CHESS_NEWGAMEMENU_HPP


#include "AbstractMenu.hpp"


class NewGameMenu : public AbstractMenu {
public:
    /**
     * Constructor
     * @param Pointer to the previous menu
     */
    explicit NewGameMenu(AbstractMenu* menu);

    ~NewGameMenu() override;

    /**
     *  Initializes menu
     */
    void initialize(Controller* controller) override;

    /**
   * Sets pointer to next menu
   */
    void setNextMenu() override;

};

#endif //CHESS_NEWGAMEMENU_HPP
