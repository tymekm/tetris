#ifndef RENDER_H
#define RENDER_H
#include <ncurses.h>
#include <vector>
#include "Enums.h"

enum class Window {playWin, scoreWin, previewWin};
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
    public:
	Render(const int h, const int w);
	window & getWin(Window w);
	void Draw(Window w, const vector<Coords> & toDraw,
		const int color, const char character = ' '); 
	void Draw(const Window w, const int toDraw,
		const int x, const int y);
	void Draw(const Window w, const char * toDraw,
		const int x, const int y);
	void setTimeOut(const int n) { timeout(n); };
	void shift(Window w, const vector<Coords> & toShift,
		const int xOffset, const int yOffset);
    private:	
	struct CharNCoords
	{
	    Coords coords;
	    unsigned int color;
	    unsigned int text;
	};
	windows wins;
	void makeWindows(const int h, const int w);
	void Draw(const Window w, const vector<CharNCoords> & characters);
}; 
#endif
