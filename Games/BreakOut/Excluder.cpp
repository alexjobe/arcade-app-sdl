//
// Created by alex on 1/16/20.
//
#include "Excluder.h"
#include "Utils.h"
#include <cmath>
#include <cassert>

void Excluder::Init(const AARectangle& rect, bool reverseNormals)
{
    mAARect = rect;
    mReverseNormals = reverseNormals;
    SetupEdges();
}

bool Excluder::HasCollided(const AARectangle& otherRect, BoundaryEdge& edge) const
{
    if(mAARect.Intersects(otherRect))
    {
        float ySize = CalculateYAxisOverlap(otherRect);
        float xSize = CalculateXAxisOverlap(otherRect);

        if(xSize > ySize)
        {
            if(otherRect.GetCenterPoint().GetY() > mAARect.GetCenterPoint().GetY())
            {
                edge = mEdges[BOTTOM_EDGE];
            }
            else
            {
                edge = mEdges[TOP_EDGE];
            }
        }
        else
        {
            if(otherRect.GetCenterPoint().GetX() < mAARect.GetCenterPoint().GetX())
            {
                edge = mEdges[LEFT_EDGE];
            }
            else
            {
                edge = mEdges[RIGHT_EDGE];
            }
        }

        return true;
    }

    return false;
}

Vec2D Excluder::GetCollisionOffset(const AARectangle& otherRect) const
{
    BoundaryEdge edge;
    Vec2D offset = Vec2D::Zero;

    if(HasCollided(otherRect, edge))
    {
        float ySize = CalculateYAxisOverlap(otherRect);
        float xSize = CalculateXAxisOverlap(otherRect);

        if(!IsEqual(edge.normal.GetY(), 0))
        {
            offset = (ySize + 1) * edge.normal;
        }
        else
        {
            offset = (xSize + 1) * edge.normal;
        }
    }
    return Vec2D::Zero;
}

float Excluder::CalculateYAxisOverlap(const AARectangle& otherRect) const
{
    float yMin = mAARect.GetTopLeftPoint().GetY() >= otherRect.GetTopLeftPoint().GetY()
                 ? mAARect.GetTopLeftPoint().GetY() : otherRect.GetTopLeftPoint().GetY();

    float yMax = mAARect.GetBottomRightPoint().GetY() <= otherRect.GetBottomRightPoint().GetY()
                 ? mAARect.GetBottomRightPoint().GetY() : otherRect.GetBottomRightPoint().GetY();

    return yMax - yMin;
}

float Excluder::CalculateXAxisOverlap(const AARectangle& otherRect) const
{
    float xMin = mAARect.GetTopLeftPoint().GetX() >= otherRect.GetTopLeftPoint().GetX()
                 ? mAARect.GetTopLeftPoint().GetX() : otherRect.GetTopLeftPoint().GetX();

    float xMax = mAARect.GetBottomRightPoint().GetX() <= otherRect.GetBottomRightPoint().GetX()
                 ? mAARect.GetBottomRightPoint().GetX() : otherRect.GetBottomRightPoint().GetX();

    return xMax - xMin;
}

void Excluder::MoveBy(const Vec2D& delta)
{
    mAARect.MoveBy(delta);
    SetupEdges();
}

void Excluder::MoveTo(const Vec2D& point)
{
    mAARect.MoveTo(point);
    SetupEdges();
}

const BoundaryEdge& Excluder::GetEdge(EdgeType edge) const
{
    assert(edge != NUM_EDGES);
    return mEdges[edge];
}

void Excluder::SetupEdges()
{
    mEdges[TOP_EDGE].edge = {mAARect.GetTopLeftPoint().GetX(), mAARect.GetTopLeftPoint().GetY(),
                             mAARect.GetBottomRightPoint().GetX(), mAARect.GetTopLeftPoint().GetY()};

    mEdges[TOP_EDGE].normal = UP_DIR;

    mEdges[LEFT_EDGE].edge = {mAARect.GetTopLeftPoint().GetX(), mAARect.GetTopLeftPoint().GetY(),
                              mAARect.GetTopLeftPoint().GetX(), mAARect.GetBottomRightPoint().GetY()};

    mEdges[LEFT_EDGE].normal = LEFT_DIR;

    mEdges[BOTTOM_EDGE].edge = {mAARect.GetTopLeftPoint().GetX(), mAARect.GetBottomRightPoint().GetY(),
                                mAARect.GetBottomRightPoint().GetX(), mAARect.GetBottomRightPoint().GetY()};

    mEdges[BOTTOM_EDGE].normal = DOWN_DIR;

    mEdges[RIGHT_EDGE].edge = {mAARect.GetBottomRightPoint().GetX(), mAARect.GetTopLeftPoint().GetY(),
                               mAARect.GetBottomRightPoint().GetX(), mAARect.GetBottomRightPoint().GetY()};

    mEdges[RIGHT_EDGE].normal = RIGHT_DIR;

    if(mReverseNormals)
    {
        for(auto& edge : mEdges)
        {
            edge.normal = -edge.normal;
        }
    }
}
