//
// Created by alex on 1/25/20.
//

#ifndef GAMES_BREAKOUT_BLOCK_H
#define GAMES_BREAKOUT_BLOCK_H

#include "Excluder.h"
#include "Color.h"

class Ball;
class Screen;
struct BoundaryEdge;

class Block : public Excluder
{
public:
    static const int UNBREAKABLE = -1;

    Block();
    void Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor);
    void Draw(Screen& screen);
    void Bounce(Ball& ball, const BoundaryEdge& edge);
    void ReduceHP();

    inline int GetHP() const { return mHP; }
    inline bool IsDestroyed() const { return mHP == 0; }
    inline const Color& GetOutlineColor() { return mOutlineColor; }
    inline const Color& GetFillColor() const { return mFillColor; }

private:
    Color mOutlineColor;
    Color mFillColor;
    int mHP; // -1 means unbreakable
};

#endif //GAMES_BREAKOUT_BLOCK_H
