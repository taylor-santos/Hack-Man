#include <iostream>
#include <stdlib.h>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>
#include <queue>
#include <climits>
//#include <fstream>

using namespace std;

class Point {
public:
	int x;
	int y;
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

vector<vector<Cell*>*> grid;
//ofstream cerr;

int width;
int height;
vector<vector<int> > is_wall;
int timebank;
int time_per_move;
int time_remaining;
int max_rounds;
int current_round;
Player me;
Player enemy;
vector<Cell*> snippets;
vector<Cell*> weapons;
vector<Cell*> bugs;

void do_move();

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

void clear_grid(){
	for (int x=0; x<20; ++x){		
		for (int y=0; y<14; ++y){
			delete (*grid[x])[y];
		}
		delete grid[x];
	}
	grid.clear();	
}

void make_grid(){
	for (int x=0; x<20; ++x){
		grid.push_back(new vector<Cell*>());
		for (int y=0; y<20; ++y){
			grid[x]->push_back(new Cell(x,y));
		}
	}
}

vector<Cell*> getAdjacentCells(int x, int y){
	vector<Cell*> adjacent;
	if (y > 0  && !(*grid[x])[y-1]->is_wall())
		adjacent.push_back((*grid[x])[y-1]);
	if (y < 13 && !(*grid[x])[y+1]->is_wall())
		adjacent.push_back((*grid[x])[y+1]);
	if (x > 0  && !(*grid[x-1])[y]->is_wall())
		adjacent.push_back((*grid[x-1])[y]);
	if (x < 19 && !(*grid[x+1])[y]->is_wall())
		adjacent.push_back((*grid[x+1])[y]);
	return adjacent;
}

vector<Cell*> shortestPath(Point start, Point end, bool print){
	int dist[20][14];
	Cell* prev[20][14];
	vector<Cell*> unvisited;
	for (int x=0; x<20; ++x){
		for (int y=0; y<14; ++y){
			unvisited.push_back((*grid[x])[y]);
			dist[x][y] = INT_MAX;
		}
	}
	dist[start.x][start.y] = 0;
	vector<Cell*> possibleBugs = bugs;
	while(find(unvisited.begin(), unvisited.end(), (*grid[end.x])[end.y]) != unvisited.end()){
		Cell* curr = NULL;
		int minDist = INT_MAX;
		int index = -1;
		for (int i=0; i<(int)unvisited.size(); ++i){
			if (dist[unvisited[i]->x][unvisited[i]->y] < minDist){
				minDist = dist[unvisited[i]->x][unvisited[i]->y];
				curr = unvisited[i];
				index = i;
			}
		}
		unvisited.erase(unvisited.begin() + index);
		vector<Cell*> neighbors = getAdjacentCells(curr->x, curr->y);
		for (int i=0; i<(int)neighbors.size(); ++i){
			/*
			if (curr->x == start.x && curr->y == start.y){
				if (find(possibleBugs.begin(), possibleBugs.end(), neighbors[i]) != possibleBugs.end()){
					cerr << "ADJACENT BUG!!!" << endl;
					continue;
				}		
			}
			*/
			int alt = dist[curr->x][curr->y] + 1;
			if (alt < dist[neighbors[i]->x][neighbors[i]->y]){
				dist[neighbors[i]->x][neighbors[i]->y] = alt;
				prev[neighbors[i]->x][neighbors[i]->y] = curr;
			}
		}
	}
	if (print){
		for (int y=0; y<14; ++y){
			for (int x=0; x<20; ++x){
				if ((*grid[x])[y]->is_wall()){
					cerr << "[][]";
					continue;
				}
				bool foundSnip = false;
				for (int i=0; i<(int)snippets.size(); ++i){
					if (snippets[i]->x == x && snippets[i]->y == y){
						cerr << " S  ";
						foundSnip = true;
						break;
					}
				}
				if(!foundSnip){
					if (x == me.x && y==me.y)
						cerr << " A  ";
					else if (x==enemy.x && y==enemy.y)
						cerr << " B  ";
					else if (dist[x][y] == INT_MAX)
						cerr << "    ";
					else if (dist[x][y] < 10)
						cerr << " 0" << dist[x][y] << " ";
					else
						cerr << " " << dist[x][y] << " ";
				}
			}
			cerr << endl;
		}
		cerr << endl;
	}
	vector<Cell*> path;
	Cell* curr = (*grid[end.x])[end.y];
	path.push_back(curr);
	while(prev[curr->x][curr->y] != (*grid[start.x])[start.y]){
		curr = prev[curr->x][curr->y];
		path.push_back(curr);
	}
	reverse(path.begin(), path.end());
	return path;
}

void process_next_command() {
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
			snippets.clear();
			weapons.clear();
			bugs.clear();
			is_wall.clear();
			for (int x = 0; x < width; x++) {
				is_wall.push_back(vector<int>(height));
			}
			string s;
			cin >> s;
			int n = s.length();
			int i = 0;
			for (int y = 0; y < height; y++) {
				for (int x = 0; x < width; x++) {
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
							is_wall[x][y] = 1;
							(*grid[x])[y]->set_wall(true);
						}
						else if (c == '.') {
							//do nothing, is_wall[x][y] == 0 by default
						}
						else if (c == 'E') {
							bugs.push_back((*grid[x])[y]);
						}
						else if (c == 'W') {
							weapons.push_back((*grid[x])[y]);
						}
						else if (c == 'C') {
							snippets.push_back((*grid[x])[y]);
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
		do_move();
		clear_grid();
		make_grid();
	}
}


int main() {
	srand((int)time(0));
	make_grid();
	//cerr.open("test123.txt");
	while (true) {
		process_next_command();
	}
	return 0;
}

//-----------------------------------------//
//  Improve the code below to win 'em all  //
//-----------------------------------------//

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,-1,0,1 };
string moves[4] = { "up", "left", "down", "right" };


void do_move() {
	cerr << "MOVE " << current_round << ":"<< endl;
	vector<string> valid_moves;
	for (int dir = 0; dir < 4; dir++) {
		int nextx = me.x + dx[dir];
		int nexty = me.y + dy[dir];
		if (nextx >= 0 && nextx < height && nexty >= 0 && nexty < width) {
			if (!is_wall[nextx][nexty]) {
				valid_moves.push_back(moves[dir]);
			}
		}
	}
	if (valid_moves.size() == 0) {
		valid_moves.push_back("pass");
	}
	if (snippets.size() == 0){
		cout << "pass" << endl;
		cerr << "No snippets on field, passing." << endl;
	}else{
		float minDist = INT_MAX;
		vector<Cell*> bestPath;
		vector<vector<Cell*>> myPaths;
		vector<vector<Cell*>> enemyPaths;
		int myBestPathIndex = -1;
		int myBestDist = INT_MAX;
		int secondBestIndex = -1;
		int secondBestDist = INT_MAX;
		int enemyBestPathIndex = -1;
		int enemyBestDist = INT_MAX;
		for (int i=0; i< (int)snippets.size(); ++i){
			cerr << "Starting path search from (" << me.x << "," << me.y << ") to (" << snippets[i]->x << "," << snippets[i]->y << ")..." << endl;
			vector<Cell*> path = shortestPath((Point)me, (Point)(*snippets[i]),true);
			vector<Cell*> enemyPath = shortestPath((Point)enemy, (Point)(*snippets[i]),false);
			myPaths.push_back(path);
			enemyPaths.push_back(enemyPath);
			if (path.size() < myBestDist){
				myBestDist = path.size();
				myBestPathIndex = i;
			}else if (path.size() < secondBestDist){
				secondBestDist = path.size();
				secondBestIndex = i;
			}
			if(enemyPath.size() < enemyBestDist){
				enemyBestDist = enemyPath.size();
				enemyBestPathIndex = i;
			}
		}
		if (myBestPathIndex == enemyBestPathIndex){
			if (myBestDist < enemyBestDist){
				bestPath = myPaths[myBestPathIndex];
				cerr << "Both players are closest to same snippet, but I am closer" << endl;
			}else{
				if (secondBestIndex != -1){
					bestPath = myPaths[secondBestIndex];
					cerr << "Both players are closest to same snippet, but enemy is closer." << endl;	
				}else{
					cerr << "Both players are closest to same snippet, enemy is closer, but I don't have a second choice."<< endl;
					bestPath = myPaths[myBestPathIndex];
				}
			}
		}else{
			cerr << "My closest snippet is uncontested." << endl;
			bestPath = myPaths[myBestPathIndex];
		}
		cerr << "Finished path search with length " << bestPath.size() << endl;
		if (bestPath.size() == 0)
			cout << "pass" << endl;
		else{
			bool adjacentBugs[4] = {false,false,false,false};
			for (int i=0; i<(int)bugs.size(); ++i){
				int adjacent = is_adjacent((Point)me, (Point)(*bugs[i]));
				if (adjacent == -1)
					continue;
				else
					adjacentBugs[adjacent] = true;			
			}
			cerr << "(" << me.x << "," << me.y << ") (" << bestPath[0]->x << "," << bestPath[0]->y << ")" << endl;
			switch(is_adjacent((Point)me, (Point)(*bestPath[0]))){
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
	}
}
