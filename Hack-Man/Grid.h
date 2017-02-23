#pragma once
#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Cell.h"
#include "Player.h"

using namespace std;

class Grid {
	int w;
	int h;
public:
	vector<vector<Cell*>> cells;
	int wallCount;
	Player* players[2];
	vector<Cell*> snippets;
	vector<Cell*> weapons;
	vector<Cell*> bugs;
	vector<int> bug_directions;

	int height() { return h; }
	int width() { return w; }
	Grid* copy();
	void reset();
	Grid(int, int);
	~Grid();
};
#endif