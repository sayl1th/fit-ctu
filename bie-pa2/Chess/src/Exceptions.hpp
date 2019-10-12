//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_EXCEPTIONS_HPP
#define CHESS_EXCEPTIONS_HPP


/**
 *Exception thrown and caught when checking if move is out of the chessboard
 */
class MoveOutOfBoardException{};
/**
 *Exception thrown and caught when loading a game from file fails
 */
class BadFileReadException{};
/**
 *Exception thrown and caught when loading a game from file reads unknown character
 */
class InvalidFileCharacterException{};
/**
 *Exception thrown and caught when user enters invalid input
 */
class BadInputException{};
/**
 *Exception thrown and caught when unknown command is demanded from user
 */
class BadCommandException{};


#endif //CHESS_EXCEPTIONS_HPP
