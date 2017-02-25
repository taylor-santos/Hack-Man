#include "shortestPath.h"

using namespace std;

void wall_character(Grid* grid, int x, int y) {
	char surroundings = 0;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	for (int d = 0; d < 4; ++d) {
		if (x + dx[d] < 0 || x + dx[d] > 19 ||
			y + dy[d] < 0 || y + dy[d] > 13)
			surroundings = surroundings | 1 << d;
		else
			surroundings = surroundings | ((int)grid->cells[x + dx[d]][y + dy[d]]->is_wall()) << d;
	}
	switch (surroundings) {
	case (char)0b00000000:
		cerr << " - ";
		return;
	case (char)0b00000001:
		cerr << " ' ";
		return;
	case (char)0b00000010:
		cerr << " --";
		return;
	case (char)0b00000011:
		cerr << " '-";
		return;
	case (char)0b00000100:
		cerr << " , ";
		return;
	case (char)0b00000101:
		cerr << " | ";
		return;
	case (char)0b00000110:
		cerr << " ,-";
		return;
	case (char)0b00000111:
		cerr << " |-";
		return;
	case (char)0b00001000:
		cerr << "-- ";
		return;
	case (char)0b00001001:
		cerr << "-' ";
		return;
	case (char)0b00001010:
		cerr << "---";
		return;
	case (char)0b00001011:
		cerr << "-'-";
		return;
	case (char)0b00001100:
		cerr << "-, ";
		return;
	case (char)0b00001101:
		cerr << "-| ";
		return;
	case (char)0b00001110:
		cerr << "-,-";
		return;
	case (char)0b00001111:
		cerr << "-|-";
		return;
	}
	/*
	switch (surroundings) {
	case (char)0b00000000:
		cerr << "|||";
		return;
	case (char)0b00000001:
		cerr << "|_|";
		return;
	case (char)0b00000010:
		cerr << "|--";
		return;
	case (char)0b00000011:
		cerr << "|__";
		return;
	case (char)0b00000100:
		cerr << "|^|";
		return;
	case (char)0b00000101:
		cerr << "| |";
		return;
	case (char)0b00000110:
		cerr << "|^^";
		return;
	case (char)0b00000111:
		cerr << "|  ";
		return;
	case (char)0b00001000:
		cerr << "--|";
		return;
	case (char)0b00001001:
		cerr << "__|";
		return;
	case (char)0b00001010:
		cerr << "---";
		return;
	case (char)0b00001011:
		cerr << "___";
		return;
	case (char)0b00001100:
		cerr << "^^|";
		return;
	case (char)0b00001101:
		cerr << "  |";
		return;
	case (char)0b00001110:
		cerr << "^^^";
		return;
	case (char)0b00001111:
		cerr << "   ";
		return;
	}
	*/
	/*
	switch (surroundings) {
	case (char)0b00000000:
		cerr << " - ";
		return;
	case (char)0b00000001:
		cerr << " ' ";
		return;
	case (char)0b00000010:
		cerr << " --";
		return;
	case (char)0b00000011:
		cerr << " '-";
		return;
	case (char)0b00000100:
		cerr << " , ";
		return;
	case (char)0b00000101:
		cerr << " | ";
		return;
	case (char)0b00000110:
		cerr << " ,-";
		return;
	case (char)0b00000111:
		cerr << " |-";
		return;
	case (char)0b00001000:
		cerr << "-- ";
		return;
	case (char)0b00001001:
		cerr << "-' ";
		return;
	case (char)0b00001010:
		cerr << "---";
		return;
	case (char)0b00001011:
		cerr << "-'-";
		return;
	case (char)0b00001100:
		cerr << "-, ";
		return;
	case (char)0b00001101:
		cerr << "-| ";
		return;
	case (char)0b00001110:
		cerr << "-,-";
		return;
	case (char)0b00001111:
		cerr << "-|-";
		return;
	}
	*/
	/*
	switch (surroundings) {
	case (char)0b00000000:
		cerr << " " << (unsigned char)205 << ' ';
		return;
	case (char)0b00000001:
		cerr << " " << (unsigned char)202 << ' ';
		return;
	case (char)0b00000010:
		cerr << " " << (unsigned char)205 << (unsigned char)205;
		return;
	case (char)0b00000011:
		cerr << " " << (unsigned char)200 << (unsigned char)205;
		return;
	case (char)0b00000100:
		cerr << " " << (unsigned char)203 << ' ';
		return;
	case (char)0b00000101:
		cerr << " " << (unsigned char)186 << ' ';
		return;
	case (char)0b00000110:
		cerr << " " << (unsigned char)201 << (unsigned char)205;
		return;
	case (char)0b00000111:
		cerr << " " << (unsigned char)204 << (unsigned char)205;
		return;
	case (char)0b00001000:
		cerr << (unsigned char)205 << (unsigned char)205 << ' ';
		return;
	case (char)0b00001001:
		cerr << (unsigned char)205 << (unsigned char)188 << ' ';
		return;
	case (char)0b00001010:
		cerr << (unsigned char)205 << (unsigned char)205 << (unsigned char)205;
		return;
	case (char)0b00001011:
		cerr << (unsigned char)205 << (unsigned char)202 << (unsigned char)205;
		return;
	case (char)0b00001100:
		cerr << (unsigned char)205 << (unsigned char)187 << ' ';
		return;
	case (char)0b00001101:
		cerr << (unsigned char)205 << (unsigned char)185 << ' ';
		return;
	case (char)0b00001110:
		cerr << (unsigned char)205 << (unsigned char)203 << (unsigned char)205;
		return;
	case (char)0b00001111:
		cerr << (unsigned char)205 << (unsigned char)206 << (unsigned char)205;
		return;
	}
	*/
}

vector<Point> shortestPathAroundBugsToPoint(Grid* grid, Point pt, int playerID) {
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	vector<Point> visited;
	grid_Q.push(grid->copy());
	path_Q.push(vector<Point>());
	while (grid_Q.size() > 0) {
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();

		Point currPlayerPoint = (Point)*curr_grid->players[playerID];
		Cell* currPlayerCell = curr_grid->cells[currPlayerPoint.x][currPlayerPoint.y];
		visited.push_back(currPlayerPoint);
		int currPlayerIndex = index[currPlayerPoint.x][currPlayerPoint.y];

		curr_path.push_back(currPlayerPoint);

		if (currPlayerPoint == pt){
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
				path_Q.pop();
			}
			delete curr_grid;
			return curr_path;
		}

		vector<int> killedBugs;
		bool killedByBug = false;
		for (int i = 0; i < curr_grid->bugs.size(); ++i) {
			if ((Point)*curr_grid->bugs[i] == currPlayerPoint) {
				killedBugs.push_back(i);
				if (curr_grid->players[playerID]->has_weapon) {
					curr_grid->players[playerID]->has_weapon = false;
				} else {
					killedByBug = true;
					break;
				}
			} else {
				int bugIndex = index[curr_grid->bugs[i]->x][curr_grid->bugs[i]->y];
				int bugDirection = curr_grid->bug_directions[i];
				int offset = -1;
				if (bugDirection == -1) {
					offset = paths[bugIndex][currPlayerIndex];
				} else {
					offset = paths_with_direction[bugDirection][bugIndex][currPlayerIndex];
				}
				if (offset != -1) {
					Point newPos = offsetPoint((Point)*curr_grid->bugs[i], offset);
					curr_grid->bug_directions[i] = offset;
					curr_grid->bugs[i] = curr_grid->cells[newPos.x][newPos.y];
					//Check if new bug position overlaps with a player again
					if ((Point)*curr_grid->bugs[i] == currPlayerPoint) {
						killedBugs.push_back(i);
						if (curr_grid->players[playerID]->has_weapon) {
							curr_grid->players[playerID]->has_weapon = false;
						} else {
							killedByBug = true;
							break;
						}
					}
				}
			}
		}
		for (int i = killedBugs.size() - 1; i >= 0; --i) { //Iterate from back to front because we are removing using the bugs' index.
			curr_grid->bugs.erase(curr_grid->bugs.begin() + killedBugs[i]);
			curr_grid->bug_directions.erase(curr_grid->bug_directions.begin() + killedBugs[i]);
		}
		if (killedByBug) {
			delete curr_grid;
			continue;
		}
		vector<Point> neighbors = getAdjacentCells(curr_grid, currPlayerPoint);
		for (int i = 0; i < neighbors.size(); ++i) {
			if (find(visited.begin(), visited.end(), neighbors[i]) == visited.end())
			{
				Grid* newGridCopy = curr_grid->copy();
				newGridCopy->players[playerID]->x = neighbors[i].x;
				newGridCopy->players[playerID]->y = neighbors[i].y;
				grid_Q.push(newGridCopy);
				path_Q.push(curr_path);
			}
		}
		delete curr_grid;
	}
	return vector<Point>();
}

vector<Point> shortestPathAroundBugs(Grid* grid, int playerID) {
	if (grid->snippets.size() == 0 && grid->weapons.size() == 0)
		return vector<Point>();
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	vector<Point> visited;
	grid_Q.push(grid->copy());
	path_Q.push(vector<Point>());
	while (grid_Q.size() > 0) {
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();

		Point currPlayerPoint = (Point)*curr_grid->players[playerID];
		Cell* currPlayerCell = curr_grid->cells[currPlayerPoint.x][currPlayerPoint.y];
		visited.push_back(currPlayerPoint);
		int currPlayerIndex = index[currPlayerPoint.x][currPlayerPoint.y];

		curr_path.push_back(currPlayerPoint);

		vector<Cell*>::iterator snippetIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), currPlayerCell);
		if (snippetIt != curr_grid->snippets.end()) {
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
				path_Q.pop();
			}
			delete curr_grid;
			return curr_path;
		}
		vector<Cell*>::iterator weaponIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), currPlayerCell);
		if (weaponIt != curr_grid->weapons.end()) {
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
				path_Q.pop();
			}
			delete curr_grid;
			return curr_path;
		}

		vector<int> killedBugs;
		bool killedByBug = false;
		for (int i = 0; i < curr_grid->bugs.size(); ++i) {
			if ((Point)*curr_grid->bugs[i] == currPlayerPoint) {
				killedBugs.push_back(i);
				if (curr_grid->players[playerID]->has_weapon) {
					curr_grid->players[playerID]->has_weapon = false;
				} else {
					killedByBug = true;
					break;
				}
			} else {
				int bugIndex = index[curr_grid->bugs[i]->x][curr_grid->bugs[i]->y];
				int bugDirection = curr_grid->bug_directions[i];
				int offset = -1;
				if (bugDirection == -1) {
					offset = paths[bugIndex][currPlayerIndex];
				} else {
					offset = paths_with_direction[bugDirection][bugIndex][currPlayerIndex];
				}
				if (offset != -1) {
					Point newPos = offsetPoint((Point)*curr_grid->bugs[i], offset);
					curr_grid->bug_directions[i] = offset;
					curr_grid->bugs[i] = curr_grid->cells[newPos.x][newPos.y];
					//Check if new bug position overlaps with a player again
					if ((Point)*curr_grid->bugs[i] == currPlayerPoint) {
						killedBugs.push_back(i);
						if (curr_grid->players[playerID]->has_weapon) {
							curr_grid->players[playerID]->has_weapon = false;
						} else {
							killedByBug = true;
							break;
						}
					}
				}
			}
		}
		for (int i = killedBugs.size() - 1; i >= 0; --i) { //Iterate from back to front because we are removing using the bugs' index.
			curr_grid->bugs.erase(curr_grid->bugs.begin() + killedBugs[i]);
			curr_grid->bug_directions.erase(curr_grid->bug_directions.begin() + killedBugs[i]);
		}
		if (killedByBug) {
			delete curr_grid;
			continue;
		}
		vector<Point> neighbors = getAdjacentCells(curr_grid, currPlayerPoint);
		for (int i = 0; i < neighbors.size(); ++i) {
			if (find(visited.begin(), visited.end(), neighbors[i]) == visited.end())
			{
				Grid* newGridCopy = curr_grid->copy();
				newGridCopy->players[playerID]->x = neighbors[i].x;
				newGridCopy->players[playerID]->y = neighbors[i].y;
				grid_Q.push(newGridCopy);
				path_Q.push(curr_path);
			}
		}
		delete curr_grid;
	}
	return vector<Point>();
}

vector<Point> findClosestItem(Grid* grid, int playerID) {
	if (grid->snippets.size() == 0 && grid->weapons.size() == 0)
		return vector<Point>();
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	queue<vector<Point>> bugPath_Q;
	queue<vector<Point>> enemyPath_Q;
	vector<Point> visited;
	grid_Q.push(grid->copy());
	path_Q.push(vector<Point>());
	vector<Point> bugPath = vector<Point>();
	for (int i = 0; i < grid->bugs.size(); ++i) {
		bugPath.push_back((Point)*grid->bugs[i]);
	}
	bugPath_Q.push(bugPath);
	vector<Point> enemyPath;
	enemyPath.push_back((Point)*grid->players[!playerID]);
	enemyPath_Q.push(enemyPath);
	while (grid_Q.size() > 0) {
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();
		vector<Point> curr_bugPath = bugPath_Q.front();
		bugPath_Q.pop();
		vector<Point> curr_enemyPath = enemyPath_Q.front();
		enemyPath_Q.pop();

		Point currPlayerPoint = (Point)*curr_grid->players[playerID];
		Point currEnemyPoint = (Point)*curr_grid->players[!playerID];
		int currPlayerIndex = index[currPlayerPoint.x][currPlayerPoint.y];
		int currEnemyIndex = index[currEnemyPoint.x][currEnemyPoint.y];
		visited.push_back(currPlayerPoint);
		curr_path.push_back(currPlayerPoint);
		bool foundItem = false;
		int enemyFoundSnippet = -1;
		for (int i = 0; i < curr_grid->snippets.size(); ++i) {
			if (currPlayerPoint == (Point)*curr_grid->snippets[i]) {
				foundItem = true;
			} else if (currEnemyPoint == (Point)*curr_grid->snippets[i]) {
				curr_grid->players[!playerID]->snippets++;
				enemyFoundSnippet = i;
			}
		}
		if (enemyFoundSnippet != -1) {
			curr_grid->snippets.erase(curr_grid->snippets.begin() + enemyFoundSnippet);
		}
		int enemyFoundWeapon = -1;
		if (curr_grid->players[playerID]->has_weapon == false) {
			for (int i = 0; i < curr_grid->weapons.size(); ++i) {
				if (currEnemyPoint == (Point)*curr_grid->weapons[i]) { //Evaluate enemy on weapon first, because it's not worth the risk of both players landing on it at the same time.
					curr_grid->players[!playerID]->has_weapon = true;
					enemyFoundWeapon = i;
				} else if (currPlayerPoint == (Point)*curr_grid->weapons[i]) {
					foundItem = true;
				}
			}
		}
		if (enemyFoundWeapon != -1) {
			curr_grid->weapons.erase(curr_grid->weapons.begin() + enemyFoundWeapon);
		}
		if (foundItem) {
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
				path_Q.pop();
			}
			delete curr_grid;

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
					else if (grid->players[playerID]->x == x && grid->players[playerID]->y == y)
						cerr << "AAA";
					else if (grid->players[!playerID]->x == x && grid->players[!playerID]->y == y)
						cerr << "BBB";
					else {
						int symbolCount = 0;
						string symbols;
						vector<Point>::iterator it = find(curr_path.begin(), curr_path.end(), (Point)*grid->cells[x][y]);
						if (it != curr_path.end()) {
							symbols += "a";
						}
						it = find(curr_bugPath.begin(), curr_bugPath.end(), (Point)*grid->cells[x][y]);
						if (it != curr_bugPath.end()) {
							symbols += "e";
						}
						it = find(curr_enemyPath.begin(), curr_enemyPath.end(), (Point)*grid->cells[x][y]);
						if (it != curr_enemyPath.end()) {
							symbols += "b";
						}
						if (symbols.length() == 0)
							cerr << "   ";
						else if (symbols.length() == 1)
							cerr << " " << symbols << " ";
						else if (symbols.length() == 2)
							cerr << symbols << " ";
						else
							cerr << symbols;
					}
				}
				wall_character(grid, 20, y);
				cerr << endl;
			}
			for (int x = -1; x<21; ++x)
				wall_character(grid, x, 14);
			cerr << endl;
			cerr << endl;

			return curr_path;
		}
		vector<Point> neighbors = getAdjacentCells(curr_grid, currPlayerPoint);
		int killedBug = -1;
		bool killedByBug = false;
		vector<int> neighborKilledBug = vector<int>(neighbors.size());
		for (int i = 0; i < neighbors.size(); ++i) {
			neighborKilledBug[i] = -1;
		}
		for (int i = 0; i < curr_grid->bugs.size(); ++i) {
			Point bugPos = (Point)*curr_grid->bugs[i];
			if (bugPos == currPlayerPoint) {
				if (curr_grid->players[playerID]->has_weapon) {
					killedBug = i;
					curr_grid->players[playerID]->has_weapon = false;
				} else {
					killedByBug = true;
					break;
				}
			}
			vector<Point>::iterator it = find(neighbors.begin(), neighbors.end(), bugPos);
			if (it != neighbors.end()) {
				if (curr_grid->players[playerID]->has_weapon && neighborKilledBug[it - neighbors.begin()] == -1) {
					neighborKilledBug[it - neighbors.begin()] = i;
				} else {
					neighbors.erase(it);
				}
			}
			int bugDir = curr_grid->bug_directions[i];
			int offset;
			if (bugDir == -1) {
				offset = paths[index[bugPos.x][bugPos.y]][currPlayerIndex];
			} else {
				offset = paths_with_direction[bugDir][index[bugPos.x][bugPos.y]][currPlayerIndex];
			}
			Point newPos = offsetPoint(bugPos, offset);
			curr_bugPath.push_back(newPos);
			curr_grid->bug_directions[i] = offset;
			curr_grid->bugs[i] = curr_grid->cells[newPos.x][newPos.y];
			it = find(neighbors.begin(), neighbors.end(), newPos);
			if (it != neighbors.end())
				neighbors.erase(it);
		}
		if (killedByBug) {
			delete curr_grid;
			continue;
		}
		if (killedBug != -1) {
			curr_grid->bugs.erase(curr_grid->bugs.begin() + killedBug);
			curr_grid->bug_directions.erase(curr_grid->bug_directions.begin() + killedBug);
		}
		if (curr_grid->players[!playerID]->has_weapon && !curr_grid->players[playerID]->has_weapon ||
			curr_grid->players[!playerID]->has_weapon && curr_grid->players[playerID]->snippets < 4) {
			if (currEnemyPoint == currPlayerPoint)
				return vector<Point>();
			vector<Point>::iterator it = find(neighbors.begin(), neighbors.end(), currEnemyPoint);
			if (it != neighbors.end())
				neighbors.erase(it);
			int offset = paths[currEnemyIndex][currPlayerIndex];
			Point newPos = offsetPoint(currEnemyPoint, offset);
			it = find(neighbors.begin(), neighbors.end(), newPos);
			if (it != neighbors.end())
				neighbors.erase(it);
		}

		int bestDist = INT_MAX;
		int bestOffset = -1;
		if (curr_grid->players[!playerID]->has_weapon && !curr_grid->players[playerID]->has_weapon)
		{
			if (path_lengths[currEnemyIndex][currPlayerIndex] < bestDist) {
				bestDist = path_lengths[currEnemyIndex][currPlayerIndex];
				bestOffset = paths[currEnemyIndex][currPlayerIndex];
			}
		}
		for (int i = 0; i < curr_grid->snippets.size(); ++i) {
			int snipIndex = index[curr_grid->snippets[i]->x][curr_grid->snippets[i]->y];
			if (path_lengths[currEnemyIndex][snipIndex] < bestDist) {
				bestDist = path_lengths[currEnemyIndex][snipIndex];
				bestOffset = paths[currEnemyIndex][snipIndex];
			}
		}
		for (int i = 0; i < curr_grid->weapons.size(); ++i) {
			int wepIndex = index[curr_grid->weapons[i]->x][curr_grid->weapons[i]->y];
			if (path_lengths[currEnemyIndex][wepIndex] < bestDist) {
				bestDist = path_lengths[currEnemyIndex][wepIndex];
				bestOffset = paths[currEnemyIndex][wepIndex];
			}
		}
		if (bestOffset != -1) {
			Point newEnemyPoint = offsetPoint(currEnemyPoint, bestOffset);
			curr_grid->players[!playerID]->x = newEnemyPoint.x;
			curr_grid->players[!playerID]->y = newEnemyPoint.y;
			curr_enemyPath.push_back(newEnemyPoint);
		}
		for (int i = 0; i < neighbors.size(); ++i) {
			if (find(visited.begin(), visited.end(), neighbors[i]) == visited.end())
			{
				Grid* newGridCopy = curr_grid->copy();
				if (neighborKilledBug[i] != -1) {
					newGridCopy->bugs.erase(newGridCopy->bugs.begin() + neighborKilledBug[i]);
					newGridCopy->bug_directions.erase(newGridCopy->bug_directions.begin() + neighborKilledBug[i]);
					newGridCopy->players[playerID]->has_weapon = false;
				}
				newGridCopy->players[playerID]->x = neighbors[i].x;
				newGridCopy->players[playerID]->y = neighbors[i].y;
				grid_Q.push(newGridCopy);
				path_Q.push(curr_path);
				bugPath_Q.push(curr_bugPath);
				enemyPath_Q.push(curr_enemyPath);
			}
		}
		delete curr_grid;
	}
	return vector<Point>();
}