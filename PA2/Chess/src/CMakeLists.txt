cmake_minimum_required(VERSION 3.14)
project(Chess)

set(CMAKE_CXX_STANDARD 14)

add_executable(Chess main.cpp AbstractMenu.cpp AbstractMenu.hpp Bishop.cpp Bishop.hpp Board.cpp Board.hpp ColorMenu.cpp ColorMenu.hpp COLORS.hpp Command.cpp Command.hpp Controller.cpp Controller.hpp DifficultyMenu.cpp DifficultyMenu.hpp FilePersistence.cpp FilePersistence.hpp GameData.hpp GameSession.cpp GameSession.hpp MoveList.cpp MoveList.hpp Intelligence.cpp Intelligence.hpp King.cpp King.hpp Knight.cpp Knight.hpp LoadGameMenu.cpp LoadGameMenu.hpp LocalPlayer.cpp LocalPlayer.hpp MainMenu.cpp MainMenu.hpp MyMove.cpp MyMove.hpp NewGameMenu.cpp NewGameMenu.hpp Pawn.cpp Pawn.hpp Persistence.cpp Persistence.hpp Piece.cpp Piece.hpp Player.cpp Player.hpp Position.cpp Position.hpp Queen.cpp Queen.hpp Rook.cpp Rook.hpp COMMANDS.hpp DIFFICULTY.hpp FIGURENAME.hpp Exceptions.hpp)