//
// Created by Jamal Azizov on 2019-05-11.
//
#include <string>

#include "Piece.hpp"
#include "King.hpp"
#include "Queen.hpp"
#include "Rook.hpp"
#include "Knight.hpp"
#include "Bishop.hpp"
#include "Pawn.hpp"
#include "Board.hpp"
#include "Exceptions.hpp"


Piece::Piece() :  m_color(WHITE), m_row(-1), m_col(-1), m_value(-1) {}


Piece::Piece(const COLOR& color, const int& row, const int& col) : m_color(color), m_row(row), m_col(col), m_value(-1) {}


Piece::~Piece() = default;


int Piece::checkPos(const int& row, const int& col, const Board& board) {

    if (col == getCol() && row == getRow())
        return 0;

    Piece* piece = board.getPiece(row, col);

    if (!piece)
        moveList.add(row, col, m_row, m_col, nullptr);

    else {

        if (isPlayerPiece(piece))
            return 1;

        else {
            moveList.add(row, col, m_row, m_col, piece);
            return 1;
        }
    }

    return 0;
}


Piece * Piece::getPiece(const char& ch, const int& row, const int& col){

    if (!Piece::checkLetter(ch))
        throw InvalidFileCharacterException();

    COLOR color;

    if (islower(ch))
        color = BLACK;
    else
        color = WHITE;

    if (toupper(ch) == '#')
        return nullptr;

    else if (toupper(ch) == _KING)
        return new King(color, row , col);

    else if (toupper(ch) == _QUEEN)
        return new Queen(color, row, col);

    else if (toupper(ch) == _ROOK)
        return new Rook(color, row, col);

    else if (toupper(ch) == _KNIGHT)
        return new Knight(color, row, col);

    else if (toupper(ch) == _BISHOP)
        return new Bishop(color, row, col);

    else if (toupper(ch) == _PAWN)
        return new Pawn(color, row, col);

    else
        return nullptr;

}


bool Piece::checkLetter(const char& ch) {

    if (ch == '#')
        return true;

    auto letter = toupper(ch);

    if (letter == _KING || letter == _QUEEN || letter == _ROOK ||
        letter == _KNIGHT || letter == _BISHOP || letter == _PAWN)
        return true;

    else
        return false;
}


void Piece::printPiece(std::ostream& os) const {

    if (m_color == BLACK)
        os << (char) tolower(getName());

    else
        os << (char) toupper(getName());
}


bool Piece::isPlayerPiece(const Piece* piece) const {

    auto tmp = getColor();

    return tmp == piece->getColor();
}


bool Piece::isPlayerPiece(const COLOR& color) const {

    auto tmp = getColor();

    return tmp == color;
}


FIGURENAME Piece::getName() const {

    return m_name;
}


COLOR Piece::getColor() const {

    return m_color;
}


int Piece::getRow() const {

    return m_row;
}


void Piece::setRow(const int& row) {

    m_row = row;
}


int Piece::getCol() const {

    return m_col;
}


void Piece::setCol(const int& col) {

    m_col = col;
}


int Piece::getValue() const {

    return m_value;
}


void Piece::setValue(const int& value) {

    m_value = value;
}


bool Piece::equals(const FIGURENAME& figName) const {

    auto tmp = tolower(getName());
    return tmp == tolower(figName);
}
