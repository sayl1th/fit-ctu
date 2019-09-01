//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_BISHOP_HPP
#define CHESS_BISHOP_HPP

#include "COLORS.hpp"
#include "Piece.hpp"

/**
 * Class representing bishop
 */
class Bishop : public Piece {
public:

    Bishop();
    /**
    * Creates a bishop with given parameters
    * @param color The color of bishop
    * @param row The row where bishop is placed
    * @param col The column where bishop is placed
    */
    Bishop(const COLOR& color,const int& row, const int& col);

    ~Bishop() override;

    /**
    * Make a copy of bishop
    * @param piece a pointer to the figure
    * @return a new instance of bishop
    */
    Piece* clone(const Piece* piece) const override;

    /**
    * finds all moves of bishop
    * @param session Reference to the instance of the game
    * @return Reference to the list of all possible moves
    */
    MoveList& findAllMoves(const GameSession& session) override;
};

#endif //CHESS_BISHOP_HPP

