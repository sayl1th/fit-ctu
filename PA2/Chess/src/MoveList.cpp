//
// Created by Jamal Azizov on 2019-05-11.
//

#include "MoveList.hpp"
#include "Piece.hpp"

MoveList::MoveList(const int& moves) : m_numOfMoves(0) {

    m_moves.reserve(moves);
    m_moves.clear();
}


MoveList::~MoveList() = default;

void MoveList::reserve(const int& val) {

    m_moves.reserve(val);
}


bool MoveList::exists(const MyMove& move) const {

    for (size_t i = 0; i < m_moves.size(); ++i) {

        if (m_moves.at(i).m_toRow == move.m_toRow && m_moves.at(i).m_toCol == move.m_toCol)
            return true;
    }

    return false;
}


void MoveList::concatenate(const MoveList& list) {

    for (size_t i = 0; i < list.m_moves.size(); ++i)
        add(list.getMove(i),list.getMove(i).m_piece);

    m_numOfMoves = m_moves.size();
}


void MoveList::add(MyMove move, Piece* piece) {

    move.m_piece = piece;
    m_moves.push_back(move);
    m_numOfMoves++;
}


void MoveList::add(const int& toRow, const int& toCol, const int& fRow, const int& fCol, Piece* piece) {

    m_moves.emplace_back(MyMove(toRow, toCol, fRow, fCol, piece));
    m_numOfMoves++;
}


void MoveList::deleteMoves() {

    m_numOfMoves=0;
    m_moves.clear();
}


bool MoveList::isEmpty() const {

    return m_numOfMoves == 0;
}


MyMove MoveList::getMove(const int& pos) const {

    return m_moves.at(pos);
}


size_t MoveList::size() const {
    return m_moves.size();
}
