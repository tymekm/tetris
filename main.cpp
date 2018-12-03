#include <iostream>
#include <chrono>
#include <thread>
#include <ctime>
#include <utility>
#include <memory>
#include <vector>

#include "Render.h"
#include "Tetromino.h"

const int HEIGHT = 18;
const int WIDTH = 12;

using std::array;
using std::wstring;
using std::unique_ptr;

void gameLoop(Render & screen);
vector<Coords> initOccupied(const int h, const int w);
vector<Coords> getLines(vector<Coords> & occupied);
bool sortCoords(const Coords & c1, const Coords & c2);

int main()
{
    std::vector<Coords> test = {{1,2}, {2,3}};
    std::srand(std::time(0));
    Render screen(HEIGHT, WIDTH);
    gameLoop(screen);
    endwin();
}

void gameLoop(Render & screen)
{
    vector<Coords> occupiedSpace = initOccupied(HEIGHT, WIDTH);
    unique_ptr<Tetromino> piece(new Tetromino);
    int ch;
    screen.Draw(playWin, piece.get()->getOccupied(), 
	    piece.get()->getColor());
    while (true)
    {	
	ch = getch();
	switch (ch) 
	{
	    case KEY_DOWN:
		piece->move(down, occupiedSpace);
		break;
	    case KEY_LEFT:
		piece->move(left, occupiedSpace);
		break;
	    case KEY_RIGHT:
		piece->move(right, occupiedSpace);
		break;
	}
	if (piece.get()->getState() != stuck)
	    screen.clearLastDraw(piece.get()->getOccupied());
	screen.Draw(playWin, piece.get()->getOccupied(), 
		piece.get()->getColor());
	if (piece.get()->getState() == stuck)
	{
	    occupiedSpace.insert(occupiedSpace.end(),
		piece.get()->getOccupied().begin(),
		piece.get()->getOccupied().end());
	    vector<Coords> tempFullLines = getLines(occupiedSpace);
	    if (!tempFullLines.empty())
	    {
		screen.Draw(playWin, getLines(occupiedSpace), line, '=');
	    }
	    piece.reset(new Tetromino);
	    screen.Draw(playWin, piece.get()->getOccupied(),
		    piece.get()->getColor());
	}
	//std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

vector<Coords> initOccupied(const int h, const int w)
{
    vector<Coords> occupiedSpace;
    for (int y = 0; y <= h; y++) 
        for (int x = 0; x <= w; x++) 
	    if (y == h - 1 or x == 0 or x == w - 1) 
		occupiedSpace.push_back({x,y});
    return occupiedSpace;
}

vector<Coords> getLines(vector<Coords> & occupied)
{
    std::sort(occupied.begin(), occupied.end(), sortCoords);
    vector<Coords> lines;
    int count = 0;
    for (int y = 0; y < HEIGHT; y++) 
    {
        count = count_if(occupied.begin(), occupied.end(),
		[&y](Coords & a)->int { return a.y == y;});
	if (count == WIDTH)
	    for (int x = 1; x < WIDTH - 1; x++) 
		lines.push_back({x,y});
    }
    return lines;
}

bool sortCoords(const Coords & c1, const Coords & c2)
{
    return c1.y < c2.y;
}
