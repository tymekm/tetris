#ifndef RENDER_H
#define RENDER_H
#include <ncurses.h>
#include <vector>
#include "Enums.h"

enum {playWin, scoreWin, previewWin};
using std::vector;

#ifndef COORDS
#define COORDS
#endif

struct window
{
    WINDOW * win;
    int height;
    int width;
    int startx;
    int starty;
};
struct windows
{
    window playWin;
    window scoreWin;
    window previewWin;
};

class Render 
{
    struct LastDrawn
    {
	window win;
	vector<Coords> coords;
    };
    private:	
	windows wins;
	LastDrawn lastDrawn;
	void makeWindows(const int h, const int w);
    public:
	Render(const int h = 25, const int w = 13);
	window & getWin(const int w);
	void Draw(const int w, const vector<Coords> & toDraw,
		const int c, const char ch = ' '); 
	void clearLastDraw(vector<Coords> & toOmit);
}; 
#endif
