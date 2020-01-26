//
// Created by alex on 1/16/20.
//

#ifndef GAMES_BREAKOUT_BOUNDARYEDGE_H
#define GAMES_BREAKOUT_BOUNDARYEDGE_H

#include "Vec2D.h"
#include "Line2D.h"

//
//               ^  normal
//               |
// ------------------------------ edge
//

enum EdgeType
{
    BOTTOM_EDGE = 0,
    TOP_EDGE,
    LEFT_EDGE,
    RIGHT_EDGE,
    NUM_EDGES
};

static const Vec2D UP_DIR = {0, -1};
static const Vec2D DOWN_DIR = {0, 1};
static const Vec2D LEFT_DIR = {-1, 0};
static const Vec2D RIGHT_DIR = {1, 0};

struct BoundaryEdge
{
    Vec2D normal;
    Line2D edge;
};

#endif //GAMES_BREAKOUT_BOUNDARYEDGE_H
