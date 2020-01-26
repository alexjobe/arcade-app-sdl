//
// Created by alex on 1/25/20.
//

#include "Block.h"
#include "Color.h"
#include "Screen.h"
#include "Ball.h"
#include "BoundaryEdge.h"

Block::Block() : mOutlineColor(Color::White()), mFillColor(Color::White()), mHP(1)
{

}

void Block::Init(const AARectangle& rect, int hp, const Color& outlineColor, const Color& fillColor)
{
    Excluder::Init(rect);
    mHP = hp;
    mOutlineColor = outlineColor;
    mFillColor = fillColor;

}

void Block::Draw(Screen& screen)
{
    screen.Draw(GetAARectangle(), mOutlineColor, true, mFillColor);

}

void Block::Bounce(Ball& ball, const BoundaryEdge& edge)
{
    ball.Bounce(edge);
}

void Block::ReduceHP()
{
    if(mHP > 0) { --mHP; }
}
