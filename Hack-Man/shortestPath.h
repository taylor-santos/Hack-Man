#pragma once
#include <vector>
#include <iostream>
#include <queue>
#include <string>
#include <algorithm>
#include <climits>
#include <assert.h>
#include "Point.h"
#include "Grid.h"
#include "adjacent.h"
#include "paths.h"

vector<Point> bestPathToPoint(Grid** grid, Point pt, int playerID, int printIndent);
vector<Point> closestItemAroundBugs(Grid** grid, int playerID);
vector<Point> shortestPathAroundBugsToPoint(Grid* grid, Point pt, int playerID);
vector<Point> optimalPathGivenEnemyPath(Grid* grid, vector<Point> enemyPath, int playerID);
void wall_character(Grid* grid, int x, int y);
void printGrid(Grid* grid, vector<vector<Point>> items = vector<vector<Point>>(), vector<char> icons = vector<char>(), int indent = 0);
