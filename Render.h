#ifndef RENDER_H
#define RENDER_H
#include <ncurses.h>
#include <vector>

enum {playWin, scoreWin, previewWin};
enum {red = 1, green = 2, blue = 3, magenta = 4, cyan = 5, white = 10,
    black = 11, line = 12};
using std::vector;

#ifndef COORDS
#define COORDS
struct Coords
{
    int x;
    int y;

    friend bool operator==(const Coords & c1, const Coords & c2)
    {
	return c1.x == c2.x and c1.y == c2.y;
    }
    friend bool operator<(const Coords & c1, const Coords & c2)
    {
        return c1.y < c2.y;
    }
    friend bool operator>(const Coords & c1, const Coords & c2)
    {
        return c1.y > c2.y;
    }
};
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
