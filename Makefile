# Makefile
LDFLAGS= -lncurses
CXXFLAGS=-Wall -pedantic -Wno-long-long -O0 --std=c++11 -ggdb
CXX=g++
RM=rm -rf
OBJECTS=bin/Object.o bin/Booster.o bin/Box.o bin/Bomb.o bin/Fire.o bin/PlayerObject.o bin/Wall.o bin/Point.o bin/Map.o bin/HumanPlayer.o bin/AiPlayer.o bin/Player.o bin/WindowNcurses.o bin/NcursesUI.o bin/Game.o bin/Configuration.o bin/HighScoresManager.o bin/LevelLoader.o bin/Application.o

all: $(OBJECTS)
	make compile
	make doc

run: bomberman
	./bomberman

compile: ./bomberman

clean:
	$(RM) ./bomberman bin doc

doc: src/*
	doxygen Doxyfile > /dev/null 2> /dev/null

bin/Object.o:
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Objects/Object.cpp -o bin/Object.o

bin/Booster.o:
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Objects/Booster/Booster.cpp -o bin/Booster.o

bin/Bomb.o:
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Objects/Bomb.cpp -o bin/Bomb.o

bin/Box.o: bin/Object.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Objects/Box.cpp -o bin/Box.o

bin/Fire.o: bin/Object.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Objects/Fire.cpp -o bin/Fire.o

bin/PlayerObject.o: bin/Object.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Objects/PlayerObject.cpp -o bin/PlayerObject.o

bin/Wall.o: bin/Object.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Objects/Wall.cpp -o bin/Wall.o

bin/Point.o: bin/Object.o bin/Bomb.o bin/Box.o bin/Fire.o bin/PlayerObject.o bin/Wall.o bin/Booster.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Point.cpp -o bin/Point.o

bin/Map.o: bin/Point.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Map.cpp -o bin/Map.o

bin/Player.o: bin/Map.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Player.cpp -o bin/Player.o

bin/HumanPlayer.o: bin/Map.o bin/Player.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/HumanPlayer.cpp -o bin/HumanPlayer.o

bin/AiPlayer.o: bin/Map.o bin/Player.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/AiPlayer.cpp -o bin/AiPlayer.o

bin/WindowNcurses.o: bin/Map.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Graphics/WindowNcurses.cpp -o bin/WindowNcurses.o

bin/NcursesUI.o: bin/WindowNcurses.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Graphics/NcursesUI.cpp -o bin/NcursesUI.o

bin/Game.o: bin/Map.o bin/Map.o bin/Player.o bin/AiPlayer.o bin/HumanPlayer.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Game/Game.cpp -o bin/Game.o

bin/Configuration.o:
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Configuration.cpp -o bin/Configuration.o

bin/HighScoresManager.o: bin/Configuration.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Utils/HighScoresManager.cpp -o bin/HighScoresManager.o

bin/LevelLoader.o: bin/Map.o bin/Game.o bin/Configuration.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Utils/LevelLoader.cpp -o bin/LevelLoader.o

bin/Application.o: bin/NcursesUI.o bin/HighScoresManager.o bin/LevelLoader.o bin/Configuration.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/Application.cpp -o bin/Application.o

bin/main.o: bin/Application.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) -c src/main.cpp -o bin/main.o $(LDFLAGS)

bomberman: bin/main.o
	mkdir -p bin/
	$(CXX) $(CXXFLAGS) bin/main.o $(OBJECTS) -o bomberman $(LDFLAGS)
