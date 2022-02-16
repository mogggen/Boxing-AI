#pragma once
#include <iostream>
#include "SDL.h"
#include "Point2D.h"

class Shape
{
protected:
	Point2D pos;
	float angle;
	Point2D pivot;
	float torque;
	Point2D velocity;
public:
	Shape();
	~Shape();
	Shape(Point2D pos);
	Shape(Point2D pos, float angle, Point2D pivot);
	virtual void render(SDL_Renderer *renderer);
};