CXX = g++
CXXFLAGS = -g -std=c++14 -Wall -MMD -Ofast
EXEC = chess.out
OBJECTS = main.o chess.o \
./game/board.o ./game/game.o ./game/gameState.o ./game/gameHistory.o \
./moveable/piece.o ./moveable/moveable.o ./moveable/decorator.o ./moveable/pieceFactory.o \
./moveable/moveX.o ./moveable/moveY.o ./moveable/moveDiagNeg.o ./moveable/moveDiagPos.o \
./moveable/moveL.o ./moveable/pawnRules.o ./moveable/castle.o \
./moveable/golem.o ./moveable/nuke.o \
./graphics/chessDrawing.o ./graphics/screen.o \
./outputs/output.o ./outputs/textDisplay.o ./outputs/visualizer.o \
./data/pieceType.o ./data/move.o ./data/position.o ./data/playerColor.o ./data/completedMove.o \
./players/player.o ./players/human.o ./players/computer1.o ./players/computer2.o ./players/computer3.o ./players/computer4.o

DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC} -lSDL -lSDL_image -lSDL_ttf

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
