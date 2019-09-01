//
// Created by Jamal Azizov on 2019-05-11.
//


#include "NewGameMenu.hpp"
#include "Controller.hpp"

#include "LocalPlayer.hpp"
#include "Intelligence.hpp"

#include "DifficultyMenu.hpp"
#include "ColorMenu.hpp"


NewGameMenu::NewGameMenu(AbstractMenu* menu) : AbstractMenu(menu) {

    m_title = "Choose the game type: ";

    m_items[0] = "Player vs AI";
    m_items[1] = "Player vs Player";
    m_items[2] = "Back";

    setNumOfItems();
}


NewGameMenu::~NewGameMenu() = default;


void NewGameMenu::initialize(Controller* controller) {

    delete controller->getSession().player1;
    controller->getSession().player1 = new LocalPlayer();

    if (m_choice == 1) {

        delete controller->getSession().player2;
        controller->getSession().player2 = new Intelligence();
    }

    else if (m_choice == 2) {

        delete controller->getSession().player2;
        controller->getSession().player2 = new LocalPlayer();
    }
}


void NewGameMenu::setNextMenu() {

    delete nextMenu;

    if (m_choice == 1)
        nextMenu = new DifficultyMenu(this);

    else if (m_choice == 2)
        nextMenu = new ColorMenu(this);

    else
        nextMenu = prevMenu;

}



