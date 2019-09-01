//
// Created by Jamal Azizov on 2019-05-11.
//

#include "MyMove.hpp"
#include "Piece.hpp"

MyMove::MyMove() : m_fRow(-1), m_fCol(-1), m_toRow(-1), m_toCol(-1), m_piece(nullptr) {}


MyMove::MyMove(const std::string& move) {

    m_fRow = move.at(0) - 48;
    m_fCol = move.at(1) - 49 - 48;

    m_toRow = move.at(3) - 48;
    m_toCol = move.at(4) - 49 - 48;

    m_piece = nullptr;
}


MyMove::MyMove(const int& toRow, const int& toCol, const int& fRow, const int& fCol, Piece* piece) : m_fRow(fRow), m_fCol(fCol) ,m_toRow(toRow), m_toCol(toCol), m_piece(piece) {}


bool MyMove::isfMove() const {

    if (m_fRow == -1)
        return true;

    return false;
}


void MyMove::printMove() const {

    std::cout<< "Player moves from [" << m_fRow <<"," << m_fCol << "] to [" << m_toRow << "," << m_toCol << "]";

    if (m_piece) {

        std::cout<<" and takes figure: ";
        m_piece->printPiece(std::cout);
    }

    std::cout << std::endl;
}

