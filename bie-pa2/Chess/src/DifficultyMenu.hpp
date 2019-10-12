//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_DIFFICULTYMENU_HPP
#define CHESS_DIFFICULTYMENU_HPP


#include "AbstractMenu.hpp"

/**
 * Subclass menu for choosing difficulty of AI
 */
class DifficultyMenu : public AbstractMenu {
public:

    /**
    * constructor
    * @param Pointer to the previous menu
    */
    explicit DifficultyMenu(AbstractMenu* menu);

    ~DifficultyMenu() override;

    /**
     *  Initializes menu
     */
    void initialize(Controller* controller) override;

    /**
    * Sets pointer to next menu
    */
    void setNextMenu() override;
};


#endif //CHESS_DIFFICULTYMENU_HPP
