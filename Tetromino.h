#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <algorithm>
#include "Enums.h"
using std::array;
using std::vector;
enum {down, right, left};
enum {valid, invalid, stuck};

class Tetromino 
{
protected:
public:
    Tetromino();
    int getColor() const { return color; }
    int getState() const { return state; }
    void move(const int dir, vector<Coords> & alreadyOccupied);
    void rotate(vector<Coords> & alreadyOccupied);
    vector<Coords> & getOccupied() { return occByTetr; }
private:
    void fillOccupied(int x, int y);
    int state =  valid;
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
