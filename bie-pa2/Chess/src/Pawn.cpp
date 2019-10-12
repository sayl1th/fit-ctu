//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Pawn.hpp"
#include "GameSession.hpp"

Pawn::Pawn() {

    m_name = _PAWN;
    m_value = 1;
    moveList.reserve(15);
}

Pawn::Pawn(const COLOR& color, const int& row, const int& col) : Piece(color, row, col) {

    m_name = _PAWN;
    m_value = 1;
    moveList.reserve(15);
}


Pawn::~Pawn() = default;


Piece* Pawn::clone(const Piece* piece) const {

    return new Pawn(piece->getColor(), piece->getRow(), piece->getCol());
}


MoveList& Pawn::findAllMoves(const GameSession& session) {

    if(session.currentPlayer != session.player1)
        return findMovesDown(session.getBoard());
    else
        return findMovesUp(session.getBoard());
}


MoveList& Pawn::findMovesDown(const Board &board) {

    moveList.deleteMoves();


    int row = getRow() - 1;
    int col = getCol();

    int firstMove = checkPosPawn(row, col, board, false);

    checkPosPawn(getRow() - 1, getCol() - 1, board, true);
    checkPosPawn(getRow() - 1, getCol() + 1, board, true);

    if (getRow() == board.startRowUp && firstMove != 2) {
        row = getRow() - 2;
        checkPosPawn(row, col, board, false);
    }

    return moveList;
}


MoveList& Pawn::findMovesUp(const Board &board) {

    moveList.deleteMoves();


    int row = getRow() + 1;
    int col = getCol();

    int firstMove = checkPosPawn(row, col, board, false);

    checkPosPawn(getRow() + 1, getCol() - 1, board, true);
    checkPosPawn(getRow() + 1, getCol() + 1, board, true);

    if (getRow() == board.startRowDown && firstMove != 2) {
        row = getRow() + 2;
        checkPosPawn(row, col, board, false);
    }

    return moveList;
}


int Pawn::checkPosPawn(const int& row, const int& col, const Board &board, bool sideMove) {

    if (row == getRow() && col == getCol())
        return 0;

    if (board.outOfBoard(row, col))
        return 1;

    Piece* piece = board.getPiece(row, col);

    if (sideMove) {

        if (!piece)
            return 1;

        else if (isPlayerPiece(piece))
            return 1;

         else {
            moveList.add(row, col, m_row, m_col, piece);
            return 0;
        }

    } else {

        if (piece)
            return 2;

         else {
            moveList.add(row, col, m_row, m_col, nullptr);
            return 0;
        }
    }
}
