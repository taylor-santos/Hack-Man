#include "shortestPath.h"

using namespace std;

vector<Point> bestPathToPoint(Grid** grid, Point pt, int playerID, int printIndent) {
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	vector<Point> visited;
	grid_Q.push((*grid)->copy());
	vector<Point> path;
	path.push_back((Point)(*grid)->players[playerID]);
	path_Q.push(path);

	queue<vector<Point>> enemyPath_Q;
	queue<vector<Point>> bugPath_Q;
	enemyPath_Q.push(vector<Point>());
	bugPath_Q.push(vector<Point>());

	while (grid_Q.size() > 0) {
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();

		vector<Point> curr_enemyPath = enemyPath_Q.front();
		enemyPath_Q.pop();
		vector<Point> curr_bugPath = bugPath_Q.front();
		bugPath_Q.pop();

		Point curr_playerPosition = (Point)curr_grid->players[playerID];
		Point curr_enemyPosition = (Point)curr_grid->players[!playerID];

		visited.push_back(curr_playerPosition);
		curr_enemyPath.push_back(curr_enemyPosition);

		int playerPositionIndex = index[curr_playerPosition.x][curr_playerPosition.y];
		int enemyPositionIndex = index[curr_enemyPosition.x][curr_enemyPosition.y];

		//Find Bug Collisions
		vector<int> neighborBugDirections;
		vector<int> killedBugs;
		bool playerKilledByBug = false;
		for (int bugIndex = 0; bugIndex < curr_grid->bugs.size(); ++bugIndex) {
			if (curr_grid->bugs[bugIndex] == curr_playerPosition) {
				if (curr_grid->players[playerID].has_weapon) {
					curr_grid->players[playerID].has_weapon = false;
					killedBugs.push_back(bugIndex);
					continue;
				} else {
					playerKilledByBug = true;
					break;
				}
			} else if (curr_grid->bugs[bugIndex] == curr_enemyPosition) {
				killedBugs.push_back(bugIndex);
				if (curr_grid->players[!playerID].has_weapon) {
					curr_grid->players[!playerID].has_weapon = false;
				} else {
					curr_grid->players[!playerID].snippets -= 4;
				}
				continue;
			}
		}
		if (playerKilledByBug) {
			delete curr_grid;
			continue;
		}
		for (int i = killedBugs.size() - 1; i >= 0; --i) { //Iterate from back to front because we are removing using the bugs' index.
			curr_grid->bugs.erase(curr_grid->bugs.begin() + killedBugs[i]);
			curr_grid->bug_directions.erase(curr_grid->bug_directions.begin() + killedBugs[i]);
		}

		//Find Player Collisions
		if (curr_enemyPosition == curr_playerPosition) {
			if (curr_grid->players[!playerID].has_weapon) {
				delete curr_grid;
				continue;
			} else if (curr_grid->players[playerID].has_weapon) {
				curr_grid->players[playerID].has_weapon = false;
				curr_grid->players[!playerID].snippets -= 4;
				curr_grid->players[playerID].is_paralyzed = true;
			}
		}

		//Find Item Collisions
		vector<Point>::iterator snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), curr_enemyPosition);
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->players[!playerID].snippets++;
			curr_grid->snippets.erase(snipIt);
		}
		snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), curr_playerPosition);
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->players[playerID].snippets++;
			curr_grid->snippets.erase(snipIt);
		}
		vector<Point>::iterator weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), curr_enemyPosition);
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->players[!playerID].has_weapon = true;
			curr_grid->weapons.erase(weapIt);
		}
		weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), curr_playerPosition);
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->players[playerID].has_weapon = true;
			curr_grid->weapons.erase(weapIt);
		}
		if (curr_enemyPosition == pt) {
			delete curr_grid;
			continue;
		} else if (curr_playerPosition == pt) {
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
			}
			if (printIndent != -1) {
				vector<vector<Point>> items;
				vector<char> icons;

				vector<Point> playerPos;
				playerPos.push_back((Point)(*grid)->players[playerID]);
				vector<Point> enemyPos;
				enemyPos.push_back((Point)(*grid)->players[!playerID]);
				vector<Point> snippets = (*grid)->snippets;
				vector<Point> weapons = (*grid)->weapons;

				items.push_back(playerPos);
				icons.push_back('A');
				items.push_back(enemyPos);
				icons.push_back('B');
				items.push_back(snippets);
				icons.push_back('S');
				items.push_back(weapons);
				icons.push_back('W');
				items.push_back(curr_path);
				icons.push_back('a');
				items.push_back(curr_enemyPath);
				icons.push_back('b');
				items.push_back(curr_bugPath);
				icons.push_back('e');

				printGrid((*grid), items, icons, printIndent);
			}

			delete *grid;
			(*grid) = curr_grid;
			return curr_path;
		}

		Grid* newGrid = curr_grid->copy();

		//Calculate Enemy Movement
		int enemyOffset = -1;
		if (!newGrid->players[!playerID].is_paralyzed) {
			int shortestPathLength = INT_MAX;
			for (int snipIndex = 0; snipIndex < newGrid->snippets.size(); ++snipIndex) {
				vector<Point> enemyToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->snippets[snipIndex], !playerID);
				vector<Point> playerToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->snippets[snipIndex], playerID);
				if ((playerToItem.size() == 0 && enemyToItem.size() > 1) || enemyToItem.size() > 1 && enemyToItem.size() <= playerToItem.size() && enemyToItem.size() < shortestPathLength) {
					shortestPathLength = enemyToItem.size();
					enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
				}
			}
			if (!newGrid->players[!playerID].has_weapon) {
				for (int weapIndex = 0; weapIndex < newGrid->weapons.size(); ++weapIndex) {
					vector<Point> enemyToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->weapons[weapIndex], !playerID);
					vector<Point> playerToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->weapons[weapIndex], playerID);
					if ((playerToItem.size() == 0 && enemyToItem.size() > 1) || enemyToItem.size() > 1 && enemyToItem.size() <= playerToItem.size() && enemyToItem.size() < shortestPathLength) {
						shortestPathLength = enemyToItem.size();
						enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
					}
				}
			}else{
				vector<Point> enemyToPlayer = shortestPathAroundBugsToPoint(newGrid, (Point)newGrid->players[playerID], !playerID);
				if (enemyToPlayer.size() > 1 && enemyToPlayer.size() < shortestPathLength) {
					shortestPathLength = enemyToPlayer.size();
					enemyOffset = is_adjacent(curr_enemyPosition, enemyToPlayer[1]);
				}
			}
		} else {
			newGrid->players[!playerID].is_paralyzed = false;
		}
		if (enemyOffset != -1) {
			curr_enemyPosition = offsetPoint(curr_enemyPosition, enemyOffset);
			newGrid->players[!playerID].x = curr_enemyPosition.x;
			newGrid->players[!playerID].y = curr_enemyPosition.y;
		}

		//Calculate Bug Movement
		for (int bugIndex = 0; bugIndex < newGrid->bugs.size(); ++bugIndex) {
			int bugPositionIndex = index[newGrid->bugs[bugIndex].x][newGrid->bugs[bugIndex].y];
			int bugDirection = newGrid->bug_directions[bugIndex];
			int offset = -1;
			if (bugDirection == -1) {
				offset = paths[bugPositionIndex][playerPositionIndex];
			} else {
				offset = paths_with_direction[bugDirection][bugPositionIndex][playerPositionIndex];
			}
			newGrid->bugs[bugIndex] = offsetPoint(newGrid->bugs[bugIndex], offset);
			curr_bugPath.push_back(newGrid->bugs[bugIndex]);
		}

		//Create Next Moves
		vector<Point> neighbors = getAdjacentCells(curr_grid, curr_playerPosition);
		for (int neighborIndex = 0; neighborIndex < neighbors.size(); ++neighborIndex) {
			if (find(visited.begin(), visited.end(), neighbors[neighborIndex]) == visited.end()) {
				Grid* nextGrid = newGrid->copy();
				nextGrid->round++;
				nextGrid->players[playerID].x = neighbors[neighborIndex].x;
				nextGrid->players[playerID].y = neighbors[neighborIndex].y;

				if (find(curr_grid->bugs.begin(), curr_grid->bugs.end(), neighbors[neighborIndex]) != curr_grid->bugs.end()) {
					vector<Point>::iterator bugIt = find(curr_grid->bugs.begin(), curr_grid->bugs.end(), neighbors[neighborIndex]);
					if (nextGrid->players[playerID].has_weapon) {
						nextGrid->bugs.erase(nextGrid->bugs.begin() + (bugIt - curr_grid->bugs.begin()));
						curr_grid->bugs.erase(bugIt);
						nextGrid->players[playerID].has_weapon = false;
					} else {
						delete nextGrid;
						continue;
					}
				}
				if (curr_grid->players[!playerID].has_weapon && (Point)curr_grid->players[!playerID] == neighbors[neighborIndex]) {
					delete nextGrid;
					continue;
				}

				grid_Q.push(nextGrid);
				vector<Point> newPath = curr_path;
				newPath.push_back(neighbors[neighborIndex]);
				path_Q.push(newPath);
				enemyPath_Q.push(curr_enemyPath);
				bugPath_Q.push(curr_bugPath);
			}
		}
		delete newGrid;
		delete curr_grid;
	}
	return vector<Point>();
}

vector<Point> shortestPathAroundBugsToPoint(Grid* grid, Point pt, int playerID) {
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	vector<Point> visited;
	grid_Q.push(grid->copy());
	vector<Point> path;
	path.push_back((Point)grid->players[playerID]);
	path_Q.push(path);

	queue<vector<Point>> enemyPath_Q;
	queue<vector<Point>> bugPath_Q;
	enemyPath_Q.push(vector<Point>());
	bugPath_Q.push(vector<Point>());

	while (grid_Q.size() > 0) {
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();

		vector<Point> curr_enemyPath = enemyPath_Q.front();
		enemyPath_Q.pop();
		vector<Point> curr_bugPath = bugPath_Q.front();
		bugPath_Q.pop();

		Point curr_playerPosition = (Point)curr_grid->players[playerID];
		Point curr_enemyPosition = (Point)curr_grid->players[!playerID];

		visited.push_back(curr_playerPosition);
		curr_enemyPath.push_back(curr_enemyPosition);

		int playerPositionIndex = index[curr_playerPosition.x][curr_playerPosition.y];
		int enemyPositionIndex = index[curr_enemyPosition.x][curr_enemyPosition.y];

		//Find Bug Collisions
		vector<int> neighborBugDirections;
		vector<int> killedBugs;
		bool playerKilledByBug = false;
		for (int bugIndex = 0; bugIndex < curr_grid->bugs.size(); ++bugIndex) {
			if (curr_grid->bugs[bugIndex] == curr_playerPosition) {
				if (curr_grid->players[playerID].has_weapon) {
					curr_grid->players[playerID].has_weapon = false;
					killedBugs.push_back(bugIndex);
					continue;
				} else {
					playerKilledByBug = true;
					break;
				}
			}
		}
		if (playerKilledByBug) {
			delete curr_grid;
			continue;
		}
		for (int i = killedBugs.size() - 1; i >= 0; --i) { //Iterate from back to front because we are removing using the bugs' index.
			curr_grid->bugs.erase(curr_grid->bugs.begin() + killedBugs[i]);
			curr_grid->bug_directions.erase(curr_grid->bug_directions.begin() + killedBugs[i]);
		}

		//Find Item Collisions
		vector<Point>::iterator snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), curr_playerPosition);
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->players[playerID].snippets++;
			curr_grid->snippets.erase(snipIt);
		}
		vector<Point>::iterator weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), curr_playerPosition);
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->players[playerID].has_weapon = true;
			curr_grid->weapons.erase(weapIt);
		}
		if (curr_enemyPosition == pt) {
			delete curr_grid;
			continue;
		} else if (curr_playerPosition == pt) {
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
			}
			delete curr_grid;
			return curr_path;
		}

		Grid* newGrid = curr_grid->copy();

		//Calculate Bug Movement
		for (int bugIndex = 0; bugIndex < newGrid->bugs.size(); ++bugIndex) {
			int bugPositionIndex = index[newGrid->bugs[bugIndex].x][newGrid->bugs[bugIndex].y];
			int bugDirection = newGrid->bug_directions[bugIndex];
			int offset = -1;
			if (bugDirection == -1) {
				offset = paths[bugPositionIndex][playerPositionIndex];
			} else {
				offset = paths_with_direction[bugDirection][bugPositionIndex][playerPositionIndex];
			}
			newGrid->bugs[bugIndex] = offsetPoint(newGrid->bugs[bugIndex], offset);
			curr_bugPath.push_back(newGrid->bugs[bugIndex]);
		}

		//Create Next Moves
		vector<Point> neighbors = getAdjacentCells(curr_grid, curr_playerPosition);
		for (int neighborIndex = 0; neighborIndex < neighbors.size(); ++neighborIndex) {
			if (find(visited.begin(), visited.end(), neighbors[neighborIndex]) == visited.end()) {
				Grid* nextGrid = newGrid->copy();
				nextGrid->round++;
				nextGrid->players[playerID].x = neighbors[neighborIndex].x;
				nextGrid->players[playerID].y = neighbors[neighborIndex].y;

				if (find(curr_grid->bugs.begin(), curr_grid->bugs.end(), neighbors[neighborIndex]) != curr_grid->bugs.end()) {
					vector<Point>::iterator bugIt = find(curr_grid->bugs.begin(), curr_grid->bugs.end(), neighbors[neighborIndex]);
					if (nextGrid->players[playerID].has_weapon) {
						nextGrid->bugs.erase(nextGrid->bugs.begin() + (bugIt - curr_grid->bugs.begin()));
						curr_grid->bugs.erase(bugIt);
						nextGrid->players[playerID].has_weapon = false;
					} else {
						delete nextGrid;
						continue;
					}
				}

				grid_Q.push(nextGrid);
				vector<Point> newPath = curr_path;
				newPath.push_back(neighbors[neighborIndex]);
				path_Q.push(newPath);
				enemyPath_Q.push(curr_enemyPath);
				bugPath_Q.push(curr_bugPath);
			}
		}
		delete newGrid;
		delete curr_grid;
	}
	return vector<Point>();
}


void wall_character(Grid* grid, int x, int y) {
	char surroundings = 0;
	int dx[4] = { 0,1,0,-1 };
	int dy[4] = { -1,0,1,0 };
	for (int d = 0; d < 4; ++d) {
		if (x + dx[d] < 0 || x + dx[d] > 19 ||
			y + dy[d] < 0 || y + dy[d] > 13)
			surroundings = surroundings | 1 << d;
		else
			surroundings = surroundings | (walls[x + dx[d]][y + dy[d]]) << d;
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

void printGrid(Grid* grid, vector<vector<Point>> items, vector<char> icons, int indent) {
	for (int i = 0; i < indent; ++i)
		cerr << "   ";
	cerr << grid->round << endl;
	for (int i = 0; i < indent; ++i)
		cerr << "   ";
	for (int x = -1; x<21; ++x)
		wall_character(grid, x, -1);
	cerr << endl;
	for (int i = 0; i < indent; ++i)
		cerr << "   ";
	for (int y = 0; y < 14; ++y) {
		wall_character(grid, -1, y);
		for (int x = 0; x < 20; ++x) {
			vector<Point>::iterator it = find(grid->bugs.begin(), grid->bugs.end(), Point(x, y));
			if (it != grid->bugs.end()) {
				if (walls[x][y])
					cerr << "-";
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
					if (walls[x][y])
						cerr << "E-";
					else
						cerr << "E ";
					break;
				}
			} else if (walls[x][y])
				wall_character(grid, x, y);
			else {
				int iconCount = 0;
				for (int i = 0; i < items.size() && iconCount < 3; ++i) {
					if (find(items[i].begin(), items[i].end(), Point(x, y)) != items[i].end()) {
						cerr << icons[i];
						iconCount++;
					}
				}
				for (int i = 0; i < 3 - iconCount; ++i)
					cerr << " ";
			}
		}
		wall_character(grid, 20, y);
		cerr << endl;
		for (int i = 0; i < indent; ++i)
			cerr << "   ";
	}
	for (int x = -1; x<21; ++x)
		wall_character(grid, x, 14);
	cerr << endl;
}