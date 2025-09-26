#include "point.hpp"

void Point::inset(const int x, const int y)
{ this->x += x >> 1, this->y += y >> 1; }

void Point::get(int *const x, int *const y)
{
	if(x) *x = this->x;
	if(y) *y = this->y;
}

void Point::offset(const int x, const int y)
{ this->x += x, this->y += y; }

Point::Point(const int x, const int y): x(x), y(y) {}

void Point::set(const int x, const int y)
{ this->x = x, this->y = y; }
