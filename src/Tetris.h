#ifndef TETRIS_H
#define TETRIS_H 
#include "Render.h"
#include "Tetromino.h"
#include "Enums.h"
#include <memory>
#include <chrono>
#include <thread>

enum class GameState {running, paused, gameover};

class Tetris 
{
    private:
	std::unique_ptr<Tetromino> piece;
	std::unique_ptr<Tetromino> nextPiece;
	Render screen;
	GameState state = GameState::running;
	vector<Coords> occupiedSpace;
	unsigned int totScore = 0;
	int linesCleared = 0;
	int lineCounter = 0;
	int level = 10;
	void initOccupied();
	void drawPiece(const vector<Coords> & oldOccupied);
	void checkForLines();
	void handleLines(const vector<int> & l);
	void addScore(const int l);
	void checkLevelUp(const int l);
    public:
	Tetris(const int h = 25, const int w = 13);
	vector<Coords> & getOccupied() { return occupiedSpace; }
	GameState movePiece(Direction dir = Direction::down);
	void rotatePiece();
	void pause();
	int getLevel() { return level; }
	GameState getState() { return state; }
	int getScore() { return totScore; }
};

#endif
