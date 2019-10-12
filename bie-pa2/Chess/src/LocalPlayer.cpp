//
// Created by Jamal Azizov on 2019-05-11.
//

#include "LocalPlayer.hpp"
#include "Exceptions.hpp"
#include "Command.hpp"

#include <climits>


LocalPlayer::LocalPlayer() = default;

LocalPlayer::~LocalPlayer() = default;


Command LocalPlayer::getCommand(const GameSession& session) {

    Command command;
    std::string commandstr;

    try {

        std::cout << "Now move of " << (session.currentPlayerColor == WHITE ? "WHITE" : "BLACK") << std::endl;
        std::cout << "Enter the command" << std::endl;
        commandstr = readInput();

    } catch(BadInputException & ex) {
        std::cout << "Invalid command" << std::endl;
        return Command(UNKNOWN);
    }

    try {
        command.createCommand(commandstr);
    } catch(BadCommandException & ex) {
        std::cout << "Invalid command" << std::endl;
        return Command(UNKNOWN);
    }
    return command;
}


std::string LocalPlayer::readInput() const{

    std::string input;

    getline(std::cin,input);

    if (!std::cin.good() || input.empty())
        throw BadInputException();


    return input;
}


