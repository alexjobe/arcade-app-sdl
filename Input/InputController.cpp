//
// Created by alex on 1/14/20.
//
#include "InputController.h"
#include "GameController.h"
#include <SDL2/SDL.h>

InputController::InputController() : mQuit(nullptr), mnoptrCurrentGameController(nullptr)
{

}

void InputController::Init(InputAction quitAction)
{
    mQuit = quitAction;
}

void InputController::Update(uint32_t dt)
{
    SDL_Event sdlEvent;

    while(SDL_PollEvent(&sdlEvent))
    {
        switch(sdlEvent.type)
        {
            case SDL_QUIT:
            {
                mQuit(dt, SDL_PRESSED);
            }
                break;
            case SDL_MOUSEMOTION:
            {
                if(mnoptrCurrentGameController)
                {
                    if(MouseMovedAction mouseMoved = mnoptrCurrentGameController->GetMouseMovedAction())
                    {
                        MousePosition position;
                        position.xPos = sdlEvent.motion.x;
                        position.yPos = sdlEvent.motion.y;
                        mouseMoved(position);
                    }
                }
                break;
            }
            case SDL_MOUSEBUTTONUP:
            case SDL_MOUSEBUTTONDOWN:
                if(mnoptrCurrentGameController)
                {
                    MouseInputAction action = mnoptrCurrentGameController->GetMouseButtonActionForMouseButton(static_cast<MouseButton>(sdlEvent.button.button));

                    MousePosition position;
                    position.xPos = sdlEvent.button.x;
                    position.yPos = sdlEvent.button.y;

                    action(static_cast<InputState>(sdlEvent.button.state), position);
                }
                break;
            case SDL_KEYDOWN:
            case SDL_KEYUP:

                if(mnoptrCurrentGameController)
                {
                    InputAction action = mnoptrCurrentGameController->GetActionForKey(sdlEvent.key.keysym.sym);

                    action(dt, static_cast<InputState>(sdlEvent.key.state));
                }
                break;
        }
    }
}

void InputController::SetGameController(GameController* controller)
{
    mnoptrCurrentGameController = controller;
}

