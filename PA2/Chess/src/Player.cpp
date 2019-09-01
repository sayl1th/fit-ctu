//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Player.hpp"
#include "GameSession.hpp"
#include "King.hpp"


Player::Player() : m_king(nullptr) {}


Player::~Player() = default;


void Player::getAllFigures(const Board &board){

    m_figures.clear();

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {

            if (!board.getPiece(i,j))
                continue;

            else if (board.getPiece(i, j)->isPlayerPiece(m_playerColor))
                m_figures.push_back(board.getPiece(i,j));
        }
    }
}


COLOR Player::getPlayerColor() const {

    return m_playerColor;
}


void Player::printPlayerColor(std::ostream& os) const {

    char c = toupper(getPlayerColor());
    os << c;
}


void Player::setPlayerColor(const COLOR& color) {

    m_playerColor = color;
}


bool Player::isKingChecked(const GameSession &session) const{

    bool tmp = (session.currentPlayer == session.player1);
    return m_king->isChecked(session.getBoard(),tmp);
}


void Player::setKing(King* king) {
    m_king = king;
}
