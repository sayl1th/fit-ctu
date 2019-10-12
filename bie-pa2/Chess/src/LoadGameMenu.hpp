//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_LOADGAMEMENU_HPP
#define CHESS_LOADGAMEMENU_HPP


#include "AbstractMenu.hpp"
#include "Controller.hpp"
#include "FilePersistence.hpp"


/**
 * Subclass for loading a saved game
 */
class LoadGameMenu : public AbstractMenu {
public:

    explicit LoadGameMenu(AbstractMenu* menu);

    ~LoadGameMenu() override;

    /**
     *  Initializes menu
     */
    void initialize(Controller* controller) override;

    /**
    * Set pointer to next menu
    */
    void setNextMenu() override;

    /**
     * Read input from the user
     */
    int readInput() override;

    /**
    *  Print menu title and menu items
    */
    void printMenu() const override;

    /**
    * Looks for the file to load
    * @param file Name of the file
    * @return bool true if the file exists
    */
    bool findFile(const std::string& file) const;

    /**
    * Calls function to load the game
    * @param file Name of file
    */
    void loadFile(const std::string& file);

    /**
     * Asks user to confirm loading the file
     */
    bool confirmLoad();

private:

    FilePersistence* m_persistence; // pointer to an instance of persistence
    std::string m_fileName;    // name of the file
    bool m_loadFlag;    // flag for successful load
};

#endif //CHESS_LOADGAMEMENU_HPP
