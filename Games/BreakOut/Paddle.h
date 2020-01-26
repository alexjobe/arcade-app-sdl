//
// Created by alex on 1/19/20.
//

#ifndef GAMES_BREAKOUT_PADDLE_H
#define GAMES_BREAKOUT_PADDLE_H

#include "Excluder.h"
#include <cstdint>

class Screen;
class Ball;

enum PaddleDirection
{
    LEFT = 1 << 0,
    RIGHT = 1 << 1
};

class Paddle: public Excluder
{
public:
    static const uint32_t PADDLE_WIDTH = 50;
    static const uint32_t PADDLE_HEIGHT = 10;

    void Init(const AARectangle& rect, const AARectangle& boundary);
    void Update(uint32_t dt, Ball& ball);
    void Draw(Screen& screen);

    bool Bounce(Ball& ball);

    inline bool IsMovingLeft() const { return mDirection == PaddleDirection::LEFT; }
    inline bool IsMovingRight() const { return mDirection == PaddleDirection ::RIGHT; }

    inline void SetMovementDirection(PaddleDirection dir) { mDirection |= dir; }
    inline void UnsetMovementDirection(PaddleDirection dir) { mDirection &= ~dir; }
    inline void StopMovement() { mDirection = 0; }



private:
    uint32_t mDirection; // Direction to move
    AARectangle mBoundary; // Boundary the paddle is confined to
    const float VELOCITY = 220.0f; // Pixels/second
    const float CORNER_BOUNCE_AMOUNT = 0.2f;
};

#endif //GAMES_BREAKOUT_PADDLE_H
