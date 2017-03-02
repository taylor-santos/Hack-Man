#pragma once
#ifndef GRID_H
#define GRID_H
#include <vector>
#include "Player.h"

using namespace std;

class Grid {
	int w;
	int h;
public:
	int round;
	Player* players[2];
	vector<Point> snippets;
	vector<Point> weapons;
	vector<Point> bugs;
	vector<int> bug_directions;

	int height() { return h; }
	int width() { return w; }
	Grid* copy();
	void reset();
	Grid(int, int);
	~Grid();
};
#endif