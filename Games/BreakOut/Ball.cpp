//
// Created by alex on 1/24/20.
//

#include "Ball.h"
#include "Utils.h"
#include "Screen.h"
#include "Circle.h"
#include "BoundaryEdge.h"

const float Ball::RADIUS = 5.0f;

Ball::Ball() : Ball(Vec2D::Zero, Ball::RADIUS)
{

}

Ball::Ball(const Vec2D& pos, float radius) :
    mBoundingBox(pos - Vec2D(radius, radius), radius * 2.0f, radius * 2.0f),
    mVelocity(Vec2D::Zero)
{

}

void Ball::Update(uint32_t dt)
{
    mBoundingBox.MoveBy(mVelocity * MillisecondsToSeconds(dt));
}

void Ball::Draw(Screen& screen)
{
    Circle circle = { mBoundingBox.GetCenterPoint(), GetRadius() };
    screen.Draw(circle, Color::Red(), true, Color::Red());
}

void Ball::MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge)
{
    if(edge.normal == DOWN_DIR)
    {
        mBoundingBox.MoveTo(Vec2D(mBoundingBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() + edge.normal.GetY()));
    }
    else if(edge.normal == UP_DIR)
    {
        mBoundingBox.MoveTo(Vec2D(mBoundingBox.GetTopLeftPoint().GetX(), edge.edge.GetP0().GetY() - mBoundingBox.GetHeight()));
    }
    else if(edge.normal == RIGHT_DIR)
    {
        mBoundingBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() + edge.normal.GetX(), mBoundingBox.GetTopLeftPoint().GetY()));
    }
    else if(edge.normal == LEFT_DIR)
    {
        mBoundingBox.MoveTo(Vec2D(edge.edge.GetP0().GetX() - mBoundingBox.GetWidth(), mBoundingBox.GetTopLeftPoint().GetY()));
    }

    pointOnEdge = edge.edge.ClosestPoint(mBoundingBox.GetCenterPoint(), limitToEdge);
}

void Ball::Bounce(const BoundaryEdge& edge)
{
    Vec2D pointOnEdge;

    MakeFlushWithEdge(edge, pointOnEdge, false);

    mVelocity = mVelocity.Reflect(edge.normal);
}

void Ball::MoveTo(const Vec2D& point)
{
    mBoundingBox.MoveTo(point - Vec2D(GetRadius(), GetRadius()));
}
