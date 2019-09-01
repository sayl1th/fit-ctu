//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_MYMOVE_HPP
#define CHESS_MYMOVE_HPP

#include <iostream>

class Piece;

class MyMove {
public:

    MyMove();

    explicit MyMove(const std::string& move);


    MyMove(const int& toRow, const int& toCol, const int& fRow = -1,const int& fCol = -1, Piece* piece = nullptr);

    /**
     * Prints a move
     */
    void printMove() const;
    /**
     * Checks whether the move is a fixed move
     */
    bool isfMove() const;

    int m_fRow;
    int m_fCol;  
    int m_toRow;   
    int m_toCol;   

    Piece* m_piece;
};



#endif //CHESS_MYMOVE_HPP
