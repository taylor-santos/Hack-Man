#pragma once
#ifndef CELL_H
#define CELL_H
#include "Point.h"
class Cell : public Point {
	bool wall = false;
public:
	bool is_wall() { return wall; }
	void set_wall(bool value) { wall = value; }
	Cell(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
#endif