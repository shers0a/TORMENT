#pragma once

#include "Stats.hpp"
#include <string>
#include <ostream>

class Player{
    public:
        Player(const std::string& name, const Stats& stats,
            double iframe_cooldown, 
            double dodge_cooldown);
        ~Player();

        friend std::ostream& operator<<(std::ostream& os, const Player& player);

        bool dodge();
        bool isInvulnerable() const;
        void takeDamage(double x);
        bool isAlive() const;
        void update(double dt);
        double getAttackDamage() const;

    private:
        std::string name;
        Stats stats;
        double iframe_cooldown; //iframe = invincibility frame
        //also variabila asta detine durata invicibilitatii jucatorului 

        double iframe_remaining_cooldown;
        double dodge_cooldown; 
        double remaining_dodge_cooldown;
};