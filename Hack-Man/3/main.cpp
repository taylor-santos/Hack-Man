#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <queue>
#include <climits>

using namespace std;

class Point {
public:
	int x;
	int y;
	
	bool operator==(const Point &other) {
		return (x == other.x && y == other.y);
	}
	bool operator!=(const Point &other) {
		return (x != other.x || y != other.y);
	}
};

class Player : public Point {
public:
	string name;
	int id;
	int snippets;
	bool has_weapon;
	bool is_paralyzed;
};

class Cell : public Point {
	bool wall = false;
public:	
	bool is_wall(){ return wall; }
	void set_wall(bool value){ wall = value; }
	Cell(int x, int y){
		this->x = x;
		this->y = y;
	}
};

class Grid {
	int w;
	int h;
	
public:
	vector<vector<Cell*>> cells;
	int wallCount;
	vector<Cell*> snippets;
	vector<Cell*> weapons;
	vector<Cell*> bugs;

	int height() { return h; }
	int width() { return w; }
	Grid* copy() {
		Grid* newGrid = new Grid(w, h);
		for (int x = 0; x < w; ++x) {
			for (int y = 0; y < h; ++y) {
				if (cells[x][y]->is_wall()) {
					newGrid->cells[x][y]->set_wall(true);
					newGrid->wallCount++;
				}
			}
		}
		for (int i = 0; i < snippets.size(); ++i) {
			int x = snippets[i]->x;
			int y = snippets[i]->y;
			newGrid->snippets.push_back(newGrid->cells[x][y]);
		}
		for (int i = 0; i < weapons.size(); ++i) {
			int x = weapons[i]->x;
			int y = weapons[i]->y;
			newGrid->weapons.push_back(newGrid->cells[x][y]);
		}
		for (int i = 0; i < bugs.size(); ++i) {
			int x = bugs[i]->x;
			int y = bugs[i]->y;
			newGrid->bugs.push_back(newGrid->cells[x][y]);
		}
		return newGrid;
	}	
	void make_bugpath() {	//Remove the walls in the 'server room' to allow bug pathfinding.
		cells[ 9][6]->set_wall(false);
		cells[10][6]->set_wall(false);
		cells[ 8][7]->set_wall(false);
		cells[ 9][7]->set_wall(false);
		cells[10][7]->set_wall(false);
		cells[11][7]->set_wall(false);
	}
	void reset() {
		for (int x = 0; x < w; ++x) {
			for (int y = 0; y < h; ++y) {
				delete cells[x][y];
				cells[x][y] = new Cell(x, y);
			}
		}
		wallCount = 0;
		snippets.clear();
		weapons.clear();
		bugs.clear();
	}
	Grid(int width, int height) {
		w = width;
		h = height;
		wallCount = 0;
		cells = vector<vector<Cell*>>(width);
		for (int x = 0; x < width; ++x) {
			cells[x] = vector<Cell*>(height);
			for (int y = 0; y < height; ++y) {
				cells[x][y] = new Cell(x, y);
			}
		}
	}
	~Grid() {
		for (int x = 0; x < w; ++x) {
			for (int y = 0; y < h; ++y) {
				delete cells[x][y];
			}
		}
	}
};

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

int is_adjacent(Point a, Point b){
	/*
	   -1=not adjacent
	    0=up
	    1=right
	    2=down
	    3=left	
	*/
	if (a.x == b.x){
		if (a.y-b.y == 1)
			return 0;
		else if (a.y-b.y == -1)
			return 2;
	}else if (a.y == b.y){
		if (a.x-b.x == 1)
			return 3;
		else if (a.x-b.x == -1)
			return 1;
	}
	return -1;
}

vector<Point> getAdjacentCells(Grid* grid, Point pt){
	vector<Point> adjacent;
	int x = pt.x;
	int y = pt.y;
	if (y > 0  && !grid->cells[x][y-1]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x][y - 1]));
	if (y < grid->height()-1 && !grid->cells[x][y+1]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x][y + 1]));
	if (x > 0  && !grid->cells[x-1][y]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x - 1][y]));
	if (x < grid->width()-1 && !grid->cells[x+1][y]->is_wall())
		adjacent.push_back((Point)(*grid->cells[x + 1][y]));
	return adjacent;
}
/*
vector<Point> shortestPath(Point start, Point end, Grid* grid, bool bugPath) {
	queue<Point> start_Q;
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	start_Q.push(start);
	Grid* gridCopy = grid->copy();
	if (bugPath)
		gridCopy->make_bugpath();
	grid_Q.push(gridCopy);
	path_Q.push(vector<Point>());
	while (start_Q.size() > 0) {
		Point curr_start = start_Q.front();
		start_Q.pop();
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();
		curr_path.push_back(curr_start);
		if (curr_start == end) {
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
		for (int i = 0; i < neighbors.size(); ++i) {
			start_Q.push(neighbors[i]);
			grid_Q.push(newGrid->copy());
			path_Q.push(curr_path);
		}
		delete newGrid;
		delete curr_grid;
	}
	return vector<Point>();
}
*/
vector<Point> shortestPath(Point start, Point end, Grid* grid, bool bugPath) {
	int dist[20][14];
	Cell* prev[20][14];
	vector<Cell*> unvisited;
	Grid* gridCopy = grid->copy();
	if (bugPath)
		gridCopy->make_bugpath();
	for (int x = 0; x<20; ++x) {
		for (int y = 0; y<14; ++y) {
			unvisited.push_back(gridCopy->cells[x][y]);
			dist[x][y] = INT_MAX;
		}
	}
	dist[start.x][start.y] = 0;
	while (find(unvisited.begin(), unvisited.end(), gridCopy->cells[end.x][end.y]) != unvisited.end()) {
		Cell* curr = NULL;
		int minDist = INT_MAX;
		int index = -1;
		for (int i = 0; i<(int)unvisited.size(); ++i) {
			if (dist[unvisited[i]->x][unvisited[i]->y] < minDist) {
				minDist = dist[unvisited[i]->x][unvisited[i]->y];
				curr = unvisited[i];
				index = i;
			}
		}
		unvisited.erase(unvisited.begin() + index);
		vector<Point> neighbors = getAdjacentCells(gridCopy, (Point)(*curr));
		for (int i = 0; i<(int)neighbors.size(); ++i) {
			int alt = dist[curr->x][curr->y] + 1;
			if (alt < dist[neighbors[i].x][neighbors[i].y]) {
				dist[neighbors[i].x][neighbors[i].y] = alt;
				prev[neighbors[i].x][neighbors[i].y] = curr;
			}
		}
	}
	
	vector<Point> path;
	Point curr = end;
	while (curr != start) {
		path.push_back(curr);
		curr = (Point)*prev[curr.x][curr.y];
	}
	reverse(path.begin(), path.end());
	return path;
}

vector<Point> findClosestItem(Point start, Grid* grid) {
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
		for (int i = 0; i < newGrid->bugs.size(); ++i) {
			Point bugPos = (Point)*newGrid->bugs[i];
			if (bugPos == curr_start)
				return vector<Point>();
			vector<Point> newPos = shortestPath(bugPos, curr_start, grid, true);
			if (newPos.size() > 0) {
				newGrid->bugs[i] = newGrid->cells[newPos[0].x][newPos[0].y];
				vector<Point>::iterator it = find(neighbors.begin(), neighbors.end(), newPos[0]);
				if (it != neighbors.end())
					neighbors.erase(it);
			}
		}

		vector<Point> enemyBestPath;
		for (int i = 0; i < newGrid->snippets.size(); ++i) {
			vector<Point> newPath = shortestPath(curr_enemy, (Point)*newGrid->snippets[i], grid, false);
			if (enemyBestPath.size() == 0 || enemyBestPath.size() > newPath.size())
				enemyBestPath = newPath;
		}
		for (int i = 0; i < newGrid->weapons.size(); ++i) {
			vector<Point> newPath = shortestPath(curr_enemy, (Point)*newGrid->weapons[i], grid, false);
			if (enemyBestPath.size() == 0 || enemyBestPath.size() > newPath.size())
				enemyBestPath = newPath;
		}
		if (enemyBestPath.size() > 0)
			curr_enemy = enemyBestPath[0];

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
				grid_Q.push(newGrid->copy());
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
			}
			else {
				enemy.has_weapon = (value == "true");
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
	vector<Point> bestPath = findClosestItem((Point)me, grid);
	/*
	for (int i = 0; i < grid->snippets.size(); ++i) {
		Point start = (Point)me;
		Point end = (Point)(*grid->snippets[i]);
		vector<Point> newPath = findBestPath(start, end, grid);
		if (bestPath.size() == 0 || bestPath.size() > newPath.size())
		{
			bestPath = newPath;
		}
	}
	for (int i = 0; i < grid->weapons.size(); ++i) {
		vector<Point> newPath = findBestPath((Point)me, (Point)(*grid->weapons[i]), grid);
		if (bestPath.size() == 0 || bestPath.size() > newPath.size())
		{
			bestPath = newPath;
		}
	}
	*/
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
}
