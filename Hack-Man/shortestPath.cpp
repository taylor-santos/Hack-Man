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

vector<Point> bestPath(Grid** grid, int playerID, int depth) {
	vector<Point> targetPoints;
	for (int snipIndex = 0; snipIndex < (*grid)->snippets.size(); ++snipIndex)
		targetPoints.push_back((*grid)->snippets[snipIndex]);
	if (!(*grid)->players[playerID]->has_weapon || !(*grid)->players[!playerID]->has_weapon) {
		//Player should go for a weapon if either player doesn't have one. 
		for (int weapIndex = 0; weapIndex < (*grid)->weapons.size(); ++weapIndex)
			targetPoints.push_back((*grid)->weapons[weapIndex]);
	}
	if (targetPoints.size() == 0)
		return vector<Point>();
	vector<Grid*> resultGrids;
	vector<vector<Point>> resultPaths;
	vector<vector<Point>> resultEnemyPaths;
	vector<int> resultFirstPathLength;
	vector<int> resultCloserPointCount;
	queue<Grid*> continueGrids;
	queue<vector<Point>> continuePaths;
	bool singleDirection = true;
	int direction = -1;
	for (int targetIndex = 0; targetIndex < targetPoints.size(); ++targetIndex) {
		Grid* newGrid = (*grid)->copy();
		Point target = targetPoints[targetIndex];
		vector<Point> pathToTarget = bestPathToPoint(&newGrid, target, playerID, depth);
		continueGrids.push(newGrid);
		continuePaths.push(pathToTarget);
		if (pathToTarget.size() > 1) {
			int offset = is_adjacent((Point)*(*grid)->players[playerID], pathToTarget[1]);
			if (direction == -1)
				direction = offset;
			else if (direction != offset)
				singleDirection = false;
		}
		/*
		if (pathToTarget.size() == 0)
			continue;
		vector<Point> nextPath = bestPath(&newGrid, playerID);
		pathToTarget.insert(pathToTarget.end(), nextPath.begin(), nextPath.end());
		resultGrids.push_back(newGrid);
		resultPaths.push_back(pathToTarget);
		*/
	}
	if (singleDirection) {
		delete (*grid);
		(*grid) = continueGrids.front();
		return continuePaths.front();
	}
	while (continueGrids.size() > 0) {
		vector<Point> curr_path = continuePaths.front();
		continuePaths.pop();
		Grid* curr_grid = continueGrids.front();
		continueGrids.pop();
		if (curr_path.size() == 0)
			continue;
		resultCloserPointCount.push_back(numberOfCloserPoints[index[curr_grid->players[!playerID]->x][curr_grid->players[!playerID]->y]][index[curr_grid->players[playerID]->x][curr_grid->players[playerID]->y]]);
		vector<Point> nextPath = bestPath(&curr_grid, playerID, depth+1);
		resultFirstPathLength.push_back(curr_path.size());
		curr_path.insert(curr_path.end(), nextPath.begin(), nextPath.end());
		resultGrids.push_back(curr_grid);
		resultPaths.push_back(curr_path);

	}
	int bestSnipCount = 0;
	int bestIndex = -1;
	for (int i = 0; i < resultGrids.size(); ++i) {
		if (resultGrids[i]->players[playerID]->snippets > bestSnipCount) {
			bestSnipCount = resultGrids[i]->players[playerID]->snippets;
			bestIndex = i;
		}
		if (resultGrids[i]->players[playerID]->snippets == bestSnipCount) {
			if (resultFirstPathLength[i] < resultFirstPathLength[i]) {
				bestSnipCount = resultGrids[i]->players[playerID]->snippets;
				bestIndex = i;
			}
		}
	}
	if (bestIndex != -1) {
		delete (*grid);
		(*grid) = resultGrids[bestIndex];
		return resultPaths[bestIndex];
	} else
		return vector<Point>();
}

vector<Point> bestPathToPoint(Grid** grid, Point pt, int playerID, int printIndent) {
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	vector<Point> visited;
	grid_Q.push((*grid)->copy());
	vector<Point> path;
	path.push_back((Point)*(*grid)->players[playerID]);
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

		Point curr_playerPosition = (Point)*curr_grid->players[playerID];
		Point curr_enemyPosition = (Point)*curr_grid->players[!playerID];

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
				if (curr_grid->players[playerID]->has_weapon) {
					curr_grid->players[playerID]->has_weapon = false;
					killedBugs.push_back(bugIndex);
					continue;
				} else {
					playerKilledByBug = true;
					break;
				}
			} else if (curr_grid->bugs[bugIndex] == curr_enemyPosition) {
				killedBugs.push_back(bugIndex);
				if (curr_grid->players[!playerID]->has_weapon) {
					curr_grid->players[!playerID]->has_weapon = false;
				} else {
					curr_grid->players[!playerID]->snippets -= 4;
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
			if (curr_grid->players[!playerID]->has_weapon) {
				delete curr_grid;
				continue;
			} else if (curr_grid->players[playerID]->has_weapon) {
				curr_grid->players[playerID]->has_weapon = false;
				curr_grid->players[!playerID]->snippets -= 4;
				curr_grid->players[playerID]->is_paralyzed = true;
			}
		}

		//Find Item Collisions
		vector<Point>::iterator snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), curr_enemyPosition);
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->players[!playerID]->snippets++;
			curr_grid->snippets.erase(snipIt);
		}
		snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), curr_playerPosition);
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->players[playerID]->snippets++;
			curr_grid->snippets.erase(snipIt);
		}
		vector<Point>::iterator weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), curr_enemyPosition);
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->players[!playerID]->has_weapon = true;
			curr_grid->weapons.erase(weapIt);
		}
		weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), curr_playerPosition);
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->players[playerID]->has_weapon = true;
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

			vector<vector<Point>> items;
			vector<char> icons;

			vector<Point> playerPos;
			playerPos.push_back((Point)*(*grid)->players[playerID]);
			vector<Point> enemyPos;
			enemyPos.push_back((Point)*(*grid)->players[!playerID]);
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

			delete *grid;
			(*grid) = curr_grid;
			return curr_path;
		}

		Grid* newGrid = curr_grid->copy();

		//Calculate Enemy Movement
		int enemyOffset = -1;
		if (!newGrid->players[!playerID]->is_paralyzed) {
			int shortestPathLength = INT_MAX;
			for (int snipIndex = 0; snipIndex < newGrid->snippets.size(); ++snipIndex) {
				vector<Point> enemyToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->snippets[snipIndex], !playerID);
				vector<Point> playerToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->snippets[snipIndex], playerID);
				if ((playerToItem.size() == 0 && enemyToItem.size() > 1) || enemyToItem.size() > 1 && enemyToItem.size() <= playerToItem.size() && enemyToItem.size() < shortestPathLength) {
					shortestPathLength = enemyToItem.size();
					enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
				}
			}
			for (int weapIndex = 0; weapIndex < newGrid->weapons.size(); ++weapIndex) {
				vector<Point> enemyToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->weapons[weapIndex], !playerID);
				vector<Point> playerToItem = shortestPathAroundBugsToPoint(newGrid, newGrid->weapons[weapIndex], playerID);
				if ((playerToItem.size() == 0 && enemyToItem.size() > 1) || enemyToItem.size() > 1 && enemyToItem.size() <= playerToItem.size() && enemyToItem.size() < shortestPathLength) {
					shortestPathLength = enemyToItem.size();
					enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
				}
			}
		} else {
			newGrid->players[!playerID]->is_paralyzed = false;
		}
		if (enemyOffset != -1) {
			curr_enemyPosition = offsetPoint(curr_enemyPosition, enemyOffset);
			newGrid->players[!playerID]->x = curr_enemyPosition.x;
			newGrid->players[!playerID]->y = curr_enemyPosition.y;
		}

		//Calculate Bug Movement
		for (int bugIndex = 0; bugIndex < newGrid->bugs.size(); ++bugIndex) {
			int bugPositionIndex = index[newGrid->bugs[bugIndex].x][newGrid->bugs[bugIndex].y];
			int bugDirection = newGrid->bug_directions[bugIndex];
			int offset = -1;
			if (bugDirection == -1) {
				if (path_lengths[bugPositionIndex][playerPositionIndex] <= path_lengths[bugPositionIndex][enemyPositionIndex])
					offset = paths[bugPositionIndex][playerPositionIndex];
				else
					offset = paths[bugPositionIndex][enemyPositionIndex];
			} else {
				if (path_lengths_with_direction[bugDirection][bugPositionIndex][playerPositionIndex] <= path_lengths_with_direction[bugDirection][bugPositionIndex][enemyPositionIndex])
					offset = paths_with_direction[bugDirection][bugPositionIndex][playerPositionIndex];
				else
					offset = paths_with_direction[bugDirection][bugPositionIndex][enemyPositionIndex];
			}
			newGrid->bugs[bugIndex] = offsetPoint(newGrid->bugs[bugIndex], offset);
			curr_bugPath.push_back(newGrid->bugs[bugIndex]);
		}

		//Create Next Moves
		vector<Point> neighbors = getAdjacentCells(curr_grid, curr_playerPosition);
		for (int neighborIndex = 0; neighborIndex < neighbors.size(); ++neighborIndex) {
			if (find(visited.begin(), visited.end(), neighbors[neighborIndex]) == visited.end()){
				Grid* nextGrid = newGrid->copy();
				nextGrid->round++;
				nextGrid->players[playerID]->x = neighbors[neighborIndex].x;
				nextGrid->players[playerID]->y = neighbors[neighborIndex].y;

				if (find(curr_grid->bugs.begin(), curr_grid->bugs.end(), neighbors[neighborIndex]) != curr_grid->bugs.end()) {
					vector<Point>::iterator bugIt = find(curr_grid->bugs.begin(), curr_grid->bugs.end(), neighbors[neighborIndex]);
					if (nextGrid->players[playerID]->has_weapon) {
						nextGrid->bugs.erase(nextGrid->bugs.begin() + (bugIt - curr_grid->bugs.begin()));
						curr_grid->bugs.erase(bugIt);
						nextGrid->players[playerID]->has_weapon = false;
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
		delete curr_grid;

		//Find Point Collisions

		/*
		//Find Bug Collisions
		vector<int> neighborBugDirections;
		vector<int> killedBugs;
		bool playerKilledByBug = false;
		for (int bugIndex = 0; bugIndex < curr_grid->bugs.size(); ++bugIndex) {
			if (curr_grid->bugs[bugIndex] == curr_playerPosition) {
				if (curr_grid->players[playerID]->has_weapon) {
					curr_grid->players[playerID]->has_weapon = false;
					killedBugs.push_back(bugIndex);
					continue;
				} else {
					playerKilledByBug = true;
					break;
				}
			}else if (curr_grid->bugs[bugIndex] == curr_enemyPosition) {
				killedBugs.push_back(bugIndex);
				if (curr_grid->players[!playerID]->has_weapon) {
					curr_grid->players[!playerID]->has_weapon = false;
				} else {
					curr_grid->players[!playerID]->snippets -= 4;
				}
				continue;
			}
			int bugPositionIndex = index[curr_grid->bugs[bugIndex].x][curr_grid->bugs[bugIndex].y];
			int bugDirection = curr_grid->bug_directions[bugIndex];
			int offset = -1;
			if (bugDirection == -1) {
				if (path_lengths[bugPositionIndex][playerPositionIndex] <= path_lengths[bugPositionIndex][enemyPositionIndex])
					offset = paths[bugPositionIndex][playerPositionIndex];
				else
					offset = paths[bugPositionIndex][enemyPositionIndex];
			} else {
				if (path_lengths_with_direction[bugDirection][bugPositionIndex][playerPositionIndex] <= path_lengths_with_direction[bugDirection][bugPositionIndex][enemyPositionIndex])
					offset = paths_with_direction[bugDirection][bugPositionIndex][playerPositionIndex];
				else
					offset = paths_with_direction[bugDirection][bugPositionIndex][enemyPositionIndex];
			}
			assert(offset != -1);
			curr_grid->bugs[bugIndex] = offsetPoint(curr_grid->bugs[bugIndex], offset);
			curr_bugPath.push_back(curr_grid->bugs[bugIndex]);
			if (curr_grid->bugs[bugIndex] == curr_playerPosition) {
				neighborBugDirections.push_back(offset);
			} else if (curr_grid->bugs[bugIndex] == curr_enemyPosition) {
				//FIXME: Wrong way to deal with adjacent bugs
				killedBugs.push_back(bugIndex);
				if (curr_grid->players[!playerID]->has_weapon) {
					curr_grid->players[!playerID]->has_weapon = false;
				} else {
					curr_grid->players[!playerID]->snippets -= 4;
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
		vector<Point>::iterator snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), curr_enemyPosition);
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->players[!playerID]->snippets++;
			curr_grid->snippets.erase(snipIt);
		}
		snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), curr_playerPosition);
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->players[playerID]->snippets++;
			curr_grid->snippets.erase(snipIt);
		}
		vector<Point>::iterator weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), curr_enemyPosition);
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->players[!playerID]->has_weapon = true;
			curr_grid->weapons.erase(weapIt);
		}
		weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), curr_playerPosition);
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->players[playerID]->has_weapon = true;
			curr_grid->weapons.erase(weapIt);
		}
	
		if (curr_enemyPosition == curr_playerPosition) {
			if (curr_grid->players[!playerID]->has_weapon) {
				delete curr_grid;
				continue;
			} else if (curr_grid->players[playerID]->has_weapon) {
				curr_grid->players[playerID]->has_weapon = false;
				curr_grid->players[!playerID]->snippets -= 4;
				curr_grid->players[playerID]->is_paralyzed = true;
			}
		}
		if (curr_enemyPosition == pt) {
			delete curr_grid;
			continue;
		}
		
		int enemyOffset = -1;
		if (!curr_grid->players[!playerID]->is_paralyzed) {
			//MOVE ENEMY
			int shortestPathLength = INT_MAX;
			for (int snipIndex = 0; snipIndex < curr_grid->snippets.size(); ++snipIndex) {
				vector<Point> enemyToItem = shortestPathAroundBugsToPoint(curr_grid, curr_grid->snippets[snipIndex], !playerID);
				vector<Point> playerToItem = shortestPathAroundBugsToPoint(curr_grid, curr_grid->snippets[snipIndex], playerID);
				if ((playerToItem.size() == 0 && enemyToItem.size() > 1) || enemyToItem.size() > 1 && enemyToItem.size() <= playerToItem.size() && enemyToItem.size() < shortestPathLength) {
					shortestPathLength = enemyToItem.size();
					enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
				}
				//if (enemyToItem.size() > 1 && enemyToItem.size() < shortestPathLength) {
				//	shortestPathLength = enemyToItem.size();
				//	enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
				//}
			}
			for (int weapIndex = 0; weapIndex < curr_grid->weapons.size(); ++weapIndex) {
				vector<Point> enemyToItem = shortestPathAroundBugsToPoint(curr_grid, curr_grid->weapons[weapIndex], !playerID);
				vector<Point> playerToItem = shortestPathAroundBugsToPoint(curr_grid, curr_grid->weapons[weapIndex], playerID);
				if ((playerToItem.size() == 0 && enemyToItem.size() > 1) || enemyToItem.size() > 1 && enemyToItem.size() <= playerToItem.size() && enemyToItem.size() < shortestPathLength) {
				shortestPathLength = enemyToItem.size();
					enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
				}
				//if (enemyToItem.size() > 1 && enemyToItem.size() < shortestPathLength) {
				//	shortestPathLength = enemyToItem.size();
				//	enemyOffset = is_adjacent(curr_enemyPosition, enemyToItem[1]);
				//}
			}
		} else {
			curr_grid->players[!playerID]->is_paralyzed = false;
		}

		if (enemyOffset != -1) {
			curr_enemyPosition = offsetPoint(curr_enemyPosition, enemyOffset);
			curr_grid->players[!playerID]->x = curr_enemyPosition.x;
			curr_grid->players[!playerID]->y = curr_enemyPosition.y;
		}

		if (curr_enemyPosition == curr_playerPosition) {
			if (curr_grid->players[!playerID]->has_weapon) {
				neighborBugDirections.push_back(enemyOffset);
			}
		}
		if (curr_enemyPosition == pt) {
			delete curr_grid;
			continue;
		} else if (curr_playerPosition == pt) {
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
			}

			vector<vector<Point>> items;
			vector<char> icons;

			vector<Point> playerPos;
			playerPos.push_back((Point)*(*grid)->players[playerID]);
			vector<Point> enemyPos;
			enemyPos.push_back((Point)*(*grid)->players[!playerID]);
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

			delete *grid;
			(*grid) = curr_grid;
			return curr_path;
		}
		
		vector<Point> neighbors = getAdjacentCells(curr_grid, curr_playerPosition);
		for (int neighborIndex = 0; neighborIndex < neighbors.size(); ++neighborIndex) {
			int neighborOffset = is_adjacent(neighbors[neighborIndex], curr_playerPosition);
			if (find(visited.begin(), visited.end(), neighbors[neighborIndex]) == visited.end() && 
				find(neighborBugDirections.begin(), neighborBugDirections.end(), neighborOffset) == neighborBugDirections.end()) {
				Grid* newGrid = curr_grid->copy();
				newGrid->players[playerID]->x = neighbors[neighborIndex].x;
				newGrid->players[playerID]->y = neighbors[neighborIndex].y;
				grid_Q.push(newGrid);
				vector<Point> newPath = curr_path;
				newPath.push_back(neighbors[neighborIndex]);
				path_Q.push(newPath);
				enemyPath_Q.push(curr_enemyPath);
				bugPath_Q.push(curr_bugPath);
			}
		}
		delete curr_grid;
		*/
	}
	return vector<Point>();
}

vector<Point> shortestPathToPoint(Grid** grid, Point pt, int playerID) {
	//Given a target point, finds the best series of moves to arrive at that point.
	//Will not consider paths in which opponent arrives at the point first.
	//The passed grid will be transformed to represent the state of the grid upon arrival.
	//Returns a length-2 vector of vectors of points, representing the paths of the player and the predicted path of the opponent.
	assert((*grid)->width() > pt.x && pt.x >= 0 && (*grid)->height() > pt.y && pt.y >= 0);
	assert(walls[pt.x][pt.y] == false);
	queue<Grid*> grid_Q;
	queue<vector<Point>> path_Q;
	queue<vector<Point>> enemy_path_Q;
	queue<vector<Point>> bug_path_Q;
	grid_Q.push((*grid)->copy());
	vector<Point> path;
	path.push_back((Point)*(*grid)->players[playerID]);
	path_Q.push(path);
	vector<Point> enemy_path;
	enemy_path.push_back((Point)*(*grid)->players[!playerID]);
	enemy_path_Q.push(enemy_path);
	bug_path_Q.push(vector<Point>());

	while (grid_Q.size() > 0) {
		Grid* curr_grid = grid_Q.front();
		grid_Q.pop();
		vector<Point> curr_path = path_Q.front();
		path_Q.pop();
		vector<Point> enemy_path = enemy_path_Q.front();
		enemy_path_Q.pop();
		vector<Point> bug_path = bug_path_Q.front();
		bug_path_Q.pop();
		Player* curr_player = curr_grid->players[playerID];
		Player* curr_enemy = curr_grid->players[!playerID];

		int curr_player_index = index[curr_player->x][curr_player->y];
		
		if ((Point)*curr_player == (Point)*curr_enemy) {
			if (curr_enemy->has_weapon) {
				delete curr_grid;
				continue;
			} else if (curr_player->has_weapon) {
				curr_player->has_weapon = false;
				curr_enemy->snippets -= 4;
				curr_enemy->is_paralyzed = true;
			}
		}
		if (!curr_enemy->is_paralyzed) {
			vector<Point> enemyPath = shortestPathAroundBugs(curr_grid, !playerID);
			if (enemyPath.size() > 1) {
				curr_enemy->x = enemyPath[1].x;
				curr_enemy->y = enemyPath[1].y;
			}
			if ((Point)*curr_player == (Point)*curr_enemy) {
				if (curr_enemy->has_weapon) {
					delete curr_grid;
					continue;
				} else if (curr_player->has_weapon) {
					curr_player->has_weapon = false;
					curr_enemy->snippets -= 4;
					curr_enemy->is_paralyzed = true;
				}
			}
		} else {
			curr_enemy->is_paralyzed = false;
		}

		vector<Point>::iterator snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), Point(curr_enemy->x,curr_enemy->y));
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->snippets.erase(snipIt);
			curr_enemy->snippets++;
		}
		snipIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), Point(curr_player->x,curr_player->y));
		if (snipIt != curr_grid->snippets.end()) {
			curr_grid->snippets.erase(snipIt);
			curr_player->snippets++;
		}

		vector<Point>::iterator weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), Point(curr_enemy->x,curr_enemy->y));
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->weapons.erase(weapIt);
			curr_enemy->has_weapon = true;
		}
		weapIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), Point(curr_player->x,curr_player->y));
		if (weapIt != curr_grid->weapons.end()) {
			curr_grid->weapons.erase(weapIt);
			curr_player->has_weapon = true;
		}

		if ((Point)*curr_enemy == pt) {
			delete curr_grid;
			continue;
		}

		if ((Point)*curr_player == pt) {
			for (int x = -1; x<21; ++x)
				wall_character((*grid), x, -1);
			cerr << endl;
			for (int y = 0; y < 14; ++y) {
				wall_character((*grid), -1, y);
				for (int x = 0; x < 20; ++x) {
					vector<Point>::iterator it = find((*grid)->bugs.begin(), (*grid)->bugs.end(), Point(x,y));
					if (it != (*grid)->bugs.end()) {
						if (walls[x][y])
							cerr << " ";
						else
							cerr << " ";
						switch ((*grid)->bug_directions[it - (*grid)->bugs.begin()]) {
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
								cerr << "E ";
							else
								cerr << "E ";
							break;
						}
					} else if (walls[x][y])
						wall_character((*grid), x, y);
					else if (find((*grid)->snippets.begin(), (*grid)->snippets.end(), Point(x,y)) != (*grid)->snippets.end()) {
						if (x == pt.x && y == pt.y)
							cerr << "[S]";
						else
							cerr << " S ";
					} else if (find((*grid)->weapons.begin(), (*grid)->weapons.end(), Point(x,y)) != (*grid)->weapons.end()) {
						if (x == pt.x && y == pt.y)
							cerr << "[W]";
						else
							cerr << " W ";
					} else if ((*grid)->players[playerID]->x == x && (*grid)->players[playerID]->y == y) {
						if (x == pt.x && y == pt.y)
							cerr << "[A]";
						else
							cerr << " A ";
					} else if ((*grid)->players[!playerID]->x == x && (*grid)->players[!playerID]->y == y) {
						if (x == pt.x && y == pt.y)
							cerr << "[B]";
						else
							cerr << " B ";
					} else {
						string cell;
						if (find(curr_path.begin(), curr_path.end(), Point(x,y)) != curr_path.end())
							cell += "a";
						if (find(bug_path.begin(), bug_path.end(), Point(x,y)) != bug_path.end())
							cell += "e";
						if (find(enemy_path.begin(), enemy_path.end(), Point(x,y)) != enemy_path.end())
							cell += "b";
						if (cell.size() == 0) {
							if (x == pt.x && y == pt.y)
								cerr << "[ ]";
							else
								cerr << "   ";
						}else if (cell.size() == 1) {
							if (x == pt.x && y == pt.y)
								cerr << "[" << cell << "]";
							else
								cerr << " " << cell << " ";
						} else if (cell.size() == 2) {
							if (x == pt.x && y == pt.y)
								cerr << "[" << cell;
							else
								cerr << " " << cell;
						}
						else if (cell.size() == 3) {
								cerr << cell;
						}
					}
				}
				wall_character((*grid), 20, y);
				cerr << endl;
			}
			for (int x = -1; x<21; ++x)
				wall_character((*grid), x, 14);
			cerr << endl;

			delete (*grid);
			*grid = curr_grid;
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
			}
			return curr_path;
		}

		vector<int> killedBugs;
		bool killedByBug = false;
		for (int i = 0; i < curr_grid->bugs.size(); ++i) {
			if (curr_grid->bugs[i] == (Point)*curr_player) {
				killedBugs.push_back(i);
				if (curr_grid->players[playerID]->has_weapon) {
					curr_grid->players[playerID]->has_weapon = false;
				} else {
					killedByBug = true;
					break;
				}
			} else if (curr_grid->bugs[i] == (Point)*curr_enemy) {
				killedBugs.push_back(i);
				if (curr_grid->players[!playerID]->has_weapon) {
					curr_grid->players[!playerID]->has_weapon = false;
				} else {
					curr_grid->players[!playerID]->snippets -= 4;
				}
			} else {
				int bugIndex = index[curr_grid->bugs[i].x][curr_grid->bugs[i].y];
				int bugDirection = curr_grid->bug_directions[i];
				int offset = -1;
				if (bugDirection == -1) {
					offset = paths[bugIndex][curr_player_index];
				} else {
					offset = paths_with_direction[bugDirection][bugIndex][curr_player_index];
				}
				if (offset != -1) {
					Point newPos = offsetPoint(curr_grid->bugs[i], offset);
					curr_grid->bug_directions[i] = offset;
					curr_grid->bugs[i] = newPos;
					bug_path.push_back(curr_grid->bugs[i]);
					//Check if new bug position overlaps with a player again
					if (curr_grid->bugs[i] == (Point)*curr_player) {
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
		
		vector<Point> neighbors = getAdjacentCells(curr_grid, (Point)*curr_player);
		for (int i = 0; i < neighbors.size(); ++i) {
			if (curr_path.size() < 2 || neighbors[i] != curr_path[curr_path.size() - 2]) { //Prevent player from doubling back on itself.
			                                                       //While this is a legal move, it adds too much complexity for little gain.
				Grid* new_grid = curr_grid->copy();
				new_grid->round++;
				new_grid->players[playerID]->x = neighbors[i].x;
				new_grid->players[playerID]->y = neighbors[i].y;
				vector<Point> new_path = curr_path;
				vector<Point> new_enemy_path = enemy_path;
				new_path.push_back((Point)*new_grid->players[playerID]);
				new_enemy_path.push_back((Point)*new_grid->players[!playerID]);
				grid_Q.push(new_grid);
				path_Q.push(new_path);
				enemy_path_Q.push(new_enemy_path);
				bug_path_Q.push(bug_path);
			}
		}
		delete curr_grid;
	}
	return vector<Point>(); //No path to point found. Returning unchanged grid with 0 moves.
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
		visited.push_back(currPlayerPoint);
		int currPlayerIndex = index[currPlayerPoint.x][currPlayerPoint.y];

		curr_path.push_back(currPlayerPoint);

		if (currPlayerPoint == pt){
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
			}
			delete curr_grid;
			return curr_path;
		}

		vector<int> killedBugs;
		vector<int> adjacentBugs;
		bool killedByBug = false;
		for (int i = 0; i < curr_grid->bugs.size(); ++i) {
			if (curr_grid->bugs[i] == currPlayerPoint) {
				killedBugs.push_back(i);
				if (curr_grid->players[playerID]->has_weapon) {
					curr_grid->players[playerID]->has_weapon = false;
				} else {
					killedByBug = true;
					break;
				}
			} else {
				int bugIndex = index[curr_grid->bugs[i].x][curr_grid->bugs[i].y];
				int bugDirection = curr_grid->bug_directions[i];
				int offset = -1;
				if (bugDirection == -1) {
					offset = paths[bugIndex][currPlayerIndex];
				} else {
					offset = paths_with_direction[bugDirection][bugIndex][currPlayerIndex];
				}
				if (offset != -1) {
					Point newPos = offsetPoint(curr_grid->bugs[i], offset);
					curr_grid->bug_directions[i] = offset;
					curr_grid->bugs[i] = Point(newPos.x, newPos.y);
					//Check if new bug position overlaps with a player again
					if (curr_grid->bugs[i] == currPlayerPoint) {
						adjacentBugs.push_back(offset);
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
			int neighborOffset = is_adjacent(neighbors[i], currPlayerPoint);
			if (find(visited.begin(), visited.end(), neighbors[i]) == visited.end() &&
				find(adjacentBugs.begin(), adjacentBugs.end(), neighborOffset) == adjacentBugs.end()) 
			{
					Grid* newGridCopy = curr_grid->copy();
					newGridCopy->round++;
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
		visited.push_back(currPlayerPoint);
		int currPlayerIndex = index[currPlayerPoint.x][currPlayerPoint.y];

		curr_path.push_back(currPlayerPoint);

		vector<Point>::iterator snippetIt = find(curr_grid->snippets.begin(), curr_grid->snippets.end(), currPlayerPoint);
		if (snippetIt != curr_grid->snippets.end()) {
			while (grid_Q.size() > 0) {
				delete grid_Q.front();
				grid_Q.pop();
				path_Q.pop();
			}
			delete curr_grid;
			return curr_path;
		}
		vector<Point>::iterator weaponIt = find(curr_grid->weapons.begin(), curr_grid->weapons.end(), currPlayerPoint);
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
			if (curr_grid->bugs[i] == currPlayerPoint) {
				killedBugs.push_back(i);
				if (curr_grid->players[playerID]->has_weapon) {
					curr_grid->players[playerID]->has_weapon = false;
				} else {
					killedByBug = true;
					break;
				}
			} else {
				int bugIndex = index[curr_grid->bugs[i].x][curr_grid->bugs[i].y];
				int bugDirection = curr_grid->bug_directions[i];
				int offset = -1;
				if (bugDirection == -1) {
					offset = paths[bugIndex][currPlayerIndex];
				} else {
					offset = paths_with_direction[bugDirection][bugIndex][currPlayerIndex];
				}
				if (offset != -1) {
					Point newPos = offsetPoint(curr_grid->bugs[i], offset);
					curr_grid->bug_directions[i] = offset;
					curr_grid->bugs[i] = Point(newPos.x,newPos.y);
					//Check if new bug position overlaps with a player again
					if (curr_grid->bugs[i] == currPlayerPoint) {
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
				newGridCopy->round++;
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
		bugPath.push_back(grid->bugs[i]);
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
			if (currPlayerPoint == curr_grid->snippets[i]) {
				foundItem = true;
			} else if (currEnemyPoint == curr_grid->snippets[i]) {
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
				if (currEnemyPoint == curr_grid->weapons[i]) { //Evaluate enemy on weapon first, because it's not worth the risk of both players landing on it at the same time.
					curr_grid->players[!playerID]->has_weapon = true;
					enemyFoundWeapon = i;
				} else if (currPlayerPoint == curr_grid->weapons[i]) {
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
					vector<Point>::iterator it = find(grid->bugs.begin(), grid->bugs.end(), Point(x,y));
					if (it != grid->bugs.end()) {
						if (walls[x][y])
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
							if (walls[x][y])
								cerr << "E ";
							else
								cerr << "E ";
							break;
						}
					} else if (walls[x][y])
						wall_character(grid, x, y);
					else if (find(grid->snippets.begin(), grid->snippets.end(), Point(x,y)) != grid->snippets.end())
						cerr << "SSS";
					else if (find(grid->weapons.begin(), grid->weapons.end(), Point(x,y)) != grid->weapons.end())
						cerr << "WWW";
					else if (grid->players[playerID]->x == x && grid->players[playerID]->y == y)
						cerr << "AAA";
					else if (grid->players[!playerID]->x == x && grid->players[!playerID]->y == y)
						cerr << "BBB";
					else {
						int symbolCount = 0;
						string symbols;
						vector<Point>::iterator it = find(curr_path.begin(), curr_path.end(), Point(x,y));
						if (it != curr_path.end()) {
							symbols += "a";
						}
						it = find(curr_bugPath.begin(), curr_bugPath.end(), Point(x,y));
						if (it != curr_bugPath.end()) {
							symbols += "e";
						}
						it = find(curr_enemyPath.begin(), curr_enemyPath.end(), Point(x,y));
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
			Point bugPos = curr_grid->bugs[i];
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
			curr_grid->bugs[i] = Point(newPos.x,newPos.y);
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
			int snipIndex = index[curr_grid->snippets[i].x][curr_grid->snippets[i].y];
			if (path_lengths[currEnemyIndex][snipIndex] < bestDist) {
				bestDist = path_lengths[currEnemyIndex][snipIndex];
				bestOffset = paths[currEnemyIndex][snipIndex];
			}
		}
		for (int i = 0; i < curr_grid->weapons.size(); ++i) {
			int wepIndex = index[curr_grid->weapons[i].x][curr_grid->weapons[i].y];
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
				newGridCopy->round++;
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