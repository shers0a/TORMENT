#include <iostream>
#include "Settings.cpp"
#include "GameLoop.cpp"

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