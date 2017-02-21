#include <vector>
#include "Cell.h"
#include "Grid.h"

using namespace std;

Grid* Grid::copy() {
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
	newGrid->playerWeapons[0] = playerWeapons[0];
	newGrid->playerWeapons[1] = playerWeapons[1];
	return newGrid;
}
void Grid::make_bugpath() {	//Remove the walls in the 'server room' to allow bug pathfinding.
	cells[9][6]->set_wall(false);
	cells[10][6]->set_wall(false);
	cells[8][7]->set_wall(false);
	cells[9][7]->set_wall(false);
	cells[10][7]->set_wall(false);
	cells[11][7]->set_wall(false);
}
void Grid::reset() {
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			delete cells[x][y];
			cells[x][y] = new Cell(x, y);
		}
	}
	wallCount = 0;
	playerWeapons[0] = false;
	playerWeapons[1] = false;
	snippets.clear();
	weapons.clear();
	bugs.clear();
}
Grid::Grid(int width, int height) {
	w = width;
	h = height;
	wallCount = 0;
	cells = vector<vector<Cell*>>(width);
	playerWeapons[0] = false;
	playerWeapons[1] = false;
	for (int x = 0; x < width; ++x) {
		cells[x] = vector<Cell*>(height);
		for (int y = 0; y < height; ++y) {
			cells[x][y] = new Cell(x, y);
		}
	}
}
Grid::~Grid() {
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			delete cells[x][y];
		}
	}
}