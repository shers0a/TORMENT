#pragma once

#include <string>
#include <vector>
#include "Attack.hpp"
#include "Stats.hpp"
#include <ostream>

class Boss{
    public:
        Boss(const std::string& name, const std::vector<Attack>&  attacks, const Stats& stats);
        ~Boss();

        friend std::ostream& operator<<(std::ostream& os, const Boss& boss);

        std::string getName() const;

        void chooseAttack();
        void update(double dt);
        bool currentHp() const;
        void takeDamage(double x);
        int currentPhase();

    private:
        std::string name;
        std::vector<Attack> attacks;
        Stats stats;
};