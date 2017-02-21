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
};
#endif