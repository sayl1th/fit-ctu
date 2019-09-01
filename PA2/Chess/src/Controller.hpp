//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_CONTROLLER_HPP
#define CHESS_CONTROLLER_HPP


#include "GameSession.hpp"
#include "COLORS.hpp"


class AbstractMenu;

class Controller {
public:

    Controller();

    virtual ~Controller();

    /**
     *  Starts initializing the game
     */
    void gameStart();

    /**
    *  The main game loop
    */
    void game();

    /**
    *  Returns a reference to the instance of the game
    */
    GameSession& getSession();

    /**
    *  Calls menus
    */
    void showMenu();

private:
    /**
     *  Deletes menu screens
     */
    void deleteMenu();

    GameSession m_session;  // the instance of a game
    AbstractMenu* m_menu; // linked list of menu screens
};


#endif //CHESS_CONTROLLER_HPP
