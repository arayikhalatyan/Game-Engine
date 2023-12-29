EXEC = play

CC = g++

CFLAGS = -lncurses -MMD

SRC = $(wildcard *.cc)

OBJECTS = $(SRC:.cc=.o)

DEPENDS = $(OBJECTS:.o=.d)

${EXEC}: ${OBJECTS}
	${CC} ${OBJECTS} ${CFLAGS} -o ${EXEC}

-include ${DEPENDS}
.PHONY: clean

clean:
	rm *.o *.d ${EXEC}
