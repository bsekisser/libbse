#pragma once

/* **** */

class Point {
private:
	int x, y;
public:
	void inset(const int x, const int y);
	void get(int *const x, int *const y);
	void offset(const int x, const int y);
	Point(const int x, const int y);
	void set(const int x, const int y);
};
