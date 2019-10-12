//
// Created by Jamal Azizov on 2019-05-11.
//

#include "DifficultyMenu.hpp"
#include "ColorMenu.hpp"
#include "Controller.hpp"
#include "Intelligence.hpp"


DifficultyMenu::DifficultyMenu(AbstractMenu* menu) : AbstractMenu(menu) {

    m_title = "Choose the difficulty of AI: ";

    m_items[0] = "Easy";
    m_items[1] = "Medium";
    m_items[2] = "Hard";
    m_items[3] = "Back";

    setNumOfItems();
}

DifficultyMenu::~DifficultyMenu() = default;

void DifficultyMenu::initialize(Controller* controller) {

    if (m_choice != 4) {
        auto* ai = dynamic_cast<Intelligence*>(controller->getSession().player2);
        ai->changeDifficulty(m_choice-1);
    }
}

void DifficultyMenu::setNextMenu() {

    delete nextMenu;

    if (m_choice == 4)
        nextMenu = prevMenu;

    else
        nextMenu = new ColorMenu(this);
}


