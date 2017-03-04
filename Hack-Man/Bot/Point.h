#pragma once
#ifndef POINT_H
#define POINT_H
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
	Point() {
		this->x = -1;
		this->y = -1;
	}
	Point(int x, int y) {
		this->x = x;
		this->y = y;
	}
};
#endif