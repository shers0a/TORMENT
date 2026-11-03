#pragma once

#include "Player.hpp"
#include "Boss.hpp"
#include <ostream>

class Fight{
    public:
        Fight(Player& player, Boss& boss, double vulnerability_window);
        ~Fight();

        friend std::ostream& operator<<(std::ostream& os, const Fight& fight);

        void update(double dt);

        bool bossWon() const;
        bool playerWon() const;

        bool playerDodge();
        bool playerAttack();

    private:
        Player& player;
        Boss& boss;
        
        const Attack* attack;
        
        double remaining_beforeAtt;
        
        double vulnerability_window;
        double remaining_vulnerability_window;
};