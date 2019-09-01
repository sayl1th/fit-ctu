//
// Created by Jamal Azizov on 2019-05-11.
//

#include "AbstractMenu.hpp"

#include <climits>

AbstractMenu::AbstractMenu(AbstractMenu* menu) : nextMenu(nullptr), prevMenu(menu), m_choice(-1), m_numOfItems(-1) {}


AbstractMenu::~AbstractMenu() = default;


void AbstractMenu::printTitle() const {

    std::cout << m_title << std::endl;
}


bool AbstractMenu::checkChoice(const int& item) const {

    if (item < 1 || item > m_numOfItems) {

        std::cout << "Error, "<< item << " is not in the menu." << std::endl;
        return false;
    }

    return true;
}


void AbstractMenu::setNumOfItems() {

    int i = 0;

    for (; i < 5 && !m_items[i].empty(); ++i) {}

    m_numOfItems = i;
}

int AbstractMenu::readInput() {

    int choice = 0;

    while (true) {

        std::cin >> choice;

        if (!std::cin.good()) {
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            std::cout << "Invalid input, please try again." << std::endl;
            continue;
        }

        if (checkChoice(choice))
            break;

        else {
            std::cout << "Please try again." << std::endl;
            continue;
        }
    }

    m_choice = choice;
    return choice;
}


void AbstractMenu::printMenu() const {

    printTitle();

    for (int i = 0; i < 5 && !m_items[i].empty(); ++i) {

        printItem(i);
    }
}


void AbstractMenu::printItem(const int& item) const {

    std::cout << item+1 << ". " << m_items[item] << std::endl;
}

