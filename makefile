CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess.out
OBJECTS = main.o chess.o ./game/board.o ./game/game.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
