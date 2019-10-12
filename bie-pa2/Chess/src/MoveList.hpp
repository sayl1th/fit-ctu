//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_MOVELIST_HPP
#define CHESS_MOVELIST_HPP

#include "MyMove.hpp"

#include <vector>
#include <iostream>

class Piece;

class MoveList {
public:
    /**
     * Constructor
     * @param moves length of the moves vector to reserve
     */
    explicit MoveList(const int& moves = 40);

    virtual ~MoveList();


    void reserve(const int& val);

    /**
    * adds 2 list of moves
    * @param list Reference to the list of moves
    */
    void concatenate(const MoveList& list);

    /**
    * Checks whether given move exists
    * @param move Given move
    */
    bool exists(const MyMove& move) const;

    /**
     * Adds a move
     * @param toRow Destination row of the move
     * @param toCol Destination column of the move
     * @param fRow  Origin row of the move
     * @param fCol Origin column of the move
     * @param piece Figure taken by the move
     */
    void add(const int& toRow, const int& toCol, const int& fRow, const int& fCol, Piece* piece);

    /**
     *Adds a move
     */
    void add(MyMove move, Piece* piece = nullptr);

    /**
    * deletes the list of moves
    */
    void deleteMoves();

    /**
     * Checks the list of moves
     */
    bool isEmpty() const;

    /**
     * Returns a move in the list of moves
     * @param pos index of the move
     * @return Move to a given position
     */
    MyMove getMove(const int& pos) const;

    /**
     * Returns size of moves vector
     * @return size of moves vector
     */
    size_t size() const;

    std::vector<MyMove> m_moves;
    int m_numOfMoves;
};


#endif //CHESS_MOVELIST_HPP
