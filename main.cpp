#include "Tetromino.h"
#include "Render.h"

#include <memory>
#include <algorithm>

const int HEIGHT = 18;
const int WIDTH = 12;

void gameLoop(Render & screen);
vector<Coords> initOccupied();
vector<int> getLines(vector<Coords> & occupied);
vector<Coords> linesToCoords(const vector<int> & l);

int main()
{
    Render screen(HEIGHT, WIDTH);  
    gameLoop(screen);
}

void gameLoop(Render & screen)
{
    std::unique_ptr<Tetromino> piece (new Tetromino);     
    std::unique_ptr<Tetromino> newPiece (new Tetromino);     
    vector<Coords> alreadyOccupied = initOccupied();
    int ch;
    screen.Draw(playWin, piece.get()->getOccupied(),
	    piece.get()->getColor());

    while (true)
    {
	if (piece.get()->getState() not_eq stuck)
	{
	    ch = getch();
	    screen.clearLastDraw(piece.get()->getOccupied());
	}
	else if (piece.get()->getState() == stuck)
	{
	    alreadyOccupied.insert(alreadyOccupied.end(),
		piece.get()->getOccupied().begin(),
		piece.get()->getOccupied().end());
	    piece = std::move(newPiece);
	    newPiece.reset(new Tetromino);
	    auto lines = getLines(alreadyOccupied);
	    screen.Draw(playWin, linesToCoords(lines), line, '=');
	    screen.Draw(playWin, piece.get()->getOccupied(),
		piece.get()->getColor());
	    ch = getch();
	}
	switch (ch) 
	{
	    case KEY_DOWN:
		piece.get()->move(down, alreadyOccupied);	
		break;
	    case KEY_LEFT:
		piece.get()->move(left, alreadyOccupied);	
		break;
	    case KEY_RIGHT:
		piece.get()->move(right, alreadyOccupied);	
		break;
	    case ' ':
		piece.get()->rotate(alreadyOccupied);
	        break;
	}
	screen.Draw(playWin, piece.get()->getOccupied(),
		piece.get()->getColor());
    }
}

vector<Coords> initOccupied()
{
    vector<Coords> occupied;
    for (int y = 0; y < HEIGHT; y++) 
	for (int x = 0; x < WIDTH; x++) 
	    if (y == HEIGHT - 1 or x == 0 or x == WIDTH -1)
		occupied.push_back({x,y});
    return occupied;
}

vector<int> getLines(vector<Coords> & occupied)
{
    int count;
    vector<int> lines;
    for (int y = HEIGHT - 2; y > 0; y--)
    {
	count = count_if(occupied.begin(), occupied.end(),
		[y](Coords & c){ return c.y == y; }); 
	if (count == WIDTH)
	    lines.push_back(y);
    }
    return lines;
}

vector<Coords> linesToCoords(const vector<int> & l)
{
    vector<Coords> lineCoords (l.size());
    for (auto & it: l)
	for (int x = 1; x < WIDTH - 1; x++) 
	    lineCoords.push_back({x, it});
    return lineCoords;
}
