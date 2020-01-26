//
// Created by alex on 1/16/20.
//

#ifndef GAMES_BREAKOUT_BREAKOUT_H
#define GAMES_BREAKOUT_BREAKOUT_H

#include "Game.h"
#include "Paddle.h"
#include "Ball.h"
#include "LevelBoundary.h"
#include "BreakOutGameLevel.h"
#include <vector>

enum BreakOutGameState
{
    IN_PLAY = 0,
    IN_SERVE,
    IN_GAME_OVER
};

class BreakOut: public Game
{
public:
    void Init(GameController& controller) override;
    void Update(uint32_t dt) override;
    void Draw(Screen& screen) override;
    const std::string& GetName() const override;

private:
    const int NUM_LIVES = 3;
    void ResetGame(size_t toLevel = 0);

    BreakOutGameLevel& GetCurrentLevel() { return mLevels[mCurrentLevel]; }
    void SetToServeState();
    bool IsBallPastCutoffY() const;
    void ReduceLifeByOne();
    bool IsGameOver() const { return mLives < 0; }

    const float INITIAL_BALL_SPEED = 200;
    const std::string mName = "Break Out!";

    Paddle mPaddle;
    Ball mBall;
    LevelBoundary mLevelBoundary;
    std::vector<BreakOutGameLevel> mLevels;
    size_t mCurrentLevel;
    BreakOutGameState mGameState;
    int mLives;
    float mYCutoff;
};

#endif //GAMES_BREAKOUT_BREAKOUT_H
