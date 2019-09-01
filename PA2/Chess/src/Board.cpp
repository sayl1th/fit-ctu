//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Board.hpp"

#include "Pawn.hpp"
#include "Bishop.hpp"
#include "Knight.hpp"
#include "Rook.hpp"
#include "Queen.hpp"
#include "King.hpp"

#include "Player.hpp"
#include "GameSession.hpp"
#include "Exceptions.hpp"

#include <iostream>
#include <fstream>


Board::Board() : startRowUp(6), startRowDown(1), lastRowUp(7), lastRowDown(0) {

    for(int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j)
            m_positions[i][j].setPosValue(8 - abs(i - 3) - abs(j - 3));
    }
}


Board::Board(const Board& rhs)  {

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            Piece* piece = rhs.m_positions[i][j].getPosPiece();

            if (piece)
                m_positions[i][j].setPosPiece(piece->clone(piece));

            else
                m_positions[i][j].setPosPiece(nullptr);

        }
    }

    lastRowDown = rhs.lastRowDown;
    lastRowUp = rhs.lastRowUp;
    startRowDown = rhs.startRowDown;
    startRowUp = rhs.startRowUp;
}


void Board::createPieces(const COLOR& color){

    int qPos;
    int kPos;

    COLOR oppColor = (color == WHITE ? BLACK : WHITE);

    if (color == WHITE) {
        qPos = 3;
        kPos = 4;
    }

    else {
        qPos = 4;
        kPos = 3;
    }

    m_positions[0][0].setPosPiece(new Rook(color, 0, 0));
    m_positions[0][7].setPosPiece(new Rook(color, 0, 7));

    m_positions[0][1].setPosPiece(new Knight(color, 0, 1));
    m_positions[0][6].setPosPiece(new Knight(color, 0, 6));

    m_positions[0][2].setPosPiece(new Bishop(color, 0, 2));
    m_positions[0][5].setPosPiece(new Bishop(color, 0, 5));

    m_positions[0][qPos].setPosPiece(new Queen(color, 0, qPos));
    m_positions[0][kPos].setPosPiece(new King(color, 0, kPos));

    for(int i = 0; i < 8; ++i)
        m_positions[1][i].setPosPiece(new Pawn(color, 1, i));


    m_positions[7][0].setPosPiece(new Rook(oppColor, 7, 0));
    m_positions[7][7].setPosPiece(new Rook(oppColor, 7, 7));

    m_positions[7][1].setPosPiece(new Knight(oppColor, 7, 1));
    m_positions[7][6].setPosPiece(new Knight(oppColor, 7, 6));

    m_positions[7][2].setPosPiece(new Bishop(oppColor, 7, 2));
    m_positions[7][5].setPosPiece(new Bishop(oppColor, 7, 5));

    m_positions[7][qPos].setPosPiece(new Queen(oppColor, 7, qPos));
    m_positions[7][kPos].setPosPiece(new King(oppColor, 7, kPos));

    for(int i = 0; i < 8; ++i)
        m_positions[6][i].setPosPiece(new Pawn(oppColor, 6, i));


    for(int i = 5; i >= 2; --i) {
        for (int j = 0; j < 8; ++j)
            m_positions[i][j].setPosPiece(nullptr);
    }

}


void Board::printBoard() const {

    Piece* piece = nullptr;

    for (int i = 7; i >= 0; --i) {
        for (int j = 0; j < 8; ++j) {

            if(j == 0)
                std::cout << i << " |";

            piece  = m_positions[i][j].getPosPiece();

            if(!piece)
                std::cout << " ";

            else
                piece->printPiece(std::cout);

            std::cout <<"|";

            if(j == 7)
                std::cout << std::endl;
        }
    }

    std::cout << "   a b c d e f g h" << std::endl;

    std::cout << std::endl << std::endl;
}


void Board::movePiece(const MyMove& move) {

    if (getPiece(move.m_fRow,move.m_fCol)->getName() == _PAWN){

        if (move.m_toRow == lastRowUp || move.m_toRow == lastRowDown) {
            promote(move);
            return;
        }
    }

    Piece* piece = m_positions[move.m_toRow][move.m_toCol].getPosPiece();
    delete piece;

    piece = m_positions[move.m_fRow][move.m_fCol].getPosPiece();

    m_positions[move.m_fRow][move.m_fCol].setPosPiece(nullptr);
    m_positions[move.m_toRow][move.m_toCol].setPosPiece(piece);

    piece->setRow(move.m_toRow);
    piece->setCol(move.m_toCol);
}


bool Board::isCheckMove(const MyMove &move, const GameSession &session) const {

    Board board(session.getBoard());
    board.movePiece(move);

    King* king = board.findKing(session.currentPlayer->getPlayerColor());

    bool isCurrPlayerDown;

    if (session.currentPlayer == session.player1)
        isCurrPlayerDown = true;
    else
        isCurrPlayerDown = false;

    return !king->isChecked(board, isCurrPlayerDown);
}


King* Board::findKing(const COLOR& color) const{

    King* king = nullptr;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; j++) {

            if (!getPiece(i,j))
                continue;

            if (getPiece(i,j)->getName() == _KING && getPiece(i,j)->getColor() == color) {

                Piece* piece = getPiece(i,j);
                king = dynamic_cast<King*>(piece);
                return king;
            }
        }
    }

    return king;
}


void Board::promote(const MyMove& move) {

    COLOR color = m_positions[move.m_fRow][move.m_fCol].getPosPiece()->getColor();

    delete m_positions[move.m_toRow][move.m_toCol].getPosPiece();
    delete m_positions[move.m_fRow][move.m_fCol].getPosPiece();

    m_positions[move.m_fRow][move.m_fCol].setPosPiece(nullptr);

    auto queen = new Queen(color, move.m_toRow, move.m_toCol);
    m_positions[move.m_toRow][move.m_toCol].setPosPiece(queen);
}


Piece* Board::getPiece(const int& row, const int& col) const {

    return m_positions[row][col].getPosPiece();
}


bool Board::outOfBoard(const int& row, const int& col) const {
    return row < 0 || row >= 8 || col < 0 || col >= 8;
}


void Board::setPos(const int& row, const int& col, Piece* piece) {

    m_positions[row][col].setPosPiece(piece);
}


int Board::getPosValue(const int& row,const int& col) const {

    if(!outOfBoard(row,col))
        return m_positions[row][col].getPosValue();

    return 0;
}


void Board::copy(const Board& rhs) {

    if(this == &rhs)
        return;

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {

            delete m_positions[i][j].getPosPiece();

            Piece* piece = rhs.m_positions[i][j].getPosPiece();
            Piece* tmp = nullptr;

            if(piece)
                tmp= piece->clone(piece);
            m_positions[i][j].setPosPiece(tmp);
        }
    }
}






