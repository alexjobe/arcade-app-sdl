//
// Created by alex on 1/14/20.
//

#ifndef INPUT_INPUTCONTROLLER_H
#define INPUT_INPUTCONTROLLER_H

#include "InputAction.h"

class GameController;

class InputController
{
public:
    InputController();
    void Init(InputAction quitAction);
    void Update(uint32_t dt);
    void SetGameController(GameController* controller);
private:
    InputAction mQuit;
    GameController* mnoptrCurrentGameController;
};

#endif //INPUT_INPUTCONTROLLER_H
