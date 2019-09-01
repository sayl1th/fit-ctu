CXX = g++ -std=c++14 -Wall -pedantic -Wno-long-long -O2
OBJECTS = main.o AbstractMenu.o Bishop.o Board.o ColorMenu.o Command.o Controller.o DifficultyMenu.o FilePersistence.o GameSession.o Intelligence.o King.o Knight.o LoadGameMenu.o LocalPlayer.o MainMenu.o MoveList.o MyMove.o NewGameMenu.o Pawn.o Persistence.o Piece.o Player.o Position.o Queen.o Rook.o 
RM = rm -f
R = -r
OUT = azizojam

all: $(OBJECTS)

main.o: ./src/main.cpp
	$(CXX) -c ./src/main.cpp
	
AbstractMenu.o: ./src/AbstractMenu.cpp ./src/AbstractMenu.hpp
	$(CXX) -c ./src/AbstractMenu.cpp
	
Bishop.o: ./src/Bishop.cpp ./src/Bishop.hpp
	$(CXX) -c ./src/Bishop.cpp
	
Board.o: ./src/Board.cpp ./src/Board.hpp
	$(CXX) -c ./src/Board.cpp
	
ColorMenu.o: ./src/ColorMenu.cpp ./src/ColorMenu.hpp
	$(CXX) -c ./src/ColorMenu.cpp
	
Command.o: ./src/Command.cpp ./src/Command.hpp
	$(CXX) -c ./src/Command.cpp
	
Controller.o: ./src/Controller.cpp ./src/Controller.hpp
	$(CXX) -c ./src/Controller.cpp

DifficultyMenu.o: ./src/DifficultyMenu.cpp ./src/DifficultyMenu.hpp
	$(CXX) -c ./src/DifficultyMenu.cpp

FilePersistence.o: ./src/FilePersistence.cpp ./src/FilePersistence.hpp
	$(CXX) -c ./src/FilePersistence.cpp

GameSession.o: ./src/GameSession.cpp ./src/GameSession.hpp
	$(CXX) -c ./src/GameSession.cpp

Intelligence.o: ./src/Intelligence.cpp ./src/Intelligence.hpp
	$(CXX) -c ./src/Intelligence.cpp

King.o: ./src/King.cpp ./src/King.hpp
	$(CXX) -c ./src/King.cpp

Knight.o: ./src/Knight.cpp ./src/Knight.hpp
	$(CXX) -c ./src/Knight.cpp

LoadGameMenu.o: ./src/LoadGameMenu.cpp ./src/LoadGameMenu.hpp
	$(CXX) -c ./src/LoadGameMenu.cpp

LocalPlayer.o: ./src/LocalPlayer.cpp ./src/LocalPlayer.hpp
	$(CXX) -c ./src/LocalPlayer.cpp

MainMenu.o: ./src/MainMenu.cpp ./src/MainMenu.hpp
	$(CXX) -c ./src/MainMenu.cpp

MoveList.o: ./src/MoveList.cpp ./src/MoveList.hpp
	$(CXX) -c ./src/MoveList.cpp

MyMove.o: ./src/MyMove.cpp ./src/MyMove.hpp
	$(CXX) -c ./src/MyMove.cpp

NewGameMenu.o: ./src/NewGameMenu.cpp ./src/NewGameMenu.hpp
	$(CXX) -c ./src/NewGameMenu.cpp

Pawn.o: ./src/Pawn.cpp ./src/Pawn.hpp
	$(CXX) -c ./src/Pawn.cpp

Persistence.o: ./src/Persistence.cpp ./src/Persistence.hpp
	$(CXX) -c ./src/Persistence.cpp

Piece.o: ./src/Piece.cpp ./src/Piece.hpp
	$(CXX) -c ./src/Piece.cpp

Player.o: ./src/Player.cpp ./src/Player.hpp
	$(CXX) -c ./src/Player.cpp

Position.o: ./src/Position.cpp ./src/Position.hpp
	$(CXX) -c ./src/Position.cpp

Queen.o: ./src/Queen.cpp ./src/Queen.hpp
	$(CXX) -c ./src/Queen.cpp

Rook.o: ./src/Rook.cpp ./src/Rook.hpp
	$(CXX) -c ./src/Rook.cpp

compile: $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(OUT)


run:
	./$(OUT)


clean: $(OUT)
	$(RM) *.o
	$(RM) $(OUT)
