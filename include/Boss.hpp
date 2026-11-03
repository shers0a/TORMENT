#pragma once

#include <string>
#include <vector>
#include "Attack.hpp"
#include "Stats.hpp"
#include <ostream>
#include <random>

class Boss{
    public:
        Boss(const std::string& name, const std::vector<Attack>&  attacks, const Stats& stats, double phase2Constant, std::mt19937::result_type seed);
        
        Boss(const Boss& _boss);

        Boss& operator=(const Boss& other);

        ~Boss();

        friend std::ostream& operator<<(std::ostream& os, const Boss& boss);

        const Attack* chooseAttack();
        void update(double dt);
        bool isAlive() const; 
        void takeDamage(double x);
        int currentPhase() const;

    private:
        std::string name;
        std::vector<Attack> attacks;
        Stats stats;
        std::mt19937 gen;
        double phase2Constant;
};