//
// Created by Jamal Azizov on 2019-05-11.
//

#ifndef CHESS_ABSTRACTMENU_HPP
#define CHESS_ABSTRACTMENU_HPP

#include <iostream>

class Controller;

/**
 * Abstract class for all menu classes
 */
class AbstractMenu {
public:
    /**
     * Constructor
     * @param Pointer to the previous menu
     */
    explicit AbstractMenu(AbstractMenu* menu);

    virtual ~AbstractMenu();


    /**
     *  Initializes menu
     */
    virtual void initialize(Controller* controller) = 0;

    /**
    * Set pointer to next menu
    */
    virtual void setNextMenu() = 0;

    /**
     * Read input from the user
     */
    virtual int readInput();

    /**
    *  Print menu title and menu items
    */
    virtual void printMenu() const;

    /**
     *  Print single menu item
     */
    void printItem(const int& item) const;

    AbstractMenu* nextMenu;     // pointer to the next menu
    AbstractMenu* prevMenu;     // pointer to the previous menu

protected:
    /**
    *  Print title of the current menu
    */
    void printTitle() const;

    /**
     *  Checks if the chosen option is valid
     * @param item index of menu item
     */
    bool checkChoice(const int& item) const;

    /**
     * Sets number of items in the menu
     */
    void setNumOfItems();

    int m_choice;               // index of chosen menu item of user
    int m_numOfItems;           // number of items in the menu
    std::string m_title;        // the title of the menu
    std::string m_items[5];    // container of items of the menu

};

#endif //CHESS_ABSTRACTMENU_HPP

