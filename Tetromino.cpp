#include "Tetromino.h"

Tetromino::Tetromino()
{
    std::srand(std::time(0));
    const int i = rand() % 7;
    tetArr = tetrominos[i];
    color = rand() % 5 + 1;
    switch (i) 
    {
        case 0:
	    color = red;	
    	break;
        case 1:
	    color = blue;	
    	break;
        case 2:
	    color = green;	
    	break;
        case 3:
	    color = cyan;	
    	break;
        case 4:
	    color = red;	
    	break;
        case 5:
	    color = blue;	
    	break;
        case 6:
	    color = magenta;	
    	break;
    }
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

    array<bool, 16> temp;
    int index = 0;
    int arrX = 0;
    int arrY = 0;

    for (int i = 0; i < 16; i++) 
    {
	if (i % 4 == 0 and i > 0)
	{
	    arrY++;
	    arrX -= 4;
	}
	switch (orientation) 
	{
	    case 0:
		index = arrY * 4 + arrX;
		break;
	    case 1:
		index = 12 + arrY - (arrX * 4);	
		break;
	    case 2:
		index = 15 - (arrY * 4) - arrX;	
		break;
	    case 3:
		index = 3 - arrY + (arrX * 4);	
		break;
	}    
	temp[index] = tetArr[i];
	arrX++;
    }

    for (int i = 0; i < 16; i++) 
    {
	if (i % 4 == 0 and i > 0)
	{
	    y++;
	    x -= 4;
	}
	if (temp[i] == true)
	{
	    occByTetr.push_back({x,y});
	}
	x++;
    }
}

void Tetromino::move(Direction dir, vector<Coords> & alreadyOccupied)
{
    vector<Coords>::iterator it;
    Coords temp = pos;
    switch (dir) 
    {
	case Direction::down:
	    temp.y ++; 
	    fillOccupied(temp.x,temp.y);
	    for (auto &i : occByTetr) 
		for (auto &j : alreadyOccupied)
		    if (i == j)
		    {
			fillOccupied(pos.x, pos.y);
			state = State::stuck;
		    }
    	break;
	case Direction::right:
	    temp.x ++; 
	    fillOccupied(temp.x,temp.y);
	    for (auto &i : occByTetr) 
		for (auto &j : alreadyOccupied)
		    if (i == j)
		    {
			fillOccupied(pos.x, pos.y);
			state = State::invalid;
		    }
    	break;
	case Direction::left:
	    temp.x --; 
	    fillOccupied(temp.x,temp.y);
	    for (auto &i : occByTetr) 
		for (auto &j : alreadyOccupied)
		    if (i == j)
		    {
			fillOccupied(pos.x, pos.y);
			state = State::invalid;
		    }
    	break;
    }
    if (state == State::valid)
	pos = temp;
    else if (state == State::invalid)
	state = State::valid;
}

void Tetromino::rotate(vector<Coords> & alreadyOccupied)
{
    if (orientation == 3)
	orientation = 0;
    else
	orientation++;
    fillOccupied(pos.x, pos.y);
    for (auto &i : occByTetr) 
	for (auto &j : alreadyOccupied)
	    if (i == j)
		state = State::invalid;
    if (state == State::invalid)
    {
	if (orientation == 0)
	    orientation = 3;
	orientation--;
    }
    fillOccupied(pos.x, pos.y);
    state = State::valid;
}

