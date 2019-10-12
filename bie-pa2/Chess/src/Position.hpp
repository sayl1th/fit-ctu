//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_POSITION_HPP
#define CHESS_POSITION_HPP

#include "Piece.hpp"


// Class representing position on the board
class Position {
public:

    Position();

    ~Position();

    /**
    * Gets a value of the position
    * @return Value of the position
    */
    int getPosValue() const;

    /**
    * Sets a value of the position
    * @param value Value to be set
    */
    void setPosValue(const int& value);

    /**
     * Returns a piece on the position
     * @return Piece on the position or null
     */
    Piece* getPosPiece() const;

    void setPosPiece(Piece* piece);

private:

    int m_posValue;  // Value of the position
    Piece* m_posPiece;    // Piece of the position
};

#endif //CHESS_POSITION_HPP
