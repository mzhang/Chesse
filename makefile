CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD
EXEC = chess.out
OBJECTS = main.o chess.o \
./game/board.o ./game/game.o \
./moveable/piece.o ./moveable/moveable.o ./moveable/decorator.o ./moveable/moveX.o ./moveable/moveY.o ./moveable/moveZ.o ./moveable/moveL.o \
./graphics/chess_drawing.o ./graphics/sdl_wrap.o \
./data/pieceType.o ./data/move.o ./data/position.o \
./computer/computer.o ./computer/level_1.o ./computer/level_2.o ./computer/level_3.o ./computer/sophisticated.o 

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lSDL -lSDL_image -lSDL_ttf

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
