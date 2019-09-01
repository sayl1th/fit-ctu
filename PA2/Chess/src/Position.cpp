//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Position.hpp"

Position::Position() : m_posValue(0), m_posPiece(nullptr) {}

Position::~Position() {

    delete m_posPiece;
}

int Position::getPosValue() const {

    return m_posValue;
}

void Position::setPosValue(const int& value) {

    m_posValue = value;
}

Piece * Position::getPosPiece() const {

    return m_posPiece;
}

void Position::setPosPiece(Piece* piece) {

    m_posPiece = piece;
}








