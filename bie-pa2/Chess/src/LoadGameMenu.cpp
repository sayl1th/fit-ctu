//
// Created by Jamal Azizov on 2019-05-11.
//
#include "LoadGameMenu.hpp"
#include "LocalPlayer.hpp"
#include "Intelligence.hpp"
#include "Piece.hpp"

#include <climits>
#include <fstream>
#include <algorithm>


LoadGameMenu::LoadGameMenu(AbstractMenu* menu) : AbstractMenu(menu), m_persistence(nullptr), m_fileName(""), m_loadFlag(false) {

    m_title = "Enter the file name to be loaded:";
}


LoadGameMenu::~LoadGameMenu() {

    delete m_persistence;
    m_persistence = nullptr;
}


void LoadGameMenu::initialize(Controller* controller) {

    if(!m_loadFlag)
        return;

    delete controller->getSession().player1;
    delete controller->getSession().player2;

    controller->getSession().player1 = new LocalPlayer();

    std::cout << "Choose the game type:" << std::endl;
    std::cout << "1. Player vs AI\n2. Player vs Player" << std::endl;

    int choice;

    while (std::cin >> choice) {
        if (!std::cin.good() || (choice != 1 && choice != 2)) {
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');
            std::cout << "Enter either 1 or 2" << std::endl;
        }
        else
            break;
    }

    if (choice == 1){
        std::cout << "Choose the difficulty of AI (1-3)" << std::endl;

        int difficulty;
        std::cin >> difficulty;

        while (!std::cin.good() || difficulty < 1 || difficulty > 3) {
            std::cin.clear();
            std::cin.ignore(INT_MAX,'\n');

            std::cout << "Enter either 1, 2, or 3" << std::endl;
            std::cin >> difficulty;
        }
        controller->getSession().player2 = new Intelligence(difficulty);
    }

    else
        controller->getSession().player2 = new LocalPlayer();

    if (m_loadFlag && m_persistence) {
        controller->getSession().m_board.copy(m_persistence->m_gameData.board);
        controller->getSession().setColors(m_persistence->m_gameData.player1col);
        controller->getSession().setMoveTurn(m_persistence->m_gameData.whosTurn);
        controller->getSession().fileName = m_fileName;
        controller->getSession().setGameReady();

    } else
        std::cout << "Could not load the game" << std::endl;

}


void LoadGameMenu::setNextMenu() {

    if (!m_loadFlag)
        nextMenu = prevMenu;
    else
        nextMenu = nullptr;

}


int LoadGameMenu::readInput() {

    std::string fileName;

    while (std::cin.good()) {

        std::cin >> fileName;

        if (!std::cin.good()) {

            fileName.clear();
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            std::cout << "Failed to read the file name, please try again" << std::endl;
            continue;
        }

        std::string tmp = fileName;

        std::transform(tmp.begin(), tmp.end(), tmp.begin(), ::tolower);

        if (tmp == "back") {
            delete nextMenu;
            return 0;
        }

        if (!findFile(fileName)) {
            std::cout << "Error, could not find the file \"" << fileName << "\"." << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
            continue;
        }

        if (confirmLoad()) {
            m_fileName = fileName;
            loadFile(m_fileName);
            break;
        }
        else
            return 1;
    }

    return 0;
}


void LoadGameMenu::printMenu() const {

    printTitle();
}


bool LoadGameMenu::findFile(const std::string& file) const {

    std::ifstream ifs(file.c_str());

    if (ifs.good()) {

        ifs.close();
            return true;
    }

    return false;

}


void LoadGameMenu::loadFile(const std::string& file) {

    delete m_persistence;
    m_persistence = new FilePersistence();

    if(m_persistence->load(file)){

        m_loadFlag = true;
        return;
    }

    m_loadFlag = false;
}


bool LoadGameMenu::confirmLoad() {

    std::cout << "The file is found" << std::endl;
    std::cout << "Do you want to load it? (y/n)" << std::endl;

    char choice;

    while (std::cin.good()) {

        std::cin>>choice;

        if (choice == 'y')
            return true;

        else if (choice == 'n') {
            return false;

        } else {
            std::cout << "Enter either y or n" << std::endl;
            std::cin.clear();
            std::cin.ignore(INT_MAX, '\n');
        }
    }

    std::cout << "Action cancelled" << std::endl;

    return false;
}
