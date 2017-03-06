#include <vector>
#include "Grid.h"

using namespace std;

Grid* Grid::copy() {
	Grid* newGrid = new Grid(w, h);
	newGrid->round = round;
	newGrid->bugs = bugs;
	newGrid->bug_directions = bug_directions;
	newGrid->snippets = snippets;
	newGrid->weapons = weapons;
	for (int i = 0; i < 2; ++i) {
		newGrid->players[i].x = players[i].x;
		newGrid->players[i].y = players[i].y;
		newGrid->players[i].snippets = players[i].snippets;
		newGrid->players[i].has_weapon = players[i].has_weapon;
		newGrid->players[i].is_paralyzed = players[i].is_paralyzed;
	}
	return newGrid;
	/*
	for (int i = 0; i < snippets.size(); ++i) {
		newGrid->snippets.push_back(this->snippets[i]);
	}
	for (int i = 0; i < weapons.size(); ++i) {
		newGrid->weapons.push_back(this->weapons[i]);
	}
	for (int i = 0; i < bugs.size(); ++i) {
		newGrid->bugs.push_back(this->bugs[i]);
		newGrid->bug_directions.push_back(this->bug_directions[i]);
	}
	for (int i = 0; i < 2; ++i) {
		newGrid->players[i].x = players[i].x;
		newGrid->players[i].y = players[i].y;
		newGrid->players[i].snippets = players[i].snippets;
		newGrid->players[i].has_weapon = players[i].has_weapon;
		newGrid->players[i].is_paralyzed = players[i].is_paralyzed;
	}
	*/
	return newGrid;
}

void Grid::reset() {
	for (int player = 0; player < 2; ++player) {
		players[player].has_weapon = false;
		players[player].is_paralyzed = false;
		players[player].snippets = 0;
		players[player].x = -1;
		players[player].y = -1;
	}
	snippets.clear();
	weapons.clear();
	bugs.clear();
	bug_directions.clear();
}
Grid::Grid(int width, int height) {
	w = width;
	h = height;
}
Grid::~Grid() {
}