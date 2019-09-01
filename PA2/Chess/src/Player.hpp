//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_PLAYER_HPP
#define CHESS_PLAYER_HPP

#include "COLORS.hpp"
#include "MoveList.hpp"

#include <vector>

class GameSession;
class Command;
class Board;
class King;
class Piece;

/**
 * Abstract class representing player
 */
class Player {
public:

    Player();

    virtual ~Player();

    /**
     * Abstract function for getting command from user.
     * @param session Reference to instance of the game
     * @return command
     */
    virtual Command getCommand(const GameSession& session) = 0;


    COLOR getPlayerColor() const;

    void printPlayerColor(std::ostream& os) const;

    void setPlayerColor(const COLOR& color);

    /**
     * Finds all figures of the player
     * @param board Reference to the board
     */
    void getAllFigures(const Board& board);

    /**
     * Checks whether player's king is checked
     * @param session Reference to instance of a game
     */
    bool isKingChecked(const GameSession& session) const;

    /**
     * Sets given king to the player
     * @param king King to be set
     */
    void setKing(King* king);

protected:
    std::vector<Piece*> m_figures;      // vector of all figures of the player
    MoveList m_allMoves;               // All possible moves of the player

    COLOR m_playerColor;              // Color of the player
    King* m_king;                    // A pointer to player's king

    friend class GameSession;
};


#endif //CHESS_PLAYER_HPP
