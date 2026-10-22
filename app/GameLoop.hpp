#pragma once

#include <iostream>
#include <SDL3/SDL.h>
#include <memory>
#include "Input.hpp"
#include "Scenes.hpp"
#include "Settings.cpp"

class GameLoop{
    public:
        GameLoop(const Settings& settings);
        ~GameLoop() = default;

        //impiedica copierea de tipul GameLoop b(a) si GameLoop a = b;
        //ar provoca crash uri la delete deoarece ar copia window urile

        GameLoop(const GameLoop&) = delete;
        GameLoop& operator=(const GameLoop&) = delete;

        void run();

    private:

        void eventHandler();
        void render();
        void update(double dt);

        /*
            practic cand misti jucatorul el se misca cu dt = 1/60
            dt = miscarea in timp a acestuia
            => d(viteza) = dx/dt
            => acceleratie = dv/dt = d/dt(dx/dt) = dx/d2t
            viteza += acceleratie * dt = viteza + dx/d2t * dt = viteza + dv;
        */
        static constexpr double DT = 1.0/60.0;
        
        /*
            daca jocul se blocheaza pentru un nr mare de secunde, ar rula update de multe ori 
            pentru a recupera timpul pierdut, ceea ce ar duce la o perioada de timp de rulare
            mare, deci iar ar trebui sa recupere, facand un loop.

            astfel, daca timpul de rulare este mai mare de .25 secunde => ca jocul va considera ca 
            au trecut doar .25 secunde.
        */
        
        static constexpr double SAFETY_LIMIT = 0.25;

        SDL_Window *win = nullptr;
        SDL_Renderer* ren = nullptr;

        bool running = true;

};