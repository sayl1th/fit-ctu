//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_MAINMENU_HPP
#define CHESS_MAINMENU_HPP


#include "AbstractMenu.hpp"
#include "Controller.hpp"

/**
 * Main menu - user chooses New game, Load game or Exit
 */
class MainMenu : public AbstractMenu {
public:
    /**
     * Constructor
     * @param Pointer to the previous menu
     */
    explicit MainMenu(AbstractMenu* menu = nullptr);

    ~MainMenu() override;

    /**
     *  Initializes menu
     */
    void initialize(Controller* controller) override;

    /**
    * Set pointer to next menu
    */
    void setNextMenu() override;

};

#endif //CHESS_MAINMENU_HPP
