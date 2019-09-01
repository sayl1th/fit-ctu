//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_COMMAND_HPP
#define CHESS_COMMAND_HPP


#include "MyMove.hpp"
#include "COMMANDS.hpp"
#include "Controller.hpp"

class GameSession;

/**
 * Class representing commands
 */
class Command {
public:

    Command();

    /**
    * Constructs Command from MyMove
    * @param move
    */
    explicit Command(const MyMove& move);

    /**
    * Copy-constructor
    * @param command
    */
    explicit Command(const COMMAND& command);

    /**
    * Creates a command from user input
    * @param command String representing user input
    */
    void createCommand(const std::string& command);

    /**
    * Executes command
    * @param session reference to instance of the game
    */
    void executeCommand(GameSession& session);

    /**
     * Calls exit command
     * @param session reference to instance of the game
     */
    void exitCommand(GameSession& session) const;

    /**
     * Class save command
     * @param session reference to instance of the game
     */
    void saveCommand(GameSession& session) const;

    /**
    * Calls move command
    * @param session reference to instance of the game
    */
    void moveCommand(GameSession& session) const;

    /**
    * Calls surrender command
    * @param session reference to instance of the game
    */
    void surrenderCommand(GameSession& session) const;

    /**
    * Calls check command
    * @param session reference to instance of the game
    */
    void checkCommand(GameSession& session) const;

    /**
    * Calls tie command
    * @param session reference to instance of the game
    */
    void tieCommand(GameSession& session) const;

    COMMAND m_command;    // Command

private:

    MyMove m_move; // Move to be executed if move command is called
    friend class Controller;
};

#endif //CHESS_COMMAND_HPP
