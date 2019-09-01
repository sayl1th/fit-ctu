//
// Created by Jamal Azizov on 2019-05-11.
//

#include <iostream>

#include "Bishop.hpp"
#include "GameSession.hpp"
#include "Piece.hpp"

Bishop::Bishop() {

    m_name = _BISHOP;
    m_value = 3;
    moveList.reserve(15);
}


Bishop::Bishop(const COLOR& color, const int& row, const int& col) : Piece(color, row, col) {

    m_name = _BISHOP;
    m_value = 3;
    moveList.reserve(15);
}

Bishop::~Bishop() = default;


Piece* Bishop::clone(const Piece* piece) const  {

    return new Bishop(piece->getColor(), piece->getRow(), piece->getCol());
}


MoveList& Bishop::findAllMoves(const GameSession& session) {

    moveList.deleteMoves();

    int row = getRow();
    int col = getCol();

    for (; row < 8 && col < 8; ++row, ++col) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    row = getRow();
    col = getCol();

    for (; row < 8 && col >= 0; ++row, --col) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    row = getRow();
    col = getCol();

    for (; row >= 0 && col < 8; --row, ++col) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    row = getRow();
    col = getCol();

    for (; row >= 0 && col >= 0; --row, --col) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    return moveList;
}



