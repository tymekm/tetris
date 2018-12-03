#ifndef TETROMINO_H
#define TETROMINO_H
#include "Enums.h"
#include <array>
#include <ctime>
#include <vector>
#include <algorithm>
using std::array;
using std::vector;
enum class Direction {down, right, left};
enum class State {valid, invalid, stuck};

class Tetromino 
{
protected:
public:
    Tetromino();
    int getColor() const { return color; }
    State getState() const { return state; }
    void move(Direction dir, vector<Coords> & alreadyOccupied);
    void rotate(vector<Coords> & alreadyOccupied);
    vector<Coords> & getOccupied() { return occByTetr; }
private:
    void fillOccupied(int x, int y);
    State state =  State::valid;
    array<bool, 16> tetArr;
    int color;
    Coords pos;
    int orientation = 0;
    vector<Coords> occByTetr;
    array<array<bool, 16>, 7> tetrominos =
    {{
	 {0,0,1,0,
	  0,1,1,0,
	  0,1,0,0,
	  0,0,0,0
	 },
	 {0,1,0,0,
	  0,1,1,0,
	  0,0,1,0,
	  0,0,0,0
	 },
	 {0,0,0,0,
	  0,1,1,0,
	  0,1,1,0,
	  0,0,0,0
	 },
	 {0,0,1,0,
	  0,1,1,0,
	  0,0,1,0,
	  0,0,0,0
	 },
	 {0,0,0,0,
	  0,1,1,0,
	  0,1,0,0,
	  0,1,0,0
	 },
	 {0,0,0,0,
	  0,1,1,0,
	  0,0,1,0,
	  0,0,1,0
	 },
	 {0,0,1,0,
	  0,0,1,0,
	  0,0,1,0,
	  0,0,1,0
	 }
     }};
};

#endif
