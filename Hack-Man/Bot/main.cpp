#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <queue>
#include <climits>
#include <assert.h>
#include "paths.h"
#include "Cell.h"
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
					grid->cells[x][y]->set_wall(true);
					grid->wallCount++;
					continue;
				}
				else if (c == '.') {
					continue;
				}
				else if (c == 'E') {
					grid->bugs.push_back(grid->cells[x][y]);
					int bugDirection = -1;
					for (int j = 0; j < prevBugs.size(); ++j)
					{
						int adjacent = is_adjacent(prevBugs[j], (Point)*grid->cells[x][y]);
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
					grid->weapons.push_back(grid->cells[x][y]);
					continue;
				}
				else if (c == 'C') {
					grid->snippets.push_back(grid->cells[x][y]);
					continue;
				}
				else {
					int id = c - '0';
					grid->players[id]->x = x;
					grid->players[id]->y = y;
					continue;
				}
			}
		}
		else if (type == "snippets") {
			int snippets;
			cin >> snippets;
			if (player_name == myName) {
				grid->players[myID]->snippets = snippets;
			}
			else {
				grid->players[!myID]->snippets = snippets;
			}
		}
		else if (type == "has_weapon") {
			string value;
			cin >> value;
			if (player_name == myName) {
				grid->players[myID]->has_weapon = (value == "true");
			}
			else {
				grid->players[!myID]->has_weapon = (value == "true");
			}
		}
		else if (type == "is_paralyzed") {
			string value;
			cin >> value;
			if (player_name == myName) {
				grid->players[myID]->is_paralyzed = (value == "true");
			}
			else {
				grid->players[!myID]->is_paralyzed = (value == "true");
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
			prevBugs.push_back((Point)*grid->bugs[i]);
		}
		grid->reset();
	}
}

void do_move(Grid* grid) {
	cerr << "MOVE " << current_round << ":" << endl;
	for (int x = -1; x<21; ++x)
		wall_character(grid, x, -1);
	cerr << endl;
	for (int y = 0; y < 14; ++y) {
		wall_character(grid, -1, y);
		for (int x = 0; x < 20; ++x) {
			vector<Cell*>::iterator it = find(grid->bugs.begin(), grid->bugs.end(), grid->cells[x][y]);
			if (it != grid->bugs.end()) {
				if (grid->cells[x][y]->is_wall())
					cerr << " ";
				else
					cerr << " ";
				switch (grid->bug_directions[it - grid->bugs.begin()]) {
				case 0:
					cerr << "E^";
					break;
				case 1:
					cerr << "E>";
					break;
				case 2:
					cerr << "Ev";
					break;
				case 3:
					cerr << "E<";
					break;
				default:
					if (grid->cells[x][y]->is_wall())
						cerr << "E ";
					else
						cerr << "E ";
					break;
				}
			} else if (grid->cells[x][y]->is_wall())
				wall_character(grid, x, y);
			else if (find(grid->snippets.begin(), grid->snippets.end(), grid->cells[x][y]) != grid->snippets.end())
				cerr << "SSS";
			else if (find(grid->weapons.begin(), grid->weapons.end(), grid->cells[x][y]) != grid->weapons.end())
				cerr << "WWW";
			else if (grid->players[myID]->x == x && grid->players[myID]->y == y)
				cerr << "AAA";
			else if (grid->players[!myID]->x == x && grid->players[!myID]->y == y)
				cerr << "BBB";
			else {
				cerr << "   ";
			}
		}
		wall_character(grid, 20, y);
		cerr << endl;
	}
	for (int x = -1; x<21; ++x)
		wall_character(grid, x, 14);
	cerr << endl;
	int myIndex = index[grid->players[myID]->x][grid->players[myID]->y];
	int enemyIndex = index[grid->players[!myID]->x][grid->players[!myID]->y];
	if (grid->snippets.size() == 0 && grid->weapons.size() == 0) {
		int optimalPosition = optimalPositions[enemyIndex];
		int pointX = coordinate[optimalPosition][0];
		int pointY = coordinate[optimalPosition][1];
		cerr << "No items on board. Moving towards optimal position (" << pointX << "," << pointY << ")" << endl;
		vector<Point> path = shortestPathAroundBugsToPoint(grid, (Point)*grid->cells[pointX][pointY], myID);
		if (path.size() > 1) {
			int adjacent = is_adjacent((Point)*grid->players[myID], path[1]);
			cerr << "Taking direction: ";
			switch (adjacent) {
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
				cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
				cout << "pass" << endl;
				break;
			}
		} else {
			bool adjacentBugs[4] = { false, false, false, false };
			bool adjacentBug = false;
			for (int i = 0; i < grid->bugs.size(); ++i) {
				int bugIndex = index[grid->bugs[i]->x][grid->bugs[i]->y];
				if (path_lengths[bugIndex][myIndex] < 3) {
					cerr << "Bug is nearby, ";
					int adjacent = is_adjacent((Point)*grid->players[myID], (Point)*grid->bugs[i]);
					if (adjacent == -1) {

						int offset = paths[bugIndex][myIndex];
						Point newBugPos = offsetPoint((Point)*grid->bugs[i], offset);
						adjacent = is_adjacent((Point)*grid->players[myID], newBugPos);
					}
					assert(adjacent != -1);
					adjacentBugs[adjacent] = true;
					adjacentBug = true;
					cerr << "can't go ";
					switch (adjacent) {
					case 0:
						cerr << "up." << endl;
						break;
					case 1:
						cerr << "right." << endl;
						break;
					case 2:
						cerr << "down." << endl;
						break;
					case 3:
						cerr << "left." << endl;
						break;
					default:
						cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
						break;
					}
				}
			}
			if (adjacentBug) {
				vector<Point> neighbors = getAdjacentCells(grid, (Point)*grid->players[myID]);
				bool foundPath = false;
				for (int i = 0; i < neighbors.size(); ++i) {
					int adjacent = is_adjacent((Point)*grid->players[myID], neighbors[i]);
					if (!adjacentBugs[adjacent]) {
						foundPath = true;
						cerr << "Found a path: ";
						switch (adjacent) {
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
							cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
							cout << "pass" << endl;
							break;
						}
						break;
					}
				}
				if (!foundPath) {
					cerr << "Oh no! No possible path avoids the bugs! Taking first choice." << endl;
					int adjacent = is_adjacent((Point)*grid->players[myID], neighbors[0]);
					switch (adjacent) {
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
						cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
						cout << "pass" << endl;
						break;
					}
				}
			} else {
				cerr << "No adjacent bugs. Standing still." << endl;
				cout << "pass" << endl;
			}
		}
	}
	else {
		vector<Point> bestPath = findClosestItem(grid, myID);
		if (bestPath.size() > 1) {
			cerr << "Found best path." << endl;
			switch (is_adjacent((Point)*grid->players[myID], (Point)(bestPath[1]))) {
			case 0:
				cout << "up" << endl;
				cerr << "up" << endl;
				break;
			case 1:
				cout << "right" << endl;
				cerr << "right" << endl;
				break;
			case 2:
				cout << "down" << endl;
				cerr << "down" << endl;
				break;
			case 3:
				cout << "left" << endl;
				cerr << "left" << endl;
				break;
			default:
				cout << "pass" << endl;
				cerr << "pass" << endl;
				break;
			}
		}
		else {
			int optimalPosition = optimalPositions[enemyIndex];
			int pointX = coordinate[optimalPosition][0];
			int pointY = coordinate[optimalPosition][1];
			cerr << "No optimal path. Moving towards optimal position (" << pointX << "," << pointY << ")" << endl;
			vector<Point> path = shortestPathAroundBugsToPoint(grid, (Point)*grid->cells[pointX][pointY], myID);
			if (path.size() > 1) {
				int adjacent = is_adjacent((Point)*grid->players[myID], path[1]);
				cerr << "Taking direction: ";
				switch (adjacent) {
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
					cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
					cout << "pass" << endl;
					break;
				}
			} else {
				bool adjacentBugs[4] = { false, false, false, false };
				bool adjacentBug = false;
				for (int i = 0; i < grid->bugs.size(); ++i) {
					int bugIndex = index[grid->bugs[i]->x][grid->bugs[i]->y];
					if (path_lengths[bugIndex][myIndex] < 3) {
						cerr << "Bug is nearby, ";
						int adjacent = is_adjacent((Point)*grid->players[myID], (Point)*grid->bugs[i]);
						if (adjacent == -1) {

							int offset = paths[bugIndex][myIndex];
							Point newBugPos = offsetPoint((Point)*grid->bugs[i], offset);
							adjacent = is_adjacent((Point)*grid->players[myID], newBugPos);
						}
						assert(adjacent != -1);
						adjacentBugs[adjacent] = true;
						adjacentBug = true;
						cerr << "can't go ";
						switch (adjacent) {
						case 0:
							cerr << "up." << endl;
							break;
						case 1:
							cerr << "right." << endl;
							break;
						case 2:
							cerr << "down." << endl;
							break;
						case 3:
							cerr << "left." << endl;
							break;
						default:
							cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
							break;
						}
					}
				}
				if (adjacentBug) {
					vector<Point> neighbors = getAdjacentCells(grid, (Point)*grid->players[myID]);
					bool foundPath = false;
					for (int i = 0; i < neighbors.size(); ++i) {
						int adjacent = is_adjacent((Point)*grid->players[myID], neighbors[i]);
						if (!adjacentBugs[adjacent]) {
							foundPath = true;
							cerr << "Found a path: ";
							switch (adjacent) {
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
								cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
								cout << "pass" << endl;
								break;
							}
							break;
						}
					}
					if (!foundPath) {
						cerr << "Oh no! No possible path avoids the bugs! Taking first choice." << endl;
						int adjacent = is_adjacent((Point)*grid->players[myID], neighbors[0]);
						switch (adjacent) {
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
							cerr << "pass. (THIS SHOULD NOT BE POSSIBLE)" << endl;
							cout << "pass" << endl;
							break;
						}
					}
				} else {
					cerr << "No adjacent bugs. Standing still." << endl;
					cout << "pass" << endl;
				}
			}
		}
	}
}

int main() {
	srand((int)time(0));
	Grid* grid = new Grid(20, 14);
	while (true) {
		process_next_command(grid);
	}
	return 0;
}