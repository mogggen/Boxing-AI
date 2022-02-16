#pragma once
#include <iostream>
#include "SDL.h"
#include "Point2D.h"

class Shape
{
protected:
	Point2D position;
	float angle;
	Point2D pivot;
	float torque;
	Point2D velocity;
public:
	Shape();
	~Shape();
	Shape(Point2D position);
	Shape(Point2D position, float angle, Point2D pivot);
	bool DetectCollision(Shape Other);
	virtual void render(SDL_Renderer *renderer);
};