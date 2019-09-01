//
// Created by Jamal Azizov on 2019-05-11.
//

#include "ColorMenu.hpp"
#include "AbstractMenu.hpp"
#include "Controller.hpp"
#include "GameSession.hpp"

ColorMenu::ColorMenu(AbstractMenu* menu) : AbstractMenu(menu) {

    m_title = "Choose color for Player1.";

    m_items[0] = "White";
    m_items[1] = "Black";
    m_items[2] = "Back";

    setNumOfItems();
}

ColorMenu::~ColorMenu() = default;

void ColorMenu::initialize(Controller* controller) {

    if (nextMenu)
        return;

    if (m_choice != 3){
        COLOR color;

        if (m_choice == 1)
            color = WHITE;
        else
            color = BLACK;

        controller->getSession().setColors(color);
        controller->getSession().moveTurnColor = WHITE;
        controller->getSession().setGameReady();
    }
}

void ColorMenu::setNextMenu() {

    delete nextMenu;

    if (m_choice == 3)
        nextMenu = prevMenu;
    else
        nextMenu = nullptr;
}

