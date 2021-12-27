CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -g
EXEC = straights
OBJECTS = card.o deck.o main.o observer.o player.o subject.o table.o addtext.o gamecontroller.o gamestate.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
