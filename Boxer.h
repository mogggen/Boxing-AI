#pragma once
#include "Shape.h"
#include "Rectangle.h"

struct Boxer : public Shape
{
    Point2D pos;
    Point2D size;
    
    Rectangle ;
public:
    Boxer(Point2D pos, Point2D size);
    ~Boxer();

}