//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_ROOK_HPP
#define CHESS_ROOK_HPP


#include "Piece.hpp"
#include "COLORS.hpp"

/**
 * Subclass representing rook
 */
class Rook : public Piece{
public:

    Rook();

    Rook(const COLOR& color, const int& row, const int& col);

    ~Rook() override;

    /**
    * Make a copy of rook
    * @param piece a pointer to the figure
    * @return a new instance of rook
    */
    Piece* clone(const Piece* piece) const override;

    /**
    * Finds all moves of rook
    * @param session Reference to the instance of the game
    * @return Reference to the list of all possible moves
    */
    MoveList& findAllMoves(const GameSession& session) override;

};
#endif //CHESS_ROOK_HPP
