#include "GameLoop.hpp"
#include <stdexcept>
#include <string>

GameLoop::GameLoop(const Settings& settings){
    if(!SDL_Init(SDL_INIT_VIDEO))
        throw std::runtime_error(SDL_GetError());
}

void GameLoop::run(){
    while(running){
        eventHandler();
    }
}

void GameLoop::eventHandler(){
    SDL_Event event;

    while(SDL_PollEvent(&event)){
        if( event.type == SDL_EVENT_QUIT){
            running = false;
            break;
        }
    }
}