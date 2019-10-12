//
// Created by Jamal Azizov on 2019-05-11.
//
#include "MyMove.hpp"

#include "FilePersistence.hpp"
#include "Player.hpp"
#include "Piece.hpp"

#include <climits>
#include <fstream>

GameSession::GameSession():  fileName(""), player1(nullptr), player2(nullptr),
                             currentPlayer(nullptr), readyFlag(false), exitFlag(false),
                             moveFlag(false), moveTurnColor(WHITE), currentPlayerColor(WHITE) {

    persistence = new FilePersistence(this);
}

GameSession::~GameSession() {

    sessionEnd();
}


void GameSession::sessionEnd() {

    delete player1;
    delete player2;
    delete persistence;

    player1 = player2 = nullptr;
    persistence = nullptr;
}

void GameSession::sessionStart() {

    if (fileName.empty())
        m_board.createPieces(player1->getPlayerColor());

    getKings();
    m_board.printBoard();

    exitFlag = false;
}

bool GameSession::checkMove(const std::string& move) {

    if (!checkPos(move.substr(0, 2)) || !checkPos(move.substr(3))
       || move.at(2) != ' ')
        return false;

    return true;
}

bool GameSession::checkPos(const std::string& move) {

    if (move.at(0) < '0' || move.at(0) > '7' || move.at(1) < 'a' || move.at(1) > 'h')
        return false;

    return true;
}

void GameSession::setColors(const COLOR& color) {

    player1->setPlayerColor(color);

    if (color == BLACK) {
        player2->setPlayerColor(WHITE);
        currentPlayer = player2;
    }
    else{
        player2->setPlayerColor(BLACK);
        currentPlayer = player1;
    }

    currentPlayerColor = WHITE;
}


void GameSession::switchPlayers() {

    if (currentPlayerColor == WHITE)
        moveTurnColor = currentPlayerColor = BLACK;
    else
        moveTurnColor = currentPlayerColor = WHITE;

    if (currentPlayer == player1)
        currentPlayer = player2;
    else
        currentPlayer = player1;
}



bool GameSession::isCheckMate() const {

    currentPlayer->getAllFigures(m_board);

    MoveList list;

    for (size_t i = 0; i < currentPlayer->m_figures.size(); ++i){

        MoveList tmp = currentPlayer->m_figures.at(i)->findAllMoves(*this);
        list.concatenate(tmp);
    }

    if (list.isEmpty())
        return true;

    for (size_t i = 0; i < list.size(); ++i){

        if (m_board.isCheckMove(list.getMove(i), *this))
            return false;
    }

    return true;
}

bool GameSession::isTie() const {

    player1->getAllFigures(m_board);
    player2->getAllFigures(m_board);

    return ((player1->m_figures.size() +  player2->m_figures.size()) == 2);
}


bool GameSession::move(const MyMove& move){

    m_board.movePiece(move);
    return true;
}

void GameSession::getKings() {

    COLOR color = player1->getPlayerColor();

    player1->setKing(m_board.findKing(color));

    color = player2->getPlayerColor();
    player2->setKing( m_board.findKing(color));
}


const Board& GameSession::getBoard() const {

    return m_board;
}

void GameSession::setGameReady() {

    readyFlag = true;
}

bool GameSession::isGameReady() const {

    return readyFlag;
}

void GameSession::setMoveTurn(const COLOR& color) {

    currentPlayerColor = moveTurnColor = color;
}

