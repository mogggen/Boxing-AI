
#pragma once
#include "Shape.h"

struct Rectangle : public Shape
{
	float width, height;
public:
	Rectangle();

	void SetRectangle(Point2D position, float width, float height);
	void SetRotation(float angle, Point2D pivot);

	void CollisionResponse(Point2D newVelocity, float newTorque, Point2D newForce);

	void render(SDL_Renderer *renderer);
};