#ifndef TETROMINO_H
#define TETROMINO_H
#include "Enums.h"
#include <array>
#include <ctime>
#include <vector>
#include <algorithm>
using std::array;
using std::vector;

enum class Direction {down, right, left, rotate};
enum class State {valid, invalid, stuck};

class Tetromino
{
protected:
public:
    Tetromino();
    int getColor() const { return color; }
    State getState() const { return state; }
    void makeValid() { state = State::valid; }
    void move(Direction dir, vector<Coords> & alreadyOccupied);
    void rotate(vector<Coords> & alreadyOccupied);
    vector<Coords> & getOccupied() { return occByTetr; }
    vector<Coords> & getPreview() { return preview; }
    static int randCounter;
private:
    void fillOccupied(int x, int y);
    void fillPreview();
    State state =  State::valid;
    array<bool, 16> tetArr;
    int color;
    Coords pos;
    int orientation = 0;
    vector<Coords> occByTetr;
    vector<Coords> preview;
    static const array<array<bool, 16>, 7> tetrominos;
};

#endif
