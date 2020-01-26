//
// Created by alex on 1/16/20.
//

#include "BreakOut.h"
#include "GameController.h"
#include "App.h"
#include "Circle.h"
#include <iostream>

void BreakOut::Init(GameController& controller)
{
    controller.ClearAll();

    ResetGame();

    ButtonAction serveAction;
    serveAction.key = GameController::ActionKey();
    serveAction.action = [this](uint32_t dt, InputState state)
    {
        if(mGameState == IN_SERVE)
        {
            if(GameController::IsPressed(state))
            {
                mGameState = IN_PLAY;
                if(mPaddle.IsMovingLeft())
                {
                    mBall.SetVelocity(Vec2D(-INITIAL_BALL_SPEED, -INITIAL_BALL_SPEED));
                }
                else
                {
                    mBall.SetVelocity(Vec2D(INITIAL_BALL_SPEED, INITIAL_BALL_SPEED));
                }
            }
        }
        else if(mGameState == IN_GAME_OVER)
        {
            if(GameController::IsPressed(state))
            {
                ResetGame();
            }
        }
    };

    controller.AddInputActionForKey(serveAction);

    ButtonAction leftKeyAction;
    leftKeyAction.key = GameController::LeftKey();
    leftKeyAction.action = [this](uint32_t dt, InputState state)
    {
        if(mGameState == IN_PLAY || mGameState == IN_SERVE)
        {
            if (GameController::IsPressed(state))
            {
                mPaddle.SetMovementDirection(PaddleDirection::LEFT);
            }
            else
            {
                mPaddle.UnsetMovementDirection(PaddleDirection::LEFT);
            }
        }
    };

    controller.AddInputActionForKey(leftKeyAction);

    ButtonAction rightKeyAction;
    rightKeyAction.key = GameController::RightKey();
    rightKeyAction.action = [this](uint32_t dt, InputState state)
    {
        if(mGameState == IN_PLAY || mGameState == IN_SERVE)
        {
            if(GameController::IsPressed(state))
            {
                mPaddle.SetMovementDirection(PaddleDirection::RIGHT);
            }
            else
            {
                mPaddle.UnsetMovementDirection(PaddleDirection::RIGHT);
            }
        }
    };

    controller.AddInputActionForKey(rightKeyAction);
}

void BreakOut::Update(uint32_t dt)
{
    if(mGameState == IN_SERVE)
    {
        mPaddle.Update(dt, mBall);
        SetToServeState();
    }
    else if (mGameState == IN_PLAY)
    {
        mPaddle.Update(dt, mBall);
        mBall.Update(dt);

        BoundaryEdge edge;

        if(mPaddle.Bounce(mBall))
        {
            return; // Return so we only bounce once this frame
        }

        if(mLevelBoundary.HasCollided(mBall, edge))
        {
            mBall.Bounce(edge);
            return;
        }

        GetCurrentLevel().Update(dt, mBall);

        if(IsBallPastCutoffY())
        {
            ReduceLifeByOne();
            if(!IsGameOver())
            {
                SetToServeState();
            }
            else
            {
                mGameState = IN_GAME_OVER;
            }
        }
        else if(GetCurrentLevel().IsLevelComplete())
        {
            mCurrentLevel = (mCurrentLevel + 1) % mLevels.size();
            ResetGame(mCurrentLevel);
        }
    }
}

void BreakOut::Draw(Screen& screen)
{
    mPaddle.Draw(screen);
    mBall.Draw(screen);
    GetCurrentLevel().Draw(screen);
    screen.Draw(mLevelBoundary.GetAARectangle(), Color::White());

//    Line2D cutoff = { Vec2D(0, mYCutoff), Vec2D(App::Singleton().Width(), mYCutoff) };
//    screen.Draw(cutoff, Color::White());

    Circle lifeCircle = { Vec2D(7, App::Singleton().Height() - 10), 5 };

    for(int i = 0; i < mLives; ++i)
    {
        screen.Draw(lifeCircle, Color::Red(), true, Color::Red());
        lifeCircle.MoveBy(Vec2D(17, 0));
    }
}

const std::string& BreakOut::GetName() const
{
    return mName;
}

void BreakOut::ResetGame(size_t toLevel)
{
    mLevels = BreakOutGameLevel::LoadLevelsFromFile(App::GetBasePath() + "Assets/BreakoutLevels.txt");
    mCurrentLevel = toLevel;
    mLives = NUM_LIVES;
    mYCutoff = App::Singleton().Height() - 2 * mBall.GetRadius();

    AARectangle paddleRect =
    {
        Vec2D(
            App::Singleton().Width() / 2 - Paddle::PADDLE_WIDTH / 2,
            App::Singleton().Height() - 3 * Paddle::PADDLE_HEIGHT
        ),
        Paddle::PADDLE_WIDTH, Paddle::PADDLE_HEIGHT
    };

    AARectangle levelBoundaryRect = { Vec2D::Zero, App::Singleton().Width(), App::Singleton().Height() };
    mLevelBoundary = { levelBoundaryRect };

    mPaddle.Init(paddleRect, levelBoundaryRect);
    mBall.MoveTo(Vec2D(App::Singleton().Width() / 2, App::Singleton().Height() * 0.75f));

    SetToServeState();
}

void BreakOut::SetToServeState()
{
    mGameState = IN_SERVE;
    mBall.Stop();
    mBall.MoveTo(Vec2D(mPaddle.GetAARectangle().GetCenterPoint().GetX(),
            mPaddle.GetAARectangle().GetTopLeftPoint().GetY() - mBall.GetRadius() - 1));
}

bool BreakOut::IsBallPastCutoffY() const
{
    return mBall.GetPosition().GetY() > mYCutoff;
}

void BreakOut::ReduceLifeByOne()
{
    if(mLives >= 0) { --mLives; }
}
