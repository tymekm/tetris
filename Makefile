all:
	g++ -Wall -std=c++14 -lncurses main.cpp Render.cpp Tetris.cpp Tetromino.cpp -o tetris
