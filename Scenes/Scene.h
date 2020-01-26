//
// Created by alex on 1/13/20.
//

#ifndef SCENES_SCENE_H
#define SCENES_SCENE_H

#include <string>
#include <stdint.h>
#include "GameController.h"

class Screen;

class Scene
{
public:
    virtual ~Scene(){}
    virtual void Init() = 0;
    virtual void Update(uint32_t dt) = 0;
    virtual void Draw(Screen& theScreen) = 0;
    virtual const std::string& GetSceneName() const = 0;

    GameController* GetGameController() { return &mGameController; }

protected:
    GameController mGameController;
};

#endif //SCENES_SCENE_H
