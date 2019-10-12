//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_BOARD_HPP
#define CHESS_BOARD_HPP

#include "COLORS.hpp"
#include "Position.hpp"

class MyMove;
class GameSession;
class King;

class Piece;
class Position;

/**
 * Class represents a chessboard
 */

class Board {

public:

    Board();

    Board(const Board& rhs);

    /**
    * Creates all pieces of the chessboard
    * @param color The color of figures on the upper side of the board
    */
    void createPieces(const COLOR& color);

    /**
     * Prints the whole board
     */
    void printBoard() const;

    /**
     * Moves the piece
     * @param move Move to be performed
     */
    void movePiece(const MyMove& move);

    /**
    * Checks if the given move result a check of king
    * @param move Move to be performed
    * @param session Reference to the game instance
    * @return True/False if the move is valid
    */
    bool isCheckMove(const MyMove& move, const GameSession& session) const;

    /**
     * Finds the king of player
     * @param color The color of player
     * @return Pointer to found king
     */
    King* findKing(const COLOR& color) const;

    /**
     * Returns a piece on the given position
     * @param row Row of the position
     * @param col Column of the position
     * @return Pointer to piece
     */
    Piece* getPiece(const int& row, const int& col) const;

    /**
     * Checks whether if the given position is valid
     * @param row Row of the position
     * @param col Column of the position
     * @return True/False if given position is valid
     */

    bool outOfBoard(const int& row, const int& col) const;

    /**
     * Sets given piece in the given position
     * @param row Row of the position
     * @param col Column of the position
     * @param piece Pointer to the piece
     */

    void setPos(const int& row, const int& col, Piece* piece);

    /**
     * Returns a value of a given position
     * @param row Row of the position
     * @param col Column of the position
     * @return Value of the position
     */
    int getPosValue(const int& row, const int& col) const;

    /**
     * Copies the existing board
     * @param rhs Given board
     */
    void copy(const Board& rhs);


    int startRowUp;    // The starting row of the pawns on the upper side of the board
    int startRowDown;  // The starting row of the pawns on the lower side of the board
    int lastRowUp;    // The last row of the pawns on the upper side of the board
    int lastRowDown;  // The last row of the pawns on the lower side of the board

private:

    /**
     * Promotes a pawn to queen
     * @param move The move of a pawn
     */
    void promote(const MyMove &move);

    Position m_positions[8][8];   // 2D array of the positions holding the figures
};

#endif //CHESS_BOARD_HPP
