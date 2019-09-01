//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Knight.hpp"
#include "Piece.hpp"
#include "GameSession.hpp"

Knight::Knight() {

    m_name = _KNIGHT;
    m_value = 5;
    moveList.reserve(5);
}

Knight::Knight(const COLOR& color, const int& row, const int& col) : Piece(color, row, col) {

    m_name = _KNIGHT;
    m_value = 5;
    moveList.reserve(5);
}

Knight::~Knight() = default;


Piece* Knight::clone(const Piece* piece) const {

    return new Knight(piece->getColor(),piece->getRow(),piece->getCol());
}


MoveList & Knight::findAllMoves(const GameSession &session) {

    moveList.deleteMoves();

    int row = getRow() + 2;
    int col = getCol() + 1;

    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    row = getRow() + 2;
    col = getCol() - 1;

    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    row = getRow() - 2;
    col = getCol() + 1;

    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    row = getRow() - 2;
    col = getCol() - 1;


    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    row = getRow() + 1;
    col = getCol() + 2;

    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    row = getRow() + 1;
    col = getCol() - 2;

    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    row = getRow() - 1;
    col = getCol() + 2;

    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    row = getRow() - 1;
    col = getCol() - 2;


    if (!session.getBoard().outOfBoard(row, col))
        checkPos(row, col, session.getBoard());

    return moveList;
}
