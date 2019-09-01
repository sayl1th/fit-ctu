//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_PIECE_HPP
#define CHESS_PIECE_HPP

#include "COLORS.hpp"
#include "FIGURENAME.hpp"
#include "MoveList.hpp"

class GameSession;

class Board;


class Piece {
public:

    Piece();

    Piece(const COLOR& color, const int& row, const int& col);

    virtual ~Piece();

    /**
    * Virtual function to make a copy of the piece
    * @param piece a pointer to the given piece
    * @return a new instance of a piece
    */
    virtual Piece* clone(const Piece* piece) const = 0;

    /**
    * Virtual function to find all moves of the given piece
    * @param session Reference to the instance of the game
    * @return Reference to the list of all possible moves
    */
    virtual MoveList& findAllMoves(const GameSession& session) = 0;

    /**
    *  Checks if the piece can move to given position
    * @param row a row of the position
    * @param col a column of the position
    * @param board reference to the chessboard
    *  @return 0 for positive answer, 1 for negative
    */
    virtual int checkPos(const int& row, const int& col, const Board& board);

    /**
     * Getter for the piece
     * @param ch A letter identifying a piece
     * @param row A row position f a piece
     * @param col A column position of the piece
     * @return Pointer to the piece
     */
    static Piece* getPiece(const char& ch, const int& row, const int& col);

    /**
     * Checks whether a given letter is valid
     * @param ch letter to be checked
     */
    static bool checkLetter(const char& ch);


    /**
     *  Prints the piece into a given stream
     * @param os stream to be written into
     */
    void printPiece(std::ostream& os) const;


    /**
    *  Checks if a given piece is a player's piece
    * @param piece a pointer to the given piece
    */
    bool isPlayerPiece(const Piece* piece) const;

    /**
     *  Checks if the piece is a player's piece
     * @param color Color of the given piece
     */
    bool isPlayerPiece(const COLOR& color) const;


    FIGURENAME getName() const;

    COLOR getColor() const;

    int getRow() const;

    void setRow(const int& row);

    int getCol() const;


    void setCol(const int& col);

    int getValue() const;

    void setValue(const int& value);

    bool equals(const FIGURENAME& figName) const;

    MoveList moveList;  //List of possible moves of a piece

protected:
    COLOR m_color;          // Color of the piece
    FIGURENAME m_name;    // Name of the piece
    int m_row;            // Row of the piece
    int m_col;           // Column of the piece
    int m_value;         // value of the piece

};


#endif //CHESS_PIECE_HPP
