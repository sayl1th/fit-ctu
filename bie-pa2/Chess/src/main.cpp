#include <iostream>
#include "Controller.hpp"


int main() {

    Controller* controller = new Controller();
    controller->showMenu();
    controller->gameStart();

   delete controller;

    return 0;
}