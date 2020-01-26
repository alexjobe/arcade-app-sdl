//
// Created by alex on 1/24/20.
//

#ifndef GAMES_BREAKOUT_LEVELBOUNDARY_H
#define GAMES_BREAKOUT_LEVELBOUNDARY_H

#include "Excluder.h"

class AARectangle;
class Ball;

class LevelBoundary
{
public:
    LevelBoundary(){}
    LevelBoundary(const AARectangle& boundary);
    bool HasCollided(const Ball& ball, BoundaryEdge& edge);
    inline const AARectangle& GetAARectangle() const { return mIncluder.GetAARectangle(); }

private:
    Excluder mIncluder;
    bool HasCollidedWithEdge(const Ball& ball, const BoundaryEdge& edge) const; // Check to see if we collided at all
};

#endif //GAMES_BREAKOUT_LEVELBOUNDARY_H
