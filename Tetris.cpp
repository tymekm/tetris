#include "Tetris.h"

Tetris::Tetris(const int h, const int w)
    :piece(new Tetromino), nextPiece(new Tetromino), screen(h,w)
{
    initOccupied();
    screen.Draw(Window::playWin, piece.get()->getOccupied(),
	    piece.get()->getColor());
    screen.Draw(Window::previewWin, nextPiece.get()->getPreview(),
	    nextPiece.get()->getColor());
    checkLevelUp(0);
    addScore(0);
    nodelay(stdscr, true);
}

void Tetris::initOccupied()
{
    const int HEIGHT = screen.getWin(Window::playWin).height;
    const int WIDTH = screen.getWin(Window::playWin).width;
    vector<Coords> occupied;
    for (int y = 0; y < HEIGHT; y++) 
	for (int x = 0; x < WIDTH; x++) 
	    if (y == HEIGHT - 1 or x == 0 or x == WIDTH -1)
		occupied.push_back({x,y});
    occupiedSpace = occupied;
}

GameState Tetris::movePiece(Direction dir)
{
    vector<Coords> oldOccupied = piece.get()->getOccupied();
    piece.get()->move(dir, occupiedSpace);
    if (piece.get()->getState() == State::stuck)
    {
	occupiedSpace.insert(occupiedSpace.begin(),
	    piece.get()->getOccupied().begin(),
	    piece.get()->getOccupied().end());
	auto & temp = piece.get()->getOccupied();
	auto it = std::find_if
	    (temp.begin(), temp.end(),
	     [](auto & a) { return a.y < 1;} );
	if (it != temp.end())
	    return GameState::gameover;
	checkForLines();
	screen.Draw(Window::previewWin, nextPiece.get()->getPreview(),
		black);
	piece = std::move(nextPiece);
	nextPiece.reset(new Tetromino);
	screen.Draw(Window::playWin, piece.get()->getOccupied(),
		piece.get()->getColor());
	screen.Draw(Window::previewWin, nextPiece.get()->getPreview(),
		nextPiece.get()->getColor());
    }
    else if (piece.get()->getState() == State::valid)
	drawPiece(oldOccupied);
    else
	piece.get()->makeValid();
    return GameState::running;
}

void Tetris::rotatePiece()
{
    vector<Coords> oldOccupied = piece.get()->getOccupied();
    piece.get()->rotate(occupiedSpace);
    if (piece.get()->getState() == State::invalid)
	piece.get()->makeValid();
    else
	drawPiece(oldOccupied);
}

void Tetris::drawPiece(const vector<Coords> & oldOccupied)
{
    vector<Coords> newOccupied = piece.get()->getOccupied();

    vector<Coords> toDraw;
    for (auto it: newOccupied) 
	if (std::find(oldOccupied.begin(), oldOccupied.end(), it)
	    == oldOccupied.end()) 
	    toDraw.push_back(it); 
    screen.Draw(Window::playWin, toDraw, piece.get()->getColor());

    vector<Coords> toErase;
    for (auto it: oldOccupied) 
	if (std::find(newOccupied.begin(), newOccupied.end(), it) 
	    == newOccupied.end()) 
	    toErase.push_back(it); 
    screen.Draw(Window::playWin, toErase, black);
}

void Tetris::checkForLines()
{
    const int HEIGHT = screen.getWin(Window::playWin).height;
    const int WIDTH = screen.getWin(Window::playWin).width;
    vector<int> lines;
    int lineCount = 0;
    for (int y = HEIGHT - 2; y > 0; y--)
    {
	int count = count_if(occupiedSpace.begin(), occupiedSpace.end(),
		[y](Coords & c){ return c.y == y; }); 
	if (count == WIDTH)
	{
	    lines.push_back(y);
	    lineCount++;
	}

    }
    if (!lines.empty())
    {
	linesCleared += lineCount;
	std::sort(lines.begin(), lines.end());
	checkLevelUp(lineCount);
	addScore(lineCount);
	handleLines(lines);
    }
}

void Tetris::handleLines(const vector<int> & l)
{
    using std::this_thread::sleep_for;
    using std::chrono::milliseconds;

    auto win = screen.getWin(Window::playWin);
    vector<Coords> lineCoords;

    for (auto & line : l)
	for (int x = 1; x < win.width - 1; x++) 
	    lineCoords.push_back({x, line});

    screen.Draw(Window::playWin, lineCoords, line, '=');
    sleep_for(milliseconds(200));
    screen.Draw(Window::playWin, lineCoords, black, ' ');

    vector<Coords> temp;
    std::sort(occupiedSpace.begin(), occupiedSpace.end());
    std::sort(lineCoords.begin(), lineCoords.end());
    std::set_difference
	(
	    occupiedSpace.begin(), occupiedSpace.end(),
	    lineCoords.begin(), lineCoords.end(),
	    std::back_inserter(temp)
	);
    occupiedSpace = std::move(temp);

    for (auto & line : l)
    {
        vector<Coords> toShift;
        for (auto & coord : occupiedSpace) 
	    if (coord.y > 0 and coord.y <= line
        	    and coord.x > 0 and coord.x < win.width - 1)
            {
        	toShift.push_back(coord);
        	coord.y++;
            }
        screen.shift(Window::playWin, toShift, 0, 1);
    }

}
void Tetris::addScore(const int l)
{
    int scoreBase;
    switch (l) 
    {
        case 1:
	    scoreBase = 40;
    	break;
        case 2:
	    scoreBase = 100;
    	break;
        case 3:
	    scoreBase = 300;
    	break;
        case 4:
	    scoreBase = 1200;
    	break;
	default:
	    scoreBase = 0;
    }
    totScore += scoreBase * level;
    auto win = screen.getWin(Window::scoreWin);
    unsigned int numberOfDigits = 0;
    unsigned int n = totScore;
    do { ++numberOfDigits; n /= 10; } while (n);    
    int x = win.width / 2 - (numberOfDigits / 2);
    int y = 1;
    screen.Draw(Window::scoreWin, totScore, x, y);
}

void Tetris::checkLevelUp(const int l)
{
    lineCounter += l;
    if (lineCounter >= 10)
    {
	level++;
	lineCounter -= 10;
    }
    auto win = screen.getWin(Window::scoreWin);
    unsigned int numberOfDigits = 0;
    unsigned int n = totScore;
    do { ++numberOfDigits; n /= 10; } while (n);    
    int x = win.width / 2;
    int y = 3;
    screen.Draw(Window::scoreWin, "lvl:", x - 3, y);
    screen.Draw(Window::scoreWin, level, x + 1, y);
}
