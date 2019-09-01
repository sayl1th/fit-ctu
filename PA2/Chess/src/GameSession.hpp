//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_GAMESESSION_HPP
#define CHESS_GAMESESSION_HPP

#include <iostream>

#include "COLORS.hpp"
#include "Board.hpp"

class Player;
class Persistence;

/**
 * class contains all important game data and performs all game related operations
 */
class GameSession {
public:

    GameSession();

    ~GameSession();

    /**
     * Starts the gam
     */
    void sessionStart();

    /**
     * Ends the game
     */
    void sessionEnd();

    /**
    * Checks whether a given move is valid
    * @param move Given move
    */
    static bool checkMove(const std::string& move);

    /**
     * Checks whether given move position is in chessboard
     * @param move Given move
     */
    static bool checkPos(const std::string& move);

    /**
    * Assigns colors to players
    * @param color A color of player1.
    */
    void setColors(const COLOR& color);

    /**
    * Switches player pointer between players
    */
    void switchPlayers();

    /**
    * Checks whether the current player's king is checked
    */
    bool isCheckMate() const;

    /**
    * Checks whether the game is tied
    */
    bool isTie() const;

    /**
    * Performs a move on the chessboard
    * @param move A move to be performed
    * @return Success/Fail of the move
    */
    bool move(const MyMove& move);

    /**
     * Finds players' kings
     */
    void getKings();

    /**
     * Getter for the board
     * @return Reference to the board instance
     */
    const Board& getBoard() const;

    /**
     * Sets a ready flag
     */
    void setGameReady();

    /**
     * Checks whether the game is ready
     */
    bool isGameReady() const;

    /**
     * Sets a variable to keep a track of whose turn it is
     * @param color Color of the player
     */
    void setMoveTurn(const COLOR& color);

    std::string fileName;        // name of the load file

    Player* player1;      // A pointer to player1
    Player* player2;      // A pointer to player2
    Player* currentPlayer;    // A pointer to current player
    Persistence* persistence; // A pointer to class which executes save/load

    bool readyFlag;
    bool exitFlag;
    bool moveFlag;

    COLOR moveTurnColor;
    COLOR currentPlayerColor;    // Current player's color

private:
    Board m_board;       // chessboard
    friend class LoadGameMenu;
};

#endif //CHESS_GAMESESSION_HPP
