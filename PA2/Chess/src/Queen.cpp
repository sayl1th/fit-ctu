//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Queen.hpp"
#include "GameSession.hpp"

Queen::Queen() {

    m_name = _QUEEN;
    m_value = 10;
    moveList.reserve(30);
}

Queen::Queen(const COLOR& color, const int& row, const int& col) : Piece(color, row, col) {

    m_name = _QUEEN;
    m_value = 10;
    moveList.reserve(30);
}

Queen::~Queen() = default;


Piece* Queen::clone(const Piece* piece) const {

    return new Queen(piece->getColor(), piece->getRow(), piece->getCol());
}


MoveList& Queen::findAllMoves(const GameSession& session) {

    moveList.deleteMoves();

    int row = getRow();
    int col = getCol();

    for (; row < 8; ++row) {

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

    for (; row >= 0; --row) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    row = getRow();
    col = getCol();

    for (; col >= 0; --col) {

        if (checkPos(row, col, session.getBoard()) == 1)
            break;
    }

    row = getRow();
    col = getCol();

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
