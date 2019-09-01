//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_KNIGHT_HPP
#define CHESS_KNIGHT_HPP


#include "Piece.hpp"
#include "COLORS.hpp"

/**
 * Subclass representing knight
 */
class Knight : public Piece{
public:
    Knight();
    /**
    * Creates a knight with given parameters
    * @param color A color of the knight
    * @param row A row of the knight's position
    * @param col A column of the knight's position
    */
    Knight(const COLOR& color, const int& row, const int& col);

    ~Knight() override;

    /**
    * Make a copy of knight
    * @param piece a pointer to the figure
    * @return a new instance of knight
    */
    Piece* clone(const Piece* piece) const override;

    /**
    * Finds all moves of knight
    * @param session Reference to the instance of the game
    * @return Reference to the list of all possible moves
    */
    MoveList& findAllMoves(const GameSession& session) override;
};

#endif //CHESS_KNIGHT_HPP
