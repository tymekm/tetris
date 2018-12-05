#ifndef ENUMS_H
#define ENUMS_H
enum {red = 1, green = 2, blue = 3, magenta = 4, cyan = 5, white = 10,
    black = 11, line = 12};

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
	if (c1.y == c2.y)
	    return c1.x < c2.x;
        return c1.y < c2.y;
    }
    friend bool operator>(const Coords & c1, const Coords & c2)
    {
	if (c1.y == c2.y)
	    return c1.x > c2.x;
        return c1.y > c2.y;
    }
};
#endif
