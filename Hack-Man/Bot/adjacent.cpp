#include "adjacent.h"

Point offsetPoint(Point pt, int offset) {
	if (offset == -1)
		return pt;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	Point newPoint(pt.x + dx[offset], pt.y + dy[offset]);
	return newPoint;
}

int is_adjacent(Point a, Point b) {
	/*
	-1=not adjacent
	0=up
	1=right
	2=down
	3=left
	*/
	if (a.x == b.x) {
		if (a.y - b.y == 1)
			return 0;
		else if (a.y - b.y == -1)
			return 2;
	}
	else if (a.y == b.y) {
		if (a.x - b.x == 1)
			return 3;
		else if (a.x - b.x == -1)
			return 1;
	}
	return -1;
}

vector<Point> getAdjacentCells(Grid* grid, Point pt) {
	vector<Point> adjacent;
	int x = pt.x;
	int y = pt.y;
	if (y > 0 && !walls[x][y - 1])
		adjacent.push_back(Point(x, y - 1));
	if (y < 13 && !walls[x][y + 1])
		adjacent.push_back(Point(x, y + 1));
	if (x > 0 && !walls[x-1][y])
		adjacent.push_back(Point(x - 1, y));
	if (x < 19 && !walls[x + 1][y])
		adjacent.push_back(Point(x + 1, y));
	return adjacent;
}