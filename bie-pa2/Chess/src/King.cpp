//
// Created by Jamal Azizov on 2019-05-11.
//

#include "King.hpp"
#include "Piece.hpp"
#include "Board.hpp"
#include "GameSession.hpp"



King::King() {

    m_name = _KING;
    m_value = 50;
    moveList.reserve(10);
}

King::King(const COLOR& color, const int& row, const int& col) : Piece(color, row, col) {

    m_name = _KING;
    m_value = 50;
    moveList.reserve(10);
}

King::~King() = default;


Piece* King::clone(const Piece* piece) const {

    return new King(piece->getColor(), piece->getRow(), piece->getCol());
}



MoveList& King::findAllMoves(const GameSession& session) {

    moveList.deleteMoves();

    int row = getRow() + 1;
    int col = getCol() + 1;

    checkPos(row, col, session.getBoard());

    row = getRow() - 1;
    col = getCol() + 1;

    checkPos(row, col, session.getBoard());

    row = getRow() + 1;
    col = getCol() - 1;

    checkPos(row, col, session.getBoard());

    row = getRow() - 1;
    col = getCol() - 1;

    checkPos(row, col, session.getBoard());

    row = getRow() + 1;
    col = getCol();

    checkPos(row, col, session.getBoard());

    row = getRow();
    col = getCol() + 1;

    checkPos(row, col, session.getBoard());

    row = getRow() - 1;
    col = getCol();

    checkPos(row, col, session.getBoard());

    row = getRow();
    col = getCol() - 1;

    checkPos(row, col, session.getBoard());

    return moveList;
}

int King::checkPos(const int& row, const int& col, const Board& board) {

    if (row == getRow() && col == getCol())
        return 0;

    if (board.outOfBoard(row, col))
        return 1;

    Piece* piece = board.getPiece(row, col);

    if (!piece) {

        moveList.add(row, col, m_row, m_col, nullptr);
        return 1;

    } else {

        if (isPlayerPiece(piece))
            return 1;

        else {
            moveList.add(row, col, m_row, m_col, piece);
            return 1;
        }
    }
}

bool King::isChecked(const Board& board, bool currentPlayerDown) const {

    int row = getRow() + 1;
    int col = getCol() - 1;

    while (!board.outOfBoard(row,col)){

        if (!board.getPiece(row,col)) {
            ++row;
            --col;
            continue;
        }

        if (board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING)) {

                if (row == getRow() + 1 && col == getCol() - 1)
                    return true;

                else
                    break;
            }

            else if (board.getPiece(row,col)->equals(_PAWN)) {

                if (currentPlayerDown && row == getRow() + 1 && col == getCol() - 1)
                    return true;
                else
                    break;
            }

            else if (board.getPiece(row,col)->equals(_BISHOP)
                     ||  board.getPiece(row,col)->equals(_QUEEN))
                return true;

            else
                break;
        }

        ++row;
        --col;
    }

    row = getRow() + 1;
    col = getCol() + 1;


    while (!board.outOfBoard(row,col)) {

        if (!board.getPiece(row,col)) {
            ++row;
            ++col;
            continue;
        }

        if (board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING)) {

                if (row == getRow() + 1 && col == getCol() + 1)
                    return true;

                else
                    break;
            }

            else if (board.getPiece(row,col)->equals(_PAWN)) {

                if (currentPlayerDown && row == getRow() + 1 && col == getCol() + 1)
                    return true;
                else
                    break;
            }

            else if (board.getPiece(row,col)->equals(_BISHOP)
                     ||  board.getPiece(row,col)->equals(_QUEEN))
                return true;
            else
                break;
        }

        ++row;
        ++col;
    }

    row = getRow() - 1;
    col = getCol() - 1;

    while (!board.outOfBoard(row,col)) {

        if (!board.getPiece(row,col)) {
            --row;
            --col;
            continue;
        }

        if (board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING) && col == getCol() - 1 && row == getRow() - 1)
                return true;

            else if (board.getPiece(row,col)->equals(_PAWN)) {

                if (currentPlayerDown == false && row == getRow() - 1 && col == getCol() - 1)
                    return true;
                else
                    break;
            }

            else if (board.getPiece(row,col)->equals(_BISHOP)
                     ||  board.getPiece(row,col)->equals(_QUEEN))
                return true;

            else
                break;
        }
        --row;
        --col;
    }

    row = getRow() - 1;
    col = getCol() + 1;

    while (!board.outOfBoard(row,col)) {

        if (!board.getPiece(row,col)){
            --row;
            ++col;
            continue;
        }

        if (board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING) && col == getCol() + 1 && row == getRow()- 1 )
                return true;

            else if (board.getPiece(row,col)->equals(_PAWN)) {

                if (currentPlayerDown==false && row == getRow() - 1 && col == getCol() + 1)
                    return true;

                else
                    break;
            }

            else if (board.getPiece(row,col)->equals(_BISHOP)
                     ||  board.getPiece(row,col)->equals(_QUEEN))
                return true;

            else
                break;
        }

        --row;
        ++col;
    }

    row = getRow();
    col = getCol() + 1;

    while (!board.outOfBoard(row,col)) {

        if (!board.getPiece(row,col)) {
            col++;
            continue;
        }

        if(board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING) && col == getCol() + 1)
                return true;

            else if (board.getPiece(row,col)->equals(_ROOK)
                     || board.getPiece(row,col)->equals(_QUEEN))
                return true;

            else
                break;
        }

        ++col;
    }

    row = getRow();
    col = getCol() - 1;

    while (!board.outOfBoard(row,col)) {

        if (!board.getPiece(row,col)){
            col--;
            continue;
        }

        if (board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING) && col == getCol() - 1)
                return true;

            else if (board.getPiece(row,col)->equals(_ROOK)
                     || board.getPiece(row,col)->equals(_QUEEN))
                return true;

            else
                break;
        }
        --col;
    }

    row = getRow() - 1;
    col = getCol();

    while (!board.outOfBoard(row,col)) {

        if (!board.getPiece(row,col)) {
            row--;
            continue;
        }

        if (board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING) && row == getRow() - 1)
                return true;

            else if (board.getPiece(row,col)->equals(_ROOK)
                     ||  board.getPiece(row,col)->equals(_QUEEN))
                return true;

            else
                break;
        }

        --row;
    }

    row = getRow() + 1;
    col = getCol();

    while (!board.outOfBoard(row,col)) {

        if (!board.getPiece(row,col)) {
            row++;
            continue;
        }

        if (board.getPiece(row, col)->isPlayerPiece(this))
            break;

        else {

            if (board.getPiece(row,col)->equals(_KING) && row == getRow() + 1)
                return true;

            else if (board.getPiece(row,col)->equals(_ROOK)
                     || board.getPiece(row,col)->equals(_QUEEN))
                return true;

            else
                break;
        }

        ++row;
    }

    row = getRow() + 2;
    col = getCol() - 1;

    if (isCheckedByKnight(row, col, board))
        return true;


    row = getRow() + 2;
    col = getCol() + 1;

    if (isCheckedByKnight(row, col, board))
        return true;

    row = getRow() - 2;
    col = getCol() - 1;

    if (isCheckedByKnight(row, col, board))
        return true;

    row = getRow() - 2;
    col = getCol() + 1;

    if (isCheckedByKnight(row, col, board))
        return true;

    row = getRow() + 1;
    col = getCol() - 2;

    if (isCheckedByKnight(row, col, board))
        return true;

    row = getRow() + 1;
    col = getCol() + 2;

    if (isCheckedByKnight(row, col, board))
        return true;

    row = getRow() - 1;
    col = getCol() + 2;

    if (isCheckedByKnight(row, col, board))
        return true;

    row = getRow() - 1;
    col = getCol() - 2;

    if (isCheckedByKnight(row, col, board))
        return true;

    return false;
}

bool King::isCheckedByKnight(const int& row, const int& col, const Board& board) const {

    if (!board.outOfBoard(row, col)) {
        if (board.getPiece(row, col)) {
            if (!(board.getPiece(row, col)->isPlayerPiece(this))) {
                if (board.getPiece(row, col)->getName() == _KNIGHT)
                    return true;
            }
        }
    }

    return false;
}
