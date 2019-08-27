SRC = $(wildcard src/*.cpp)
CFLAGS = -Wall -std=c++14
LDFLAGS = -lncurses

tetris: 
	${CXX} ${SRC} ${LDFLAGS} -o $@
