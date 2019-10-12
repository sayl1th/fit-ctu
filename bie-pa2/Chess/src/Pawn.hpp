//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_PAWN_HPP
#define CHESS_PAWN_HPP


#include "COLORS.hpp"
#include "Piece.hpp"


/**
 * Subclass representing a pawn
 */
class Pawn : public Piece {
public:

    Pawn();
    /**
    * Creates a bishop with given parameters
    * @param color The color of bishop
    * @param row The row where bishop is placed
    * @param col The column where bishop is placed
    */
    Pawn(const COLOR& color, const int& row, const int& col);

    ~Pawn() override;

    /**
    * Make a copy of pawn
    * @param piece a pointer to the figure
    * @return a new instance of pawn
    */
    Piece* clone(const Piece* piece) const override;

    /**
    * finds all moves of pawn
    * @param session Reference to the instance of the game
    * @return Reference to the list of all possible moves
    */
    MoveList& findAllMoves(const GameSession& session) override;


    MoveList& findMovesUp(const Board& board);

    MoveList& findMovesDown(const Board& board);

    int checkPosPawn(const int &row, const int &col, const Board &board, bool sideMove);
};


#endif //CHESS_PAWN_HPP
