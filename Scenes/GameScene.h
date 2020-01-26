//
// Created by alex on 1/14/20.
//

#ifndef SCENES_GAMESCENE_H
#define SCENES_GAMESCENE_H

#include "Scene.h"
#include "Game.h"
#include <memory>

class GameScene: public Scene
{
public:
    GameScene(std::unique_ptr<Game> optrGame);
    virtual ~GameScene(){}
    virtual void Init() override;
    virtual void Update(uint32_t dt) override;
    virtual void Draw(Screen& screen) override;

    virtual const std::string& GetSceneName() const override;
private:
    std::unique_ptr<Game> mGame;
};

#endif //SCENES_GAMESCENE_H
