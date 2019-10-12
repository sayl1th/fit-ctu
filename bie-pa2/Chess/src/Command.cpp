//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Command.hpp"
#include "GameSession.hpp"
#include "MyMove.hpp"
#include "Pawn.hpp"
#include "Persistence.hpp"
#include "Exceptions.hpp"

#include <string>

Command::Command() : m_command(UNKNOWN) {}


Command::Command(const COMMAND& command) : m_command(command) {}


Command::Command(const MyMove& move) :  m_command(MOVE), m_move(move) {}


void Command::executeCommand(GameSession& session) {

    if (m_command == MOVE)
        moveCommand(session);

    else if (m_command == SAVE)
        saveCommand(session);

    else if (m_command == SURRENDER)
        surrenderCommand(session);

    else if (m_command == CHECK)
        checkCommand(session);

    else if (m_command == TIE)
        tieCommand(session);

    else if (m_command == EXIT)
        exitCommand(session);

    else
        return;
}


void Command::createCommand(const std::string& command) {

    if(command.size() == 5) {

        if(GameSession::checkMove(command)){
            m_command = MOVE;
            MyMove move(command);
            m_move = move;
        }

        else {
            m_command = UNKNOWN;
            throw BadCommandException();
        }
    }

    else if (command == "save")
        m_command = SAVE;

    else if (command == "exit")
        m_command = EXIT;

    else {
        m_command = UNKNOWN;
        throw BadCommandException();
    }
}


void Command::moveCommand(GameSession& session) const {

    MoveList list;
    Piece* piece = session.getBoard().getPiece(m_move.m_fRow,m_move.m_fCol);

    if (!piece) {

        std::cout << "Empty slot, no figure in this position." << std::endl;
        return;
    }

    else if (!(piece->isPlayerPiece(session.currentPlayerColor))) {
        std::cout << "This figure is not yours." << std::endl;
        return;
    }

    else {

        list = piece->findAllMoves(session);

        if (!list.exists(m_move)){
            std::cout << "This move is not possible." << std::endl;
            return;
        }

        if (!session.getBoard().isCheckMove(m_move, session)) {

            std::cout << "This move leads to check, try different move" << std::endl;
            return;
        }
        else {
            session.move(m_move);
            session.getBoard().printBoard();
            session.moveFlag = true;
        }
    }
}


void Command::saveCommand(GameSession& session) const {

    session.persistence->save();
}


void Command::surrenderCommand(GameSession& session) const {

    std::cout << "CHECKMATE! PLAYER " << (session.currentPlayerColor == BLACK ? "WHITE " : "BLACK ") << "HAS WON" << std::endl;
    exitCommand(session);
}


void Command::exitCommand(GameSession& session) const {

    session.exitFlag = true;
}


void Command::checkCommand(GameSession& session) const {

    std::cout << "CHECK! Player " << (session.currentPlayerColor == BLACK ? "BLACK " : "WHITE ") << "is checked" << std::endl;
}


void Command::tieCommand(GameSession& session) const {

    std::cout << "GAME IS TIED, NO ONE WINS!" << std::endl;
    exitCommand(session);
}

