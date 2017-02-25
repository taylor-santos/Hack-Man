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
		newGrid->bug_directions.push_back(bug_directions[i]);
	}
	for (int i = 0; i < 2; ++i) {
		newGrid->players[i]->x = players[i]->x;
		newGrid->players[i]->y = players[i]->y;
		newGrid->players[i]->snippets = players[i]->snippets;
		newGrid->players[i]->has_weapon = players[i]->has_weapon;
		newGrid->players[i]->is_paralyzed = players[i]->is_paralyzed;
	}
	return newGrid;
}

void Grid::reset() {
	for (int x = 0; x < w; ++x) {
		for (int y = 0; y < h; ++y) {
			delete cells[x][y];
			cells[x][y] = new Cell(x, y);
		}
	}
	delete players[0];
	delete players[1];
	players[0] = new Player();
	players[1] = new Player();
	wallCount = 0;
	snippets.clear();
	weapons.clear();
	bugs.clear();
	bug_directions.clear();
}
Grid::Grid(int width, int height) {
	w = width;
	h = height;
	wallCount = 0;
	cells = vector<vector<Cell*>>(width);
	players[0] = new Player();
	players[1] = new Player();
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
	delete players[0];
	delete players[1];
}