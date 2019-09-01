//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_LOCALPLAYER_HPP
#define CHESS_LOCALPLAYER_HPP

#include "Player.hpp"
#include "GameSession.hpp"


/**
 * Subclass representing a local player
 */
class LocalPlayer : public Player {
public:

    LocalPlayer();

    ~LocalPlayer() override;

    /**
     * Gets command from user.
     * @param session Reference to instance of the game
     * @return command
     */
    Command getCommand(const GameSession& session) override;

    /**
    * Reads command
    * @return command in a form of string
    */
    std::string readInput() const;
};

#endif //CHESS_LOCALPLAYER_HPP
