//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Rook.hpp"
#include "GameSession.hpp"


Rook::Rook() {

    m_name = _ROOK;
    m_value = 5;
    moveList.reserve(15);
}
Rook::Rook(const COLOR& color, const int& row, const int& col) : Piece(color, row, col) {

    m_name = _ROOK;
    m_value = 5;
    moveList.reserve(15);
}

Rook::~Rook() = default;


Piece* Rook::clone(const Piece* piece) const {

    return new Rook(piece->getColor(), piece->getRow(), piece->getCol());
}

MoveList& Rook::findAllMoves(const GameSession& session) {

    moveList.deleteMoves();


    int row = getRow();
    int col = getCol();

    for (; row < 8; ++row) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    row = getRow();
    col = getCol();

    for (; row >= 0; --row) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    row = getRow();
    col = getCol();

    for (; col < 8; ++col) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }



    row = getRow();
    col = getCol();

    for (; col >= 0; --col) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    return moveList;

}


