CXX = g++
CXXFLAGS = -g -Wall -std=c++11 -Werror=vla
OBJECTS = Controller.o Game.o Enemy.o Player.o TextDisplay.o Tile.o Component.o Item.o Potion.o Treasure.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = cc3k

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm -f *.d *.o

-include ${DEPENDS}