#include "Render.h"
#include <ncurses.h>
#include <algorithm>

Render::Render(const int h, const int w)
{
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);

    start_color();
    init_pair(red, COLOR_RED, COLOR_RED);
    init_pair(blue, COLOR_BLUE, COLOR_BLUE);
    init_pair(green, COLOR_GREEN, COLOR_GREEN);
    init_pair(magenta, COLOR_MAGENTA, COLOR_MAGENTA);
    init_pair(cyan, COLOR_CYAN, COLOR_CYAN);

    init_pair(white, COLOR_BLACK, COLOR_WHITE);
    init_pair(black, COLOR_BLACK, COLOR_BLACK);
    init_pair(line, COLOR_RED, COLOR_BLACK);
    refresh();
    makeWindows(h,w);
}

window & Render::getWin(Window w)
{
    switch (w) 
    {
	case Window::playWin:
	    return wins.playWin;	
    	break;
	case Window::scoreWin:
	    return wins.scoreWin; 
	    break;	
	case Window::previewWin:
	    return wins.previewWin; 
	    break;
	default:
	    return wins.playWin;
    }
}

void Render::Draw(const Window w, const vector<Coords> & toDraw,
		const int color, const char character)
{
    auto win = getWin(w);
    for (auto it : toDraw)
	if (it.y > 0)
	{
	    mvwaddch(win.win, it.y, it.x, character| COLOR_PAIR(color));
	}
    wrefresh(win.win);
}

void Render::Draw(const Window w, const vector<CharNCoords> & characters)
{
    auto win = getWin(w);
    for (auto c : characters) 
	mvwaddch(win.win, c.coords.y, c.coords.x, c.text | c.color);
    wrefresh(win.win);
}

void Render::Draw(const Window w, const int toDraw, const int x, const int y)
{
    auto win = getWin(w);
    mvwprintw(win.win, y, x, "%d", toDraw);
    wrefresh(win.win);
}

void Render::Draw(const Window w, const char * toDraw, const int x, const int y)
{
    auto win = getWin(w);
    mvwprintw(win.win, y, x, toDraw);
    wrefresh(win.win);
}

void Render::shift(const Window w, const vector<Coords> & toShift,
	const int xOffset, const int yOffset)
{
    vector<CharNCoords> chars;
    auto win = getWin(w).win;
    for (auto & coord : toShift) 
    {
	chtype character = mvwinch(win, coord.y, coord.x); 
	Coords newCoords = {coord.x + xOffset, coord.y + yOffset};
	auto color = character & A_COLOR;
	auto text = character & A_CHARTEXT;
	chars.push_back({newCoords, color, text});
    }
    Draw(w, toShift, black);
    Draw(w, chars);
}

void Render::makeWindows(const int playHeight, const int playWidth)
{
    const int scoreHeight = 5;
    const int scoreWidth = 10;

    window playBox;
    playBox.height = playHeight;
    playBox.width = playWidth;
    playBox.starty = (LINES - playBox.height) / 2;	
    playBox.startx = (COLS - playBox.width) / 2;
    playBox.win = newwin(playBox.height, playBox.width,
	    playBox.starty,  playBox.startx);

    wattron(playBox.win ,COLOR_PAIR(white));
    box(playBox.win, ' ', ' ');
    wattroff(playBox.win ,COLOR_PAIR(white));
    const int secColStartX = playBox.startx + playBox.width;
    const int secColStartY = playBox.starty;

    window scoreBox;
    scoreBox.height = scoreHeight;
    scoreBox.width = scoreWidth;
    scoreBox.starty = secColStartY;	
    scoreBox.startx = secColStartX;
    scoreBox.win = newwin(scoreBox.height, scoreBox.width,
	    scoreBox.starty,  scoreBox.startx);
    box(scoreBox.win, 0, 0);
    
    window previewBox;
    previewBox.height = playBox.height - scoreBox.height;
    previewBox.width = scoreWidth;
    previewBox.starty = scoreBox.starty + scoreBox.height;
    previewBox.startx = secColStartX;
    previewBox.win = newwin(previewBox.height, previewBox.width,
	    previewBox.starty, previewBox.startx);
    box(previewBox.win, 0, 0);

    wnoutrefresh(playBox.win);
    wnoutrefresh(scoreBox.win);
    wnoutrefresh(previewBox.win);
    doupdate();

    wins.playWin = playBox;
    wins.scoreWin = scoreBox;
    wins.previewWin = previewBox;
}

