//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_GAMEDATA_HPP
#define CHESS_GAMEDATA_HPP

#include "Board.hpp"
#include "COLORS.hpp"

struct GameData {

    Board board;
    COLOR player1col;
    COLOR whosTurn;

};


#endif //CHESS_GAMEDATA_HPP
