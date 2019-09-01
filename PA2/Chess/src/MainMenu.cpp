//
// Created by Jamal Azizov on 2019-05-11.
//


#include "MainMenu.hpp"

#include "LoadGameMenu.hpp"
#include "NewGameMenu.hpp"

MainMenu::MainMenu(AbstractMenu* menu) : AbstractMenu(menu) {

    m_title = "Choose your destiny: ";

    m_items[0] = "New game";
    m_items[1] = "Load game";
    m_items[2] = "Exit";

    setNumOfItems();
}

MainMenu::~MainMenu() = default;

void MainMenu::initialize(Controller* controller) {}

void MainMenu::setNextMenu() {

    delete nextMenu;

    if (m_choice == 1)
        nextMenu = new NewGameMenu(this);

    else if (m_choice == 2)
        nextMenu = new LoadGameMenu(this);

    else
        nextMenu = nullptr;

}
