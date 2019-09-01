//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Controller.hpp"
#include "AbstractMenu.hpp"
#include "GameSession.hpp"
#include "Command.hpp"
#include "Player.hpp"
#include "MainMenu.hpp"

Controller::Controller() {

    m_menu = new MainMenu();
}


Controller::~Controller() {

    deleteMenu();
}


void Controller::deleteMenu() {

    AbstractMenu* menu = m_menu;
    AbstractMenu* tmpMenu = menu;

    if (!m_menu)
        return;

    while (menu->nextMenu) {

        menu = menu->nextMenu;
        delete tmpMenu;
        tmpMenu = menu;
    }

    delete menu;

    m_menu = nullptr;
}


void Controller::gameStart() {

    if (m_session.isGameReady())
        m_session.sessionStart();
    else {
        m_session.sessionEnd();
        return;
    }

    game();
    m_session.sessionEnd();
}


void Controller::game() {

    std::cin.ignore();

    if (m_session.moveTurnColor == WHITE) {
        if (m_session.player1->getPlayerColor() == WHITE)
            m_session.currentPlayer = m_session.player1;
        else
            m_session.currentPlayer = m_session.player2;
    } else {
        if (m_session.player1->getPlayerColor() == BLACK)
            m_session.currentPlayer = m_session.player1;
        else
            m_session.currentPlayer = m_session.player2;
    }

    while (true) {

        Command command;

        if (m_session.isCheckMate()) {

            command.m_command = SURRENDER;
            command.executeCommand(m_session);
            return;
        }

        else if (m_session.isTie()) {

            command.m_command = TIE;
            command.executeCommand(m_session);
            return;
        }

        else if (m_session.currentPlayer->isKingChecked(m_session)) {

            Command checkCommand;
            checkCommand.m_command = CHECK;
            checkCommand.executeCommand(m_session);
        }

        while (command.m_command == UNKNOWN) {
            if (m_session.currentPlayer == m_session.player2)
                std::cout << "Waiting for opponent's move." << std::endl;
            command = m_session.currentPlayer->getCommand(m_session);
        }

        command.executeCommand(m_session);

        if (m_session.exitFlag)
            break;

        if (m_session.moveFlag) {
            m_session.switchPlayers();
            m_session.moveFlag = false;

        }
    }
}


void Controller::showMenu(){

    AbstractMenu* menu = m_menu;

    while (menu) {

        menu->printMenu();
        std::cout << "Your choice: " << menu->readInput() << std::endl;

        menu->initialize(this);
        menu->setNextMenu();

        if (!menu->nextMenu && !menu->prevMenu) {
            deleteMenu();
            break;
        }
        else
            menu = menu->nextMenu;
    }
}


GameSession& Controller::getSession() {

    return m_session;
}

