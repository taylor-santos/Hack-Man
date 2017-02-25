#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Point.h"
#include <string>
class Player : public Point {
public:
	int snippets;
	bool has_weapon;
	bool is_paralyzed;
	Player() {};
	Player(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
#endif