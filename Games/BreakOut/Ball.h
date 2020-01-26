//
// Created by alex on 1/24/20.
//

#ifndef GAMES_BREAKOUT_BALL_H
#define GAMES_BREAKOUT_BALL_H

#include "AARectangle.h"
#include <cstdint>

class Screen;
struct BoundaryEdge;

class Ball
{
public:
    Ball();
    Ball(const Vec2D& pos, float radius);

    void Update(uint32_t dt);
    void Draw(Screen& screen);
    void MakeFlushWithEdge(const BoundaryEdge& edge, Vec2D& pointOnEdge, bool limitToEdge);
    void MoveTo( const Vec2D& point);
    void Bounce(const BoundaryEdge& edge);

    inline void Stop() { mVelocity = Vec2D::Zero; };
    inline const AARectangle GetBoundingRect() const { return mBoundingBox; };
    inline void SetVelocity(const Vec2D& vel) { mVelocity = vel; }
    inline Vec2D GetVelocity() const { return mVelocity; }
    inline float GetRadius() const { return mBoundingBox.GetWidth() / 2.0f; }
    inline Vec2D GetPosition() const { return mBoundingBox.GetCenterPoint(); }


private:
    AARectangle mBoundingBox;
    Vec2D mVelocity;
    static const float RADIUS;
};

#endif //GAMES_BREAKOUT_BALL_H
