#include <iostream>
#include "Settings.hpp"
#include "GameLoop.hpp"

int main(){
    try {
        Settings settings("assets/data/config.json");
        GameLoop game(settings);
        game.run();
    } catch (const std::exception& e) {
        SDL_Log("Eroare: %s", e.what());
        return 1;
    }
    return 0;
}