#include "Render.h"
#include "Tetris.h"
#include <iostream>

const int HEIGHT = 18;
const int WIDTH = 13;

void gameLoop(Tetris & tetris);
void moveOccDown(vector<Coords> & occ, const vector<int> & l, Render & s);


int main()
{
    Tetris tetris(HEIGHT, WIDTH);  
    gameLoop(tetris);
    int score = tetris.getScore();
    std::cout << "Game Over!\n";
    std::cout << "Score: " << score << '\n';
}

void gameLoop(Tetris & tetris)
{
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    int tick = 0;
    int key;

    while (true)
    {
	if (tetris.getState() == GameState::gameover)
	{
	    werase(stdscr);
	    refresh();
	    break;
	}
	key = getch();
	Direction dir;
	switch (key) 
	{
	    case KEY_DOWN:
		dir = Direction::down;
		break;
	    case KEY_LEFT:
		dir = Direction::left;
		break;
	    case KEY_RIGHT:
		dir = Direction::right;
		break;
	    case ' ':
		dir = Direction::rotate;
	        break;
	    case 'p':
	    case 'P':
		tetris.pause();
		break;
	}
	if (tetris.getState() == GameState::paused)
	    continue;
	if (key != ERR)
	    tetris.movePiece(dir);
	sleep_for(milliseconds(1));
	tick += 1;
	if (tick == (1000 - tetris.getLevel() * 40))
	{
	    tetris.movePiece(Direction::down);
	    tick = 0;
	}
    }
}
