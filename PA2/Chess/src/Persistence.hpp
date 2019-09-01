//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_PERSISTENCE_HPP
#define CHESS_PERSISTENCE_HPP

#include <iostream>

class GameSession;
/**
 * An abstract parent class for handling different save/load techniques
 */
class Persistence {
public:

    Persistence();

    explicit Persistence(GameSession* session);

    virtual ~Persistence();

    /**
     * abstract function to save the game
     */
    virtual void save() const = 0;

    /**
     * abstract function to load the game
     * @param file name of the file
     */
    virtual bool load(const std::string& file) = 0;

protected:

    GameSession* m_gameSession; // pointer to instance of the game
};


#endif //CHESS_PERSISTENCE_HPP
