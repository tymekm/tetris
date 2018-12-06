#include "Render.h"
#include "Tetris.h"

const int HEIGHT = 18;
const int WIDTH = 13;

void gameLoop(Tetris & tetris);
void moveOccDown(vector<Coords> & occ, const vector<int> & l, Render & s);


int main()
{
    Tetris tetris(HEIGHT, WIDTH);  
    gameLoop(tetris);
}

void gameLoop(Tetris & tetris)
{
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    int tick = 0;
    int key;

    while (true)
    {
	key = getch();
	switch (key) 
	{
	    case KEY_DOWN:
		tetris.movePiece(Direction::down);
		break;
	    case KEY_LEFT:
		tetris.movePiece(Direction::left);
		break;
	    case KEY_RIGHT:
		tetris.movePiece(Direction::right);
		break;
	    case ' ':
		tetris.rotatePiece();
	        break;
	//    case KEY_UP:
	//	sleep_for(milliseconds(1000000));
	//	break;
	}
	sleep_for(milliseconds(1));
	tick += 1;
	if (tick == (1000 - tetris.getLevel() * 40))
	{
	    tetris.movePiece(Direction::down);
	    tick = 0;
	}
	key = 0;
    }
}
