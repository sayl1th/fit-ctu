//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_COLORMENU_HPP
#define CHESS_COLORMENU_HPP


#include "AbstractMenu.hpp"

/**
 * Menu class for choosing a player's color
 */
class ColorMenu : public AbstractMenu {
public:
    /**
    * Constructor
    * @param Pointer to the previous menu
    */
    explicit ColorMenu(AbstractMenu* menu);

    ~ColorMenu() override;

    /**
     *  Initialize menu
     */
    void initialize(Controller* controller) override;

    /**
    * Set pointer to next menu
    */
    void setNextMenu() override;
};

#endif //CHESS_COLORMENU_HPP
