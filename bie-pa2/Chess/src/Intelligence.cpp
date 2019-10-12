//
// Created by Jamal Azizov on 2019-05-11.
//

#include "Intelligence.hpp"
#include "Command.hpp"
#include "Piece.hpp"


Intelligence::Intelligence() : m_difficulty(0) {}

Intelligence::Intelligence(const int& difficulty) : m_difficulty(difficulty) {}

Intelligence::~Intelligence() = default;


void Intelligence::changeDifficulty(const int& difficulty ) {

    m_difficulty = difficulty;
}


void Intelligence::removeAllCheckMoves(MoveList& list, const GameSession& session){

    MoveList list1;

    for (size_t i = 0; i < list.size(); ++i) {

        MyMove move = list.getMove(i);

        if(session.getBoard().isCheckMove(move, session))
            list1.add(move,move.m_piece);
    }

    list.deleteMoves();
    list.concatenate(list1);
}

int Intelligence::getBestMoveIndex(MoveList& list, const Board& board) const {

    if (m_difficulty == 0){
        srand(time(nullptr));
        return rand() % (m_allMoves.size());
    }

    int bestValPiece = 0;
    int bestValPos = 0;
    int bestValueTotal = 0;
    int bestIdxPiece = 0;
    int bestIdxPos = 0;
    int bestIdxTotal = 0;


    for (size_t i = 0; i < list.size(); i++) {

        Piece* piece = list.getMove(i).m_piece;

        if (!piece)
            continue;

        int val = (piece->getValue()) * 10;

        if (val > bestValPiece){
            bestValPiece = val;
            bestIdxPiece = i;
        }
    }

    for (size_t i = 0; i < list.size(); i++) {

        MyMove move = list.getMove(i);
        int val = board.getPosValue(move.m_toRow, move.m_toCol);

        if (val > bestValPos) {
            bestValPos = val;
            bestIdxPos = i;
        }

        if (!list.getMove(i).m_piece)
            continue;

        else {

            if (list.getMove(i).m_piece->getValue() * 10 + val > bestValueTotal){
                bestValueTotal = list.getMove(i).m_piece->getValue() * 10 + val;
                bestIdxTotal = i;
            }
        }
    }

    if(m_difficulty == 1)
        return bestValPiece > bestValPos ? bestIdxPiece : bestIdxPos;

    if( (bestValueTotal >= bestValPiece && bestValPiece >= bestValPos)
        || (bestValueTotal >= bestValPos && bestValPos >= bestValPiece ) )
        return bestIdxTotal;

    else
        return bestValPiece > bestValPos ? bestIdxPiece : bestIdxPos;
}


MyMove Intelligence::getMove(const GameSession& session) {

    m_allMoves.deleteMoves();

    MoveList list;

    getAllFigures(session.getBoard());

    for (size_t i = 0; i < m_figures.size(); ++i) {

        list = m_figures.at(i)->findAllMoves(session);
        m_allMoves.concatenate(list);
    }

    removeAllCheckMoves(m_allMoves, session);

    if (m_allMoves.isEmpty())
        return MyMove(-1,-1,-1,-1);


    int bestIdx = getBestMoveIndex(m_allMoves, session.getBoard());

    return m_allMoves.getMove(bestIdx);
}

Command Intelligence::getCommand(const GameSession& session) {

    MyMove move = getMove(session);

    if (move.isfMove())
        return Command(SURRENDER);

    move.printMove();
    return Command(move);
}


