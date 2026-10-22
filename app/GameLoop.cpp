#pragma once

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