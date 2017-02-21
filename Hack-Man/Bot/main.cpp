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

using namespace std;

int width;
int height;
int timebank;
int time_per_move;
int time_remaining;
int max_rounds;
int current_round;
Player me;
Player enemy;

Grid* CurrGrid;

void do_move(Grid*);
int is_adjacent(Point, Point);
vector<Point> getAdjacentCells(Grid* grid, Point pt);	// Returns a vector of all the playable cells next to Point pt

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
	if (y > 0 && !grid->cells[x][y - 1]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x][y - 1]));
	if (y < grid->height() - 1 && !grid->cells[x][y + 1]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x][y + 1]));
	if (x > 0 && !grid->cells[x - 1][y]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x - 1][y]));
	if (x < grid->width() - 1 && !grid->cells[x + 1][y]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x + 1][y]));
	return adjacent;
}

Point offsetPoint(Point pt, int offset) {
	if (offset == -1)
		return pt;
	assert(offset >= 0 && offset < 4);
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	Point newPoint;
	newPoint.x = pt.x + dx[offset];
	newPoint.y = pt.y + dy[offset];
	return newPoint;
}

vector<Point> findClosestItem(Point start, Grid* grid, bool weapon) {
	if (grid->snippets.size() == 0 && grid->weapons.size() == 0)
		return vector<Point>();
	queue<Point> start_Q;
	queue<Point> enemy_Q;
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	start_Q.push(start);
	enemy_Q.push((Point)enemy);
	grid_Q.push(grid->copy());
	path_Q.push(vector<Point>());
	while (start_Q.size() > 0) {
		Point curr_start = start_Q.front();
		start_Q.pop();
		Point curr_enemy = enemy_Q.front();
		enemy_Q.pop();
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();
		curr_path.push_back(curr_start);
		bool foundItem = false;
		for (int i = 0; i < curr_grid->snippets.size(); ++i) {
			if (curr_start == (Point)(*curr_grid->snippets[i])) {
				foundItem = true;
			}
		}
		for (int i = 0; i < curr_grid->weapons.size(); ++i) {
			if (curr_start == (Point)(*curr_grid->weapons[i])) {
				foundItem = true;
			}
		}
		if (foundItem) {
			while (start_Q.size() > 0) {
				start_Q.pop();
				delete grid_Q.front();
				grid_Q.pop();
				path_Q.pop();
			}
			delete curr_grid;
			return curr_path;
		}
		Grid* newGrid = curr_grid->copy();
		newGrid->cells[curr_start.x][curr_start.y]->set_wall(true);
		newGrid->wallCount++;
		vector<Point> neighbors = getAdjacentCells(curr_grid, curr_start);
		int killedBug = -1;
		vector<int> neighborKilledBug = vector<int>(neighbors.size());
		for (int i = 0; i < neighbors.size(); ++i) {
			neighborKilledBug[i] = -1;
		}
		for (int i = 0; i < newGrid->bugs.size(); ++i) {
			Point bugPos = (Point)*newGrid->bugs[i];
			if (bugPos == curr_start) {
				if (newGrid->playerWeapons[me.id]) {
					killedBug = i;
					newGrid->playerWeapons[me.id] = false;
				}
				else {
					return vector<Point>();
				}
			}
			vector<Point>::iterator it = find(neighbors.begin(), neighbors.end(), bugPos);
			if (it != neighbors.end()) {
				if (newGrid->playerWeapons[me.id]) {
					neighborKilledBug[it - neighbors.begin()] = i;
				}
				else {
					neighbors.erase(it);
				}
			}
			int offset = paths[index[bugPos.x][bugPos.y]][index[curr_start.x][curr_start.y]];
			Point newPos = offsetPoint(bugPos, offset);
			newGrid->bugs[i] = newGrid->cells[newPos.x][newPos.y];
			it = find(neighbors.begin(), neighbors.end(), newPos);
			if (it != neighbors.end())
				neighbors.erase(it);
		}
		if (killedBug != -1) {
			newGrid->bugs.erase(newGrid->bugs.begin() + killedBug);
		}
		if (newGrid->playerWeapons[enemy.id] && !newGrid->playerWeapons[me.id] ||
			newGrid->playerWeapons[enemy.id] && me.snippets < 4) {
			Point enemyPos = (Point)curr_enemy;
			if (enemyPos == curr_start)
				return vector<Point>();
			vector<Point>::iterator it = find(neighbors.begin(), neighbors.end(), enemyPos);
			if (it != neighbors.end())
				neighbors.erase(it);
			int offset = paths[index[enemyPos.x][enemyPos.y]][index[curr_start.x][curr_start.y]];
			Point newPos = offsetPoint(enemyPos, offset);
			it = find(neighbors.begin(), neighbors.end(), newPos);
			if (it != neighbors.end())
				neighbors.erase(it);
		}

		int bestDist = INT_MAX;
		int bestOffset = -1;
		int enemyIndex = index[curr_enemy.x][curr_enemy.y];
		if (newGrid->playerWeapons[enemy.id] && !newGrid->playerWeapons[me.id])
		{
			int meIndex = index[curr_start.x][curr_start.y];
			if (path_lengths[enemyIndex][meIndex] < bestDist) {
				bestDist = path_lengths[enemyIndex][meIndex];
				bestOffset = paths[enemyIndex][meIndex];
			}
		}
		for (int i = 0; i < newGrid->snippets.size(); ++i) {
			int snipIndex = index[newGrid->snippets[i]->x][newGrid->snippets[i]->y];
			if (path_lengths[enemyIndex][snipIndex] < bestDist) {
				bestDist = path_lengths[enemyIndex][snipIndex];
				bestOffset = paths[enemyIndex][snipIndex];
			}
		}
		for (int i = 0; i < newGrid->weapons.size(); ++i) {
			int wepIndex = index[newGrid->weapons[i]->x][newGrid->weapons[i]->y];
			if (path_lengths[enemyIndex][wepIndex] < bestDist) {
				bestDist = path_lengths[enemyIndex][wepIndex];
				bestOffset = paths[enemyIndex][wepIndex];
			}
		}
		if (bestOffset != -1)
			curr_enemy = offsetPoint(curr_enemy, bestOffset);

		vector<Cell*>::iterator snip_it = find(newGrid->snippets.begin(), newGrid->snippets.end(), newGrid->cells[curr_enemy.x][curr_enemy.y]);
		if (snip_it != newGrid->snippets.end())
			newGrid->snippets.erase(snip_it);
		vector<Cell*>::iterator weap_it = find(newGrid->weapons.begin(), newGrid->weapons.end(), newGrid->cells[curr_enemy.x][curr_enemy.y]);
		if (weap_it != newGrid->weapons.end())
			newGrid->weapons.erase(weap_it);
		if (newGrid->snippets.size() != 0 || newGrid->weapons.size() != 0) {
			for (int i = 0; i < neighbors.size(); ++i) {

				start_Q.push(neighbors[i]);
				enemy_Q.push(curr_enemy);
				Grid* newGridCopy = newGrid->copy();
				if (neighborKilledBug[i] != -1) {
					newGridCopy->bugs.erase(newGridCopy->bugs.begin() + neighborKilledBug[i]);
					newGridCopy->playerWeapons[me.id] = false;
				}
				grid_Q.push(newGridCopy);
				path_Q.push(curr_path);
			}
		}
		delete newGrid;
		delete curr_grid;
	}
	return vector<Point>();
}

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
			// player names aren't very useful
		}
		else if (type == "your_bot") {
			cin >> me.name;
		}
		else if (type == "your_botid") {
			cin >> me.id;
			enemy.id = !me.id;
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
			int n = s.length();
			int i = 0;
			for (int y = 0; y < grid->height(); y++) {
				for (int x = 0; x < grid->width(); x++) {
					Point pt;
					pt.x = x;
					pt.y = y;
					while (true) {
						if (i == n || s[i] == ',') {
							i++;
							break;
						}
						char c = s[i++];
						if (c == 'x') {
							grid->cells[x][y]->set_wall(true);
							grid->wallCount++;
						}
						else if (c == '.') {
							//do nothing, is_wall[x][y] == 0 by default
						}
						else if (c == 'E') {
							grid->bugs.push_back(grid->cells[x][y]);
						}
						else if (c == 'W') {
							grid->weapons.push_back(grid->cells[x][y]);
						}
						else if (c == 'C') {
							grid->snippets.push_back(grid->cells[x][y]);
						}
						else {
							// played id
							int id = c - '0';
							if (id == me.id) {
								me.x = x;
								me.y = y;
							}
							else {
								enemy.x = x;
								enemy.y = y;
							}
						}
					}
				}
			}
		}
		else if (type == "snippets") {
			if (player_name == me.name) {
				cin >> me.snippets;
			}
			else {
				cin >> enemy.snippets;
			}
		}
		else if (type == "has_weapon") {
			string value;
			cin >> value;
			if (player_name == me.name) {
				me.has_weapon = (value == "true");
				if (me.has_weapon)
					grid->playerWeapons[me.id] = true;
				else
					grid->playerWeapons[me.id] = false;
			}
			else {
				enemy.has_weapon = (value == "true");
				if (enemy.has_weapon)
					grid->playerWeapons[enemy.id] = true;
				else
					grid->playerWeapons[enemy.id] = false;
			}
		}
		else if (type == "is_paralyzed") {
			string value;
			cin >> value;
			if (player_name == me.name) {
				me.is_paralyzed = (value == "true");
			}
			else {
				enemy.is_paralyzed = (value == "true");
			}
		}
	}
	else if (command == "action") {
		string useless_move;
		cin >> useless_move;
		cin >> time_remaining;
		do_move(grid);
		grid->reset();
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

//-----------------------------------------//
//  Improve the code below to win 'em all  //
//-----------------------------------------//

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
string moves[4] = { "up", "left", "down", "right" };


void do_move(Grid* grid) {

	cerr << "MOVE " << current_round << ":" << endl;
	/*
	int offset = -1;
	int bestDist = INT_MAX;
	Point chosenSnippet;
	for (int i = 0; i < grid->snippets.size(); ++i) {
	int length = path_lengths[index[me.x][me.y]][index[grid->snippets[i]->x][grid->snippets[i]->y]];
	cerr << "Snippet at (" << grid->snippets[i]->x << "," << grid->snippets[i]->y << ") is " << length << " units away." << endl;
	if (length < bestDist) {
	bestDist = length;
	offset = paths[index[me.x][me.y]][index[grid->snippets[i]->x][grid->snippets[i]->y]];
	chosenSnippet = (Point)*grid->snippets[i];
	}
	}
	switch (offset) {
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

	for (int y = 0; y < 14; ++y) {
	for (int x = 0; x < 20; ++x) {
	if (find(grid->bugs.begin(), grid->bugs.end(), grid->cells[x][y]) != grid->bugs.end()) {
	if (grid->cells[x][y]->is_wall())
	cerr << "X";
	else
	cerr << " ";
	cerr << "E";
	}
	else if (grid->cells[x][y]->is_wall())
	cerr << "XX";
	else if (find(grid->snippets.begin(), grid->snippets.end(), grid->cells[x][y]) != grid->snippets.end()) {
	if ((Point)*grid->cells[x][y] == chosenSnippet)
	cerr << " S";
	else
	cerr << " s";
	}
	else if (find(grid->weapons.begin(), grid->weapons.end(), grid->cells[x][y]) != grid->weapons.end())
	cerr << " W";
	else if (me.x == x && me.y == y)
	cerr << " " << me.id;
	else if (enemy.x == x && enemy.y == y)
	cerr << " " << enemy.id;
	else
	cerr << "  ";
	}
	cerr << endl;
	}
	*/
	if (grid->snippets.size() == 0 && grid->weapons.size() == 0) {
		cerr << "No items on board. Checking for adjacent bugs." << endl;
		bool adjacentBugs[4] = { false, false, false, false };
		bool adjacentBug = false;
		for (int i = 0; i < grid->bugs.size(); ++i) {
			if (path_lengths[index[grid->bugs[i]->x][grid->bugs[i]->y]][index[me.x][me.y]] < 3) {
				cerr << "Bug is nearby, ";
				int adjacent = is_adjacent((Point)me, (Point)*grid->bugs[i]);
				if (adjacent == -1) {
					int offset = paths[index[grid->bugs[i]->x][grid->bugs[i]->y]][index[me.x][me.y]];
					Point newBugPos = offsetPoint((Point)*grid->bugs[i], offset);
					adjacent = is_adjacent((Point)me, newBugPos);
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
			vector<Point> neighbors = getAdjacentCells(grid, (Point)me);
			bool foundPath = false;
			for (int i = 0; i < neighbors.size(); ++i) {
				int adjacent = is_adjacent((Point)me, neighbors[i]);
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
				int adjacent = is_adjacent((Point)me, neighbors[0]);
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

		vector<Point> bestPath = findClosestItem((Point)me, grid, me.has_weapon);
		if (bestPath.size() > 1) {
			cerr << "Found best path." << endl;
			switch (is_adjacent((Point)me, (Point)(bestPath[1]))) {
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
				if (path_lengths[index[grid->bugs[i]->x][grid->bugs[i]->y]][index[me.x][me.y]] < 3) {
					cerr << "Bug is blocking path, ";
					int adjacent = is_adjacent((Point)me, (Point)*grid->bugs[i]);
					if (adjacent == -1) {
						int offset = paths[index[grid->bugs[i]->x][grid->bugs[i]->y]][index[me.x][me.y]];
						Point newBugPos = offsetPoint((Point)*grid->bugs[i], offset);
						adjacent = is_adjacent((Point)me, newBugPos);
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
				int length = path_lengths[index[me.x][me.y]][index[grid->snippets[i]->x][grid->snippets[i]->y]];
				cerr << "    Snippet at (" << grid->snippets[i]->x << "," << grid->snippets[i]->y << ") is " << length << " units away." << endl;
				if (length < bestDist) {
					int newOffset = paths[index[me.x][me.y]][index[grid->snippets[i]->x][grid->snippets[i]->y]];
					if (!adjacentBugs[newOffset]) {
						bestDist = length;
						offset = newOffset;
					}
					else {
						cerr << "        Unfortunately, its path is blocked by an adjacent bug." << endl;
					}
				}
				if (length < bugBestDist) {
					int newOffset = paths[index[me.x][me.y]][index[grid->snippets[i]->x][grid->snippets[i]->y]];
					bugBestDist = length;
					bugOffset = newOffset;
				}
			}
			for (int i = 0; i < grid->weapons.size(); ++i) {
				int length = path_lengths[index[me.x][me.y]][index[grid->weapons[i]->x][grid->weapons[i]->y]];
				cerr << "    Weapon at (" << grid->weapons[i]->x << "," << grid->weapons[i]->y << ") is " << length << " units away." << endl;
				if (length < bestDist) {
					int newOffset = paths[index[me.x][me.y]][index[grid->weapons[i]->x][grid->weapons[i]->y]];
					if (!adjacentBugs[newOffset]) {
						bestDist = length;
						offset = newOffset;
					}
					else {
						cerr << "        Unfortunately, its path is blocked by an adjacent bug." << endl;
					}
				}
				if (length < bugBestDist) {
					int newOffset = paths[index[me.x][me.y]][index[grid->weapons[i]->x][grid->weapons[i]->y]];
					bugBestDist = length;
					bugOffset = newOffset;
				}
			}
			if (offset == -1) {
				cerr << "Every path to an item is blocked by an adjacent bug (!), choosing an escape route." << endl;
				vector<Point> neighbors = getAdjacentCells(grid, (Point)me);
				bool foundPath = false;
				for (int i = 0; i < neighbors.size(); ++i) {
					int adjacent = is_adjacent((Point)me, neighbors[i]);
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

	for (int y = 0; y < 14; ++y) {
		for (int x = 0; x < 20; ++x) {
			if (find(grid->bugs.begin(), grid->bugs.end(), grid->cells[x][y]) != grid->bugs.end()) {
				if (grid->cells[x][y]->is_wall())
					cerr << " ";
				else
					cerr << " ";
				cerr << "E";
			}
			else if (grid->cells[x][y]->is_wall())
				cerr << "  ";
			else if (find(grid->snippets.begin(), grid->snippets.end(), grid->cells[x][y]) != grid->snippets.end())
				cerr << " S";
			else if (find(grid->weapons.begin(), grid->weapons.end(), grid->cells[x][y]) != grid->weapons.end())
				cerr << " W";
			else if (me.x == x && me.y == y)
				cerr << " " << me.id;
			else if (enemy.x == x && enemy.y == y)
				cerr << " " << enemy.id;
			else
				cerr << "[]";
		}
		cerr << endl;
	}
	/*
	if (bestPath.size() <= 1){
	vector<Point> possibleMoves = getAdjacentCells(grid, (Point)me);
	bool adjacentBug = false;
	for (int i = 0; i < grid->bugs.size(); ++i) {
	vector<Point>::iterator it = find(possibleMoves.begin(), possibleMoves.end(), (Point)*grid->bugs[i]);
	if (it != possibleMoves.end()) {
	adjacentBug = true;
	possibleMoves.erase(it);
	}
	}
	if (adjacentBug && possibleMoves.size() > 0) {
	cerr << "There is an adjacent bug, must move ";
	switch (is_adjacent((Point)me, (Point)(possibleMoves[0]))) {
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
	vector<Point> bestPath;
	for (int i = 0; i < grid->snippets.size(); ++i) {
	vector<Point> newPath = shortestPath((Point)me, (Point)*grid->snippets[i], grid, false);
	if (bestPath.size() == 0 || bestPath.size() > newPath.size())
	bestPath = newPath;
	}
	for (int i = 0; i < grid->weapons.size(); ++i) {
	vector<Point> newPath = shortestPath((Point)me, (Point)*grid->snippets[i], grid, false);
	if (bestPath.size() == 0 || bestPath.size() > newPath.size())
	bestPath = newPath;
	}
	if (bestPath.size() > 0) {
	cerr << "Seems like enemy is closer to all snippets. Attempting to get there first." << endl;
	switch (is_adjacent((Point)me, (Point)(bestPath[0]))) {
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
	cerr << "ERROR: Enemy is closer to all snippets, and no path is available for some reason!" << endl;
	cout << "pass" << endl;
	cerr << "pass" << endl;
	}
	}
	} else {
	cerr << "Found best path." << endl;
	switch (is_adjacent((Point)me, (Point)(bestPath[1]))) {
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

	for (int y = 0; y < 14; ++y) {
	for (int x = 0; x < 20; ++x) {
	if (find(grid->bugs.begin(), grid->bugs.end(), grid->cells[x][y]) != grid->bugs.end()) {
	if (grid->cells[x][y]->is_wall())
	cerr << "X";
	else
	cerr << " ";
	cerr << "E";
	}
	else if (grid->cells[x][y]->is_wall())
	cerr << "XX";
	else if (find(grid->snippets.begin(), grid->snippets.end(), grid->cells[x][y]) != grid->snippets.end())
	cerr << " S";
	else if (find(grid->weapons.begin(), grid->weapons.end(), grid->cells[x][y]) != grid->weapons.end())
	cerr << " W";
	else if (me.x == x && me.y == y)
	cerr << " " << me.id;
	else if (enemy.x == x && enemy.y == y)
	cerr << " " << enemy.id;
	else
	cerr << "  ";
	}
	cerr << endl;
	}
	*/
}
