//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_QUEEN_HPP
#define CHESS_QUEEN_HPP


#include "Piece.hpp"
#include "COLORS.hpp"

/**
 * Subclass representing queen
 */
class Queen : public Piece {
public:

    Queen();

    Queen(const COLOR& color, const int& row,const int& col);

    ~Queen() override;

    /**
    * Make a copy of queen
    * @param piece a pointer to the figure
    * @return a new instance of queen
    */
    Piece* clone(const Piece* piece) const override;

    /**
    * Finds all moves of queen
    * @param session Reference to the instance of the game
    * @return Reference to the list of all possible moves
    */
    MoveList& findAllMoves(const GameSession& session) override;
};



#endif //CHESS_QUEEN_HPP
