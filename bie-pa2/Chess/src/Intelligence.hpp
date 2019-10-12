//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_INTELLIGENCE_HPP
#define CHESS_INTELLIGENCE_HPP

#include "DIFFICULTY.hpp"
#include "Player.hpp"


/**
 * Subclass representing AI
 */
class Intelligence : public Player {
public:
    Intelligence();

    ~Intelligence() override;

    /**
    * @param difficulty Desired level of difficulty
    */
    explicit Intelligence(const int& difficulty);

    /**
     * Changes the difficulty
     * @param difficulty New difficulty level
     */
    void changeDifficulty(const int& difficulty);

    /**
    * Gets command from AI
    * @param session Reference to instance of the game
    * @return Command
    */
    Command getCommand(const GameSession& session) override;

    /**
     * Gets move from AI
     * @param session Reference to instance of the game
     * @return Move
     */
    MyMove getMove(const GameSession& session);

private:

    /**
    * Removes all check moves from the list of all possible moves
    * @param list Reference to list of moves
    * @param session Reference to the instance of the game
    */
    void removeAllCheckMoves(MoveList& list, const GameSession& session);

    /**
     * Finds index of the best move in the list of all possible moves
     * @param list Reference to the list of moves
     * @param board Reference to the board
     * @return index of the best move
     */
    int getBestMoveIndex(MoveList& list, const Board& board) const;

    int m_difficulty; //difficulty
};

#endif //CHESS_INTELLIGENCE_HPP
