//
// Created by alex on 1/16/20.
//

#ifndef GAMES_BREAKOUT_EXCLUDER_H
#define GAMES_BREAKOUT_EXCLUDER_H

#include "AARectangle.h"
#include "BoundaryEdge.h"

class Excluder
{
public:
    virtual ~Excluder() {}
    void Init(const AARectangle& rect, bool reverseNormals = false);
    bool HasCollided(const AARectangle& otherRect, BoundaryEdge& edge) const;
    Vec2D GetCollisionOffset(const AARectangle& rect) const;
    inline const AARectangle& GetAARectangle() const { return mAARect; }
    void MoveBy(const Vec2D& delta);
    void MoveTo(const Vec2D& point);
    const BoundaryEdge& GetEdge(EdgeType edge) const;

private:
    void SetupEdges();
    float CalculateYAxisOverlap(const AARectangle& otherRect) const;
    float CalculateXAxisOverlap(const AARectangle& otherRect) const;
    AARectangle mAARect;
    BoundaryEdge mEdges[NUM_EDGES];
    bool mReverseNormals;
};

#endif //GAMES_BREAKOUT_EXCLUDER_H
