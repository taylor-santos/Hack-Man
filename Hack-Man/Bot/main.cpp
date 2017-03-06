#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <stack>
#include <climits>
#include <assert.h>
#include <queue>
#include "paths.h"
#include "Grid.h"
#include "Player.h"
#include "Point.h"
#include "shortestPath.h"
#include "adjacent.h"

using namespace std;

int width;
int height;
int timebank;
int time_per_move;
int time_remaining;
int max_rounds;
int current_round;
int myID;
int dx[4] = { 0,1,0,-1 };
int dy[4] = { -1,0,1,0 };
string myName;
string moves[4] = { "up", "left", "down", "right" };
vector<Point> prevBugs;
Grid* CurrGrid;

void do_move(Grid* grid);
void process_next_command(Grid* grid);

void process_next_command(Grid* grid) {
	string command;
	cin >> command;
	if (command == "settings") {
		string type;
		cin >> type;
		if (type == "timebank") {
			cin >> timebank;
		}
		else if (type == "time_per_move") {
			cin >> time_per_move;
		}
		else if (type == "player_names") {
			string names;
			cin >> names;
		}
		else if (type == "your_bot") {
			cin >> myName;
		}
		else if (type == "your_botid") {
			cin >> myID;
		}
		else if (type == "field_width") {
			cin >> width;
		}
		else if (type == "field_height") {
			cin >> height;
		}
		else if (type == "max_rounds") {
			cin >> max_rounds;
		}
	}
	else if (command == "update") {
		string player_name, type;
		cin >> player_name >> type;
		if (type == "round") {
			cin >> current_round;
			grid->round = current_round;
		}
		else if (type == "field") {
			string s;
			cin >> s;
			int x = 0;
			int y = 0;
			for (int i = 0; i < s.length(); ++i) {
				char c = s[i];
				if (c == ',') {
					x++;
					if (x == grid->width()) {
						x = 0;
						y++;
					}
					continue;
				}else if (c == 'x') {
					continue;
				}
				else if (c == '.') {
					continue;
				}
				else if (c == 'E') {
					grid->bugs.push_back(Point(x,y));
					int bugDirection = -1;
					for (int j = 0; j < prevBugs.size(); ++j)
					{
						int adjacent = is_adjacent(prevBugs[j], Point(x,y));
						if (adjacent != -1) {
							bugDirection = adjacent;
							prevBugs.erase(prevBugs.begin() + j);
							break;
						}
					}
					grid->bug_directions.push_back(bugDirection);
					continue;
				}
				else if (c == 'W') {
					grid->weapons.push_back(Point(x,y));
					continue;
				}
				else if (c == 'C') {
					grid->snippets.push_back(Point(x, y));
					continue;
				}
				else {
					int id = c - '0';
					grid->players[id].x = x;
					grid->players[id].y = y;
					continue;
				}
			}
		}
		else if (type == "snippets") {
			int snippets;
			cin >> snippets;
			if (player_name == myName) {
				grid->players[myID].snippets = snippets;
			}
			else {
				grid->players[!myID].snippets = snippets;
			}
		}
		else if (type == "has_weapon") {
			string value;
			cin >> value;
			if (player_name == myName) {
				grid->players[myID].has_weapon = (value == "true");
			}
			else {
				grid->players[!myID].has_weapon = (value == "true");
			}
		}
		else if (type == "is_paralyzed") {
			string value;
			cin >> value;
			if (player_name == myName) {
				grid->players[myID].is_paralyzed = (value == "true");
			}
			else {
				grid->players[!myID].is_paralyzed = (value == "true");
			}
		}
	}
	else if (command == "action") {
		string useless_move;
		cin >> useless_move;
		cin >> time_remaining;
		do_move(grid);
		prevBugs.clear();
		for (int i = 0; i < grid->bugs.size(); ++i) {
			prevBugs.push_back(grid->bugs[i]);
		}
		grid->reset();
	}
}

void do_move(Grid* grid) {
	cerr << "Round " << current_round << ":" << endl;
	cerr << "My Snippets: " << grid->players[myID].snippets << endl;
	cerr << "Enemy Snippets: " << grid->players[!myID].snippets << endl;
	if (grid->players[myID].has_weapon)
		cerr << "I have a weapon." << endl;
	if (grid->players[!myID].has_weapon)
		cerr << "Enemy has a weapon." << endl;
	cerr << "Current board: " << endl;

	vector<vector<Point>> items;
	vector<char> icons;

	vector<Point> playerPos;
	playerPos.push_back((Point)grid->players[myID]);
	vector<Point> enemyPos;
	enemyPos.push_back((Point)grid->players[!myID]);
	vector<Point> snippets = grid->snippets;
	vector<Point> weapons = grid->weapons;

	items.push_back(playerPos);
	icons.push_back('A');
	items.push_back(enemyPos);
	icons.push_back('B');
	items.push_back(snippets);
	icons.push_back('S');
	items.push_back(weapons);
	icons.push_back('W');

	printGrid(grid, items, icons, 0);

	int myIndex = index[grid->players[myID].x][grid->players[myID].y];

	vector<Point> targetPoints;
	for (int snipIndex = 0; snipIndex < grid->snippets.size(); ++snipIndex)
		targetPoints.push_back(grid->snippets[snipIndex]);
	if (!grid->players[myID].has_weapon || !grid->players[!myID].has_weapon) {
		//Player should go for a weapon if either player doesn't have one. 
		for (int weapIndex = 0; weapIndex < grid->weapons.size(); ++weapIndex)
			targetPoints.push_back(grid->weapons[weapIndex]);
	}
	vector<vector<Point>> myPaths;
	vector<vector<Point>> enemyPaths;
	cerr << "Possible paths:" << endl;
	for (int targetIndex = 0; targetIndex < targetPoints.size(); ++targetIndex) {
		Grid* newGrid = grid->copy();
		vector<Point> pathToTarget = bestPathToPoint(&newGrid, targetPoints[targetIndex], myID, 1);
		vector<Point> enemyPathToTarget = bestPathToPoint(&newGrid, targetPoints[targetIndex], !myID, -1);
		if (pathToTarget.size() > 0 || enemyPathToTarget.size() > 0) {
			myPaths.push_back(pathToTarget);
			enemyPaths.push_back(enemyPathToTarget);
		}
	}
	int bestPathIndex = -1;
	int bestPathLength = INT_MAX;
	for (int i = 0; i < myPaths.size(); ++i) {
		if (enemyPaths[i].size() == 0) {
			if (myPaths[i].size() < bestPathLength) {
				bestPathIndex = i;
				bestPathLength = myPaths[i].size();
			}
		} else if (myPaths[i].size() > 0) {
			if (myPaths[i].size() <= enemyPaths[i].size() && myPaths.size() < bestPathLength) {
				bestPathIndex = i;
				bestPathLength = myPaths[i].size();
			}
		}
	}
	if (bestPathIndex != -1) {
		cerr << "Chose path #" << bestPathIndex << ", with length " << bestPathLength << endl << "Output: ";
		int offset = is_adjacent((Point)grid->players[myID], myPaths[bestPathIndex][1]);
		switch (offset) {
		case 0:
			cerr << "up." << endl;
			cout << "up" << endl;
			break;
		case 1:
			cerr << "right." << endl;
			cout << "right" << endl;
			break;
		case 2:
			cerr << "down." << endl;
			cout << "down" << endl;
			break;
		case 3:
			cerr << "left." << endl;
			cout << "left" << endl;
			break;
		default:
			cerr << "pass." << endl;
			cout << "pass" << endl;
			break;
		}
	} else {
		cerr << "No path to any item. Looking for path to optimal position on board." << endl;
		int enemyIndex = index[grid->players[!myID].x][grid->players[!myID].y];
		int optimalPositionIndex = optimalPositions[enemyIndex];
		Point optimalPoint = Point(coordinate[optimalPositionIndex][0], coordinate[optimalPositionIndex][1]);
		Grid* newGrid = grid->copy();
		vector<Point> pathToTarget = bestPathToPoint(&newGrid, optimalPoint, myID, 1);
		if (pathToTarget.size() > 1) {
			cerr << "Found optimal positioning. Output: ";
			int offset = is_adjacent((Point)grid->players[myID], pathToTarget[1]);
			switch (offset) {
			case 0:
				cerr << "up." << endl;
				cout << "up" << endl;
				break;
			case 1:
				cerr << "right." << endl;
				cout << "right" << endl;
				break;
			case 2:
				cerr << "down." << endl;
				cout << "down" << endl;
				break;
			case 3:
				cerr << "left." << endl;
				cout << "left" << endl;
				break;
			default:
				cerr << "pass." << endl;
				cout << "pass" << endl;
				break;
			}
		} else {
			cerr << "No path to optimal position. Looking for bug-free path to nearest item." << endl;
			vector<Point> bestPath;
			int shortestPathLength = INT_MAX;
			for (int targetIndex = 0; targetIndex < targetPoints.size(); ++targetIndex) {
				vector<Point> pathToTarget = shortestPathAroundBugsToPoint(grid, targetPoints[targetIndex], myID);
				if (pathToTarget.size() > 0 && pathToTarget.size() < shortestPathLength) {
					bestPath = pathToTarget;
					shortestPathLength = pathToTarget.size();
				}
			}
			if (bestPath.size() > 1) {
				cerr << "Found path around bugs to nearest item. Output: ";
				int offset = is_adjacent((Point)grid->players[myID], bestPath[1]);
				switch (offset) {
				case 0:
					cerr << "up." << endl;
					cout << "up" << endl;
					break;
				case 1:
					cerr << "right." << endl;
					cout << "right" << endl;
					break;
				case 2:
					cerr << "down." << endl;
					cout << "down" << endl;
					break;
				case 3:
					cerr << "left." << endl;
					cout << "left" << endl;
					break;
				default:
					cerr << "pass." << endl;
					cout << "pass" << endl;
					break;
				}
			} else {
				cerr << "No path available to any item around bugs. Looking for adjacent bugs." << endl;
				bool adjacentBugs[4] = { false, false, false, false };
				int adjacentEnemy = -1;
				for (int bugIt = 0; bugIt < grid->bugs.size(); ++bugIt) {
					int bugDir = grid->bug_directions[bugIt];
					int bugIndex = index[grid->bugs[bugIt].x][grid->bugs[bugIt].y];
					if (bugIndex == -1) {
						int pathLength = path_lengths[bugIndex][myIndex];
						if (pathLength == 1) {
							int offset = is_adjacent((Point)grid->players[myID], grid->bugs[bugIt]);
							if (offset != -1)
								adjacentBugs[offset] = true;
						} else if (pathLength == 2) {
							int offset = paths[bugIndex][myIndex];
							Point offsetBug = offsetPoint(grid->bugs[bugIt], offset);
							offset = is_adjacent((Point)grid->players[myID], offsetBug);
							if (offset != -1)
								adjacentBugs[offset] = true;
						}
					} else {
						int pathLength = path_lengths_with_direction[bugDir][bugIndex][myIndex];
						if (pathLength == 1) {
							int offset = is_adjacent((Point)grid->players[myID], grid->bugs[bugIt]);
							if (offset != -1)
								adjacentBugs[offset] = true;
						} else if (pathLength == 2) {
							int offset = paths_with_direction[bugDir][bugIndex][myIndex];
							Point offsetBug = offsetPoint(grid->bugs[bugIt], offset);
							offset = is_adjacent((Point)grid->players[myID], offsetBug);
							if (offset != -1)
								adjacentBugs[offset] = true;
						}
					}
				}
				if (grid->players[!myID].has_weapon) {
					int pathLength = path_lengths[enemyIndex][myIndex];
					if (pathLength == 1) {
						int offset = is_adjacent((Point)grid->players[myID], (Point)grid->players[!myID]);
						if (offset != -1)
							adjacentEnemy = offset;
					} else if (pathLength == 2) {
						int offset = paths[enemyIndex][myIndex];
						Point offsetEnemy = offsetPoint((Point)grid->players[!myID], offset);
						offset = is_adjacent((Point)grid->players[myID], offsetEnemy);
						if (offset != -1)
							adjacentEnemy = offset;
					}
				}
				vector<Point> neighbors = getAdjacentCells(grid, (Point)grid->players[myID]);
				bool foundNeighbor = false;
				for (int i = 0; i < neighbors.size(); ++i) {
					int offset = is_adjacent((Point)grid->players[myID], neighbors[i]);
					if (!adjacentBugs[offset] && offset != adjacentEnemy) {
						foundNeighbor = true;
						cerr << "Found adjacent position without a bug. Output: ";
						switch (offset) {
						case 0:
							cerr << "up." << endl;
							cout << "up" << endl;
							break;
						case 1:
							cerr << "right." << endl;
							cout << "right" << endl;
							break;
						case 2:
							cerr << "down." << endl;
							cout << "down" << endl;
							break;
						case 3:
							cerr << "left." << endl;
							cout << "left" << endl;
							break;
						default:
							cerr << "pass." << endl;
							cout << "pass" << endl;
							break;
						}
						break;
					}
				}
				if (!foundNeighbor) {
					cerr << "None of the possible moves can avoid a bug! ";
					int shortestPath = INT_MAX;
					int offset = -1;
					for (int targetIt = 0; targetIt < targetPoints.size(); ++targetIt) {
						int targetIndex = index[targetPoints[targetIt].x][targetPoints[targetIt].y];
						if (path_lengths[myIndex][targetIndex] < shortestPath && adjacentEnemy != paths[myIndex][targetIndex]) {
							shortestPath = path_lengths[myIndex][targetIndex];
							offset = paths[myIndex][targetIndex];
						}
					}
					if (offset != -1) {
						cerr << "Finding the shortest path to the nearest item. (Will hit a bug!) Output: ";
						switch (offset) {
						case 0:
							cerr << "up." << endl;
							cout << "up" << endl;
							break;
						case 1:
							cerr << "right." << endl;
							cout << "right" << endl;
							break;
						case 2:
							cerr << "down." << endl;
							cout << "down" << endl;
							break;
						case 3:
							cerr << "left." << endl;
							cout << "left" << endl;
							break;
						default:
							cerr << "pass." << endl;
							cout << "pass" << endl;
							break;
						}
					} else {
						int offset = paths[myIndex][optimalPositionIndex];
						if (offset != adjacentEnemy) {
							cerr << "Finding the shortest path to the optimal point on board. (Will hit a bug!) Output: ";
							switch (offset) {
							case 0:
								cerr << "up." << endl;
								cout << "up" << endl;
								break;
							case 1:
								cerr << "right." << endl;
								cout << "right" << endl;
								break;
							case 2:
								cerr << "down." << endl;
								cout << "down" << endl;
								break;
							case 3:
								cerr << "left." << endl;
								cout << "left" << endl;
								break;
							default:
								cerr << "pass." << endl;
								cout << "pass" << endl;
								break;
							}
						} else {
							bool foundNeighbor = false;
							for (int i = 0; i < neighbors.size(); ++i) {
								int offset = is_adjacent((Point)grid->players[myID], neighbors[i]);
								if (offset != adjacentEnemy) {
									foundNeighbor = true;
									cerr << "No other options available. Choosing first neighbor path that doesn't intersect with weaponized opponent. Output: ";
									switch (offset) {
									case 0:
										cerr << "up." << endl;
										cout << "up" << endl;
										break;
									case 1:
										cerr << "right." << endl;
										cout << "right" << endl;
										break;
									case 2:
										cerr << "down." << endl;
										cout << "down" << endl;
										break;
									case 3:
										cerr << "left." << endl;
										cout << "left" << endl;
										break;
									default:
										cerr << "pass." << endl;
										cout << "pass" << endl;
										break;
									}
								}
								break;
							}
							if (!foundNeighbor) {
								cerr << "No paths exist which avoid the weaponized opponent. Taking first neighbor. Output: ";
								int offset = is_adjacent((Point)grid->players[myID], neighbors[0]);
								switch (offset) {
								case 0:
									cerr << "up." << endl;
									cout << "up" << endl;
									break;
								case 1:
									cerr << "right." << endl;
									cout << "right" << endl;
									break;
								case 2:
									cerr << "down." << endl;
									cout << "down" << endl;
									break;
								case 3:
									cerr << "left." << endl;
									cout << "left" << endl;
									break;
								default:
									cerr << "pass." << endl;
									cout << "pass" << endl;
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

int main() {
	Grid* grid = new Grid(20, 14);
	while (true) {
		process_next_command(grid);
	}
	return 0;
}