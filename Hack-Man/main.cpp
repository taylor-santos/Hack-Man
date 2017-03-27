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

	vector<Point> nextPath;
	vector<Point> enemyPath;
	enemyPath.push_back(grid->players[!myID]);
	Grid* currGrid = grid->copy();
	int currLength = 0;
	bool foundPath = false;
	do {
		nextPath = closestItemAroundBugs(&currGrid, !myID);
		enemyPath.insert(enemyPath.end(), nextPath.begin(), nextPath.end());
		currLength += nextPath.size();
		if (nextPath.size() > 0) {
			vector<Point> playerPath = shortestPathAroundBugsToPoint(grid, nextPath.back(), myID);
			if (playerPath.size() > 0 && playerPath.size() < currLength) {
				cerr << playerPath.size() << " < " << currLength << endl;
				int offset = is_adjacent((Point)grid->players[myID], playerPath[0]);
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
				foundPath = true;
				break;
			} else {
				cerr << playerPath.size() << " > " << currLength << endl;
				vector<Point>::iterator itemIt = find(targetPoints.begin(), targetPoints.end(), nextPath.back());
				if (itemIt != targetPoints.end()) {
					targetPoints.erase(itemIt);
				}
			}
		}
	} while (nextPath.size() > 0);
	if (!foundPath) {
		vector<Point> bestPath;
		for (int i = 0; i < targetPoints.size(); ++i) {
			vector<Point> playerPath = shortestPathAroundBugsToPoint(grid, targetPoints[i], myID);
			if (playerPath.size() > 0 && (playerPath.size() < bestPath.size() || bestPath.size() == 0)) {
				bestPath = playerPath;
			}
		}
		if (bestPath.size() > 0) {
			int offset = is_adjacent((Point)grid->players[myID], bestPath[0]);
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
			vector<Point> optimalPath = optimalPathGivenEnemyPath(grid, enemyPath, myID);
			if (optimalPath.size() > 1) {
				int offset = is_adjacent((Point)grid->players[myID], optimalPath[1]);
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
				cerr << "pass." << endl;
				cout << "pass" << endl;
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