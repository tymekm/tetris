SRC = $(wildcard src/*.cpp)
CFLAGS = -g -Wall -std=c++14
LDFLAGS = -lncurses
BINARY = tetris

all: ${BINARY}

${BINARY}: 
	${CXX} ${SRC} ${LDFLAGS} -o $@

clean :
	${RM} ${BINARY} 
