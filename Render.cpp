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

window & Render::getWin(const int w)
{
    switch (w) 
    {
        case playWin:
	    return wins.playWin;	
    	break;
	case scoreWin:
	    return wins.scoreWin; 
	    break;	
	case previewWin:
	    return wins.previewWin; 
	    break;
	default:
	    return wins.playWin;
    }
}

void Render::Draw(const int w, const vector<Coords> & toDraw,
		const int c, const char ch)
{
    auto win = getWin(w);
    for (auto it : toDraw)
	if (it.y > 0)
	    mvwaddch(win.win, it.y, it.x, ch| COLOR_PAIR(c));
    wrefresh(win.win);
    lastDrawn.win = win;
    lastDrawn.coords = toDraw;
}

void Render::clearLastDraw(vector<Coords> & toOmit)
{
	
    for (auto &i : lastDrawn.coords)
	if (i.y > 0)
	    mvwaddch(lastDrawn.win.win, i.y, i.x, 'X' | COLOR_PAIR(black));
    wnoutrefresh(lastDrawn.win.win);
    wrefresh(lastDrawn.win.win);
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
