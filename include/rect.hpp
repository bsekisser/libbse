#pragma once

/* **** */

#include "point.hpp"

/* **** */

class Rect {
private:
	Point topLeft;
	Point extent;
public:
	void inset(const int x, const int y);
	void offset(const int x, const int y);
	Rect(Point topLeft, Point extent);
};
