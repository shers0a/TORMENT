#pragma once
#include <ostream>

class Stats{
    public:
        Stats(double maxHp, double hp, double damage, double def, double spd);

        friend std::ostream& operator<<(std::ostream& os, const Stats& stats);
        
        //getteri

        double getHp() const;
        double getDamage() const;
        double getMaxHp() const;

        //stats modifieri

        void damageTaken(const double damage_taken);

    private:
        double maxHp;
        double hp;
        double damage;
        double def;
        double spd;
}; 