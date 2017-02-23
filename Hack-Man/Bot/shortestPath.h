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

vector<Point> findClosestItem(Grid* grid, int playerID);

//vector<Point> recursiveFindBestPath(Grid* grid, int playerID);
//vector<Point> shortestPathAroundBugs(Grid* grid, int playerID);
//vector<Point> findClosestItem(Grid* grid, int playerID);