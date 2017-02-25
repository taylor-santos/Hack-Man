#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <climits>
#include "Point.h"
#include "Grid.h"
#include "adjacent.h"
#include "paths.h"

void wall_character(Grid* grid, int x, int y);
vector<Point> shortestPathAroundBugsToPoint(Grid* grid, Point pt, int playerID);
vector<Point> findClosestItem(Grid* grid, int playerID);
