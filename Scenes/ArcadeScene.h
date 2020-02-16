//
// Created by alex on 1/13/20.
//

#ifndef SCENES_ARCADESCENE_H
#define SCENES_ARCADESCENE_H

#include "Scene.h"
#include "SpriteSheet.h"
#include <memory>

enum eGame
{
    TETRIS = 0,
    BREAK_OUT,
    ASTEROIDS,
    PACMAN,
    NUM_GAMES
};

class Screen;

class ArcadeScene: public Scene
{
public:
    ArcadeScene();
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& theScreen) override;
    virtual const std::string& GetSceneName() const override;

private:
    std::unique_ptr<Scene> GetScene(eGame game);

    // Temporary
    SpriteSheet mTempSS;
};

#endif //SCENES_ARCADESCENE_H
