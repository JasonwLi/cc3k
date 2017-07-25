CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -Werror=vla
OBJECTS = TextDisplay.o Tile.o Component.o Enemy.o Player.o Item.o Potion.o Treasure.o Effect.o Effectdeco.o Character.o Game.o Controller.o main.o Stair.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -f *.d *.o

-include ${DEPENDS}
