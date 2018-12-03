#include "Tetromino.h"

Tetromino::Tetromino()
{
    std::srand(std::time(0));
    const int i = rand() % 7;
    tetArr = tetrominos[2];
    color = rand() % 5 + 1;
    if (i < 4)
	pos.y = -1; 
    else if (i >= 4)
	pos.y = -2;
    pos.x = 4;
    fillOccupied(pos.x, pos.y);
}

void Tetromino::fillOccupied(int x, int y)
{
    if (!occByTetr.empty())
	occByTetr.clear();
    for (int i = 0; i < 16; i++) 
    {
	if (i % 4 == 0 and i > 0)
	{
	    y++;
	    x -= 4;
	}
	if (tetArr[i] == true)
	{
	    occByTetr.push_back({x,y});
	}
	x++;
    }
}

void Tetromino::move(const int dir, vector<Coords> & alreadyOccupied)
{
    vector<Coords>::iterator it;
    Coords temp = pos;
    switch (dir) 
    {
        case down:
	    temp.y ++; 
	    fillOccupied(temp.x,temp.y);
	    for (auto &i : occByTetr) 
		for (auto &j : alreadyOccupied)
		    if (i == j)
		    {
			fillOccupied(pos.x, pos.y);
			state = stuck;
		    }
    	break;
        case right:
	    temp.x ++; 
	    fillOccupied(temp.x,temp.y);
	    for (auto &i : occByTetr) 
		for (auto &j : alreadyOccupied)
		    if (i == j)
	    {
		fillOccupied(pos.x, pos.y);
		state = invalid;
	    }
    	break;
        case left:
	    temp.x --; 
	    fillOccupied(temp.x,temp.y);
	    for (auto &i : occByTetr) 
		for (auto &j : alreadyOccupied)
		    if (i == j)
	    {
		fillOccupied(pos.x, pos.y);
		state = invalid;
	    }
    	break;
    }
    if (state == valid)
	pos = temp;
    else if (state == invalid)
	state = valid;
}

bool Tetromino::rotate()
{
//    if (orientation == 3)
//	orientation = 0;
//    else
//	orientation++;
//
//    vector<Coords> tempCoords;
//
//    for (int i = 0; i < 16; i++) 
//    {
//        
//    }
//    	
//    for (auto &it : tetArr)
//    {
//	
//    }
//
    return true;
}

