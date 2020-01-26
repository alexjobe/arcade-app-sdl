//
// Created by alex on 12/8/19.
//

#include "Shape.h"

void Shape::MoveBy(const Vec2D& deltaOffset)
{
    for(Vec2D& point : mPoints)
    {
        point = point + deltaOffset;
    }
}

