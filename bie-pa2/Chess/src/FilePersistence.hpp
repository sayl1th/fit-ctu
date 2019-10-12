//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_FILEPERSISTENCE_HPP
#define CHESS_FILEPERSISTENCE_HPP

#include "GameData.hpp"
#include "Persistence.hpp"
#include "GameSession.hpp"


/**
 * Subclass for implementing save and load operations
 */
class FilePersistence : public Persistence {
public:

    FilePersistence();

    ~FilePersistence() override;

    explicit FilePersistence(GameSession* session);

    /**
    * Saves the game to a file
    */
    void save() const override;

    /**
    * Loads a game from the given file name
    * @param file Filename to be loaded
    * @return bool True/False if load is successful
    */
    bool load(const std::string& file) override;

private:

    GameData m_gameData;    //struct containing temporary data for game load
    friend class LoadGameMenu;
};

#endif //CHESS_FILEPERSISTENCE_HPP
