//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_KING_HPP
#define CHESS_KING_HPP

#include "Piece.hpp"
#include "COLORS.hpp"

class GameSession;
class Board;

/**
 * Subclass representing king
 */

class King : public Piece {
public:

    King();
    /**
    * Creates a king with given parameters
    * @param color A color of the king
    * @param row A row of the king's position
    * @param col A column of the king's position
    */
    King(const COLOR& color, const int& row, const int& col);

    ~King() override;

    /**
    * Make a copy of king
    * @param piece a pointer to the figure
    * @return a new instance of king
    */
    Piece* clone(const Piece* piece) const override;

    /**
    * Finds all moves of king
    * @param session Reference to the instance of the game
    * @return Reference to the list of all possible moves
    */
    MoveList & findAllMoves(const GameSession& session) override;


    /**
    * Checks if the king can move to given position
    * @param row a row of the position
    * @param col a column of the position
    * @param board reference to chessboard
    * @return 0 for positive answer, 1 for negative
    */
    int checkPos(const int& row, const int& col, const Board& board) override;

    bool isChecked(const Board& board, bool currentPlayerDown) const;

    bool isCheckedByKnight(const int& row, const int& col, const Board& board) const;
};


#endif //CHESS_KING_HPP
