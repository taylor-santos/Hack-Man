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
	int myIndex = index[grid->players[myID]->x][grid->players[myID]->y];
	if (grid->snippets.size() == 0 && grid->weapons.size() == 0) {
		cerr << "No items on board. Checking for adjacent bugs." << endl;
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
		}
		else {
			cerr << "No adjacent bugs. Standing still." << endl;
			cout << "pass" << endl;
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
			cerr << "No optimal path found." << endl;
			bool adjacentBugs[4] = { false, false, false, false };
			for (int i = 0; i < grid->bugs.size(); ++i) {
				int bugIndex = index[grid->bugs[i]->x][grid->bugs[i]->y];
				if (path_lengths[bugIndex][myIndex] < 3) {
					cerr << "Bug is blocking path, ";
					int adjacent = is_adjacent((Point)*grid->players[myID], (Point)*grid->bugs[i]);
					if (adjacent == -1) {
						int offset = paths[bugIndex][myIndex];
						Point newBugPos = offsetPoint((Point)*grid->bugs[i], offset);
						adjacent = is_adjacent((Point)*grid->players[myID], newBugPos);
					}
					assert(adjacent != -1);
					adjacentBugs[adjacent] = true;
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
			cerr << "Targeting closest item." << endl;
			int offset = -1;
			int bugOffset = -1;
			int bestDist = INT_MAX;
			int bugBestDist = INT_MAX;
			for (int i = 0; i < grid->snippets.size(); ++i) {
				int snippetIndex = index[grid->snippets[i]->x][grid->snippets[i]->y];
				int length = path_lengths[myIndex][snippetIndex];
				cerr << "    Snippet at (" << grid->snippets[i]->x << "," << grid->snippets[i]->y << ") is " << length << " units away." << endl;
				if (length < bestDist) {
					int newOffset = paths[myIndex][snippetIndex];
					if (!adjacentBugs[newOffset]) {
						bestDist = length;
						offset = newOffset;
					}
					else {
						cerr << "        Unfortunately, its path is blocked by an adjacent bug." << endl;
					}
				}
				if (length < bugBestDist) {
					int newOffset = paths[myIndex][snippetIndex];
					bugBestDist = length;
					bugOffset = newOffset;
				}
			}
			for (int i = 0; i < grid->weapons.size(); ++i) {
				int weaponIndex = index[grid->weapons[i]->x][grid->weapons[i]->y];
				int length = path_lengths[myIndex][weaponIndex];
				cerr << "    Weapon at (" << grid->weapons[i]->x << "," << grid->weapons[i]->y << ") is " << length << " units away." << endl;
				if (length < bestDist) {
					int newOffset = paths[myIndex][weaponIndex];
					if (!adjacentBugs[newOffset]) {
						bestDist = length;
						offset = newOffset;
					}
					else {
						cerr << "        Unfortunately, its path is blocked by an adjacent bug." << endl;
					}
				}
				if (length < bugBestDist) {
					int newOffset = paths[myIndex][weaponIndex];
					bugBestDist = length;
					bugOffset = newOffset;
				}
			}
			if (offset == -1) {
				cerr << "Every path to an item is blocked by an adjacent bug (!), choosing an escape route." << endl;
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
					cerr << "Oh no! No possible path avoids the bugs! Going towards nearest item anyways, even though there's a bug in the way :(" << endl;
					switch (bugOffset) {
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
			}
			else {
				switch (offset) {
				case 0:
					cout << "up" << endl;
					cerr << "Output: up" << endl;
					break;
				case 1:
					cout << "right" << endl;
					cerr << "Output: right" << endl;
					break;
				case 2:
					cout << "down" << endl;
					cerr << "Output: down" << endl;
					break;
				case 3:
					cout << "left" << endl;
					cerr << "Output: left" << endl;
					break;
				default:
					cout << "pass" << endl;
					cerr << "Output: pass" << endl;
					break;
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