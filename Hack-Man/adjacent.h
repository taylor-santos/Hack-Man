#pragma once
#include <vector>
#include "Grid.h"
#include "Point.h"
#include "paths.h"

Point offsetPoint(Point pt, int offset);
int is_adjacent(Point, Point);
vector<Point> getAdjacentCells(Grid* grid, Point pt);