#pragma once
#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Cell.h"

using namespace std;

class Grid {
	int w;
	int h;
public:
	vector<vector<Cell*>> cells;
	int wallCount;
	bool playerWeapons[2]{ false, false };
	vector<Cell*> snippets;
	vector<Cell*> weapons;
	vector<Cell*> bugs;

	int height() { return h; }
	int width() { return w; }
	Grid* copy();
	void make_bugpath();
	void reset();
	Grid(int, int);
	~Grid();
};
#endif