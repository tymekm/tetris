#ifndef TETROMINO_H
#define TETROMINO_H
#include <array>
#include <ctime>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using std::array;
using std::vector;
enum {down, right, left};
enum {valid, invalid, stuck};

#ifndef COORDS
#define COORDS
struct Coords
{
    int x;
    int y;

    friend bool operator==(const Coords & c1, const Coords & c2)
    {
	return c1.x == c2.x and c1.y == c2.y;
    }
    friend bool operator<(const Coords & c1, const Coords & c2)
    {
        return c1.y < c2.y;
    }
    friend bool operator>(const Coords & c1, const Coords & c2)
    {
        return c1.y > c2.y;
    }
};
#endif

class Tetromino 
{
protected:
public:
    Tetromino();
    int getColor() const { return color; }
    int getState() const { return state; }
    void move(const int dir, vector<Coords> & alreadyOccupied);
    bool rotate();
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
