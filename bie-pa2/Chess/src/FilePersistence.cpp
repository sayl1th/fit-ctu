//
// Created by Jamal Azizov on 2019-05-11.
//


#include "FilePersistence.hpp"
#include "Player.hpp"
#include "Piece.hpp"
#include "Exceptions.hpp"

#include <iostream>
#include <fstream>
#include <climits>


FilePersistence::FilePersistence() : Persistence() {}


FilePersistence::FilePersistence(GameSession* session) : Persistence(session) {}


FilePersistence::~FilePersistence() = default;


void FilePersistence::save() const {

    std::string file;

    std::cout << "Enter a file name" << std::endl;

    std::ofstream ofs;

    while (true) {

        std::cin.clear();
        getline(std::cin,file);
        ofs.open(file);

        if (!std::cin.good() || !ofs.good()) {
            ofs.clear();
            std::cin.clear();
            file.clear();
            std::cout << "Failed to create a file, please enter a different name." << std::endl;
        }
        else
            break;
    }

    std::string line;
    std::string figName;

    for (int i = 7; i >=0; --i) {
        for (int j = 0; j < 8; ++j) {

            Piece* piece = m_gameSession->getBoard().getPiece(i,j);

            if (!piece) {
                line+='#';
                continue;
            }

            if (piece->getColor() == WHITE)
                figName = toupper(piece->getName());

            else
                figName = tolower(piece->getName());

            line += figName;
        }

        line += '\n';
        ofs << line;

        line.clear();
    }
    m_gameSession->player1->printPlayerColor(ofs);
    m_gameSession->currentPlayer->printPlayerColor(ofs);

    std::cout << "The game was successfully saved." << std::endl;
    ofs.close();
}


bool FilePersistence::load(const std::string& file) {

    std::ifstream ifs(file);

    if (!ifs.is_open()) {
        std::cout << "Failed to open the file" << std::endl;
        return false;
    }

    std::string data;

    for (int i = 7; i >= 0; --i) {

        getline(ifs, data, '\n');

        if (!ifs.good())
            throw BadFileReadException();

        for (int j = 0; j < 8; ++j) {

            Piece* piece = nullptr;
            piece = Piece::getPiece(data.at(j), i, j);
            m_gameData.board.setPos(i, j, piece);
        }
    }

    std::string colData;

    ifs >> colData;

    if (colData.size() == 2) {

        if (colData.at(0) == 'W')
            m_gameData.player1col = WHITE;

        else if (colData.at(0) == 'B')
            m_gameData.player1col = BLACK;

        else {
            std::cout << "The wrong file format." << std::endl;
            ifs.close();
            return false;
        }

        if (colData.at(1) == 'W') {
            m_gameData.whosTurn = WHITE;
            ifs.close();
            return true;
        }

        else if (colData.at(1) == 'B') {
            m_gameData.whosTurn = BLACK;
            ifs.close();
            return true;
        }

        else {
            std::cout << "The wrong file format." << std::endl;
            ifs.close();
            return false;
        }
    }

    std::cout << "The wrong file format." << std::endl;
    ifs.close();
    return false;
}







