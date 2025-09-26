#include "point.hpp"
#include "rect.hpp"

/* **** */

void Rect::inset(const int x, const int y)
{ topLeft.inset(x, y), extent.inset(x, y); }

void Rect::offset(const int x, const int y)
{ topLeft.offset(x, y); }

Rect::Rect(Point topLeft, Point extent):
	topLeft(topLeft), extent(extent)
	{}
