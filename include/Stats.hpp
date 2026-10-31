#pragma once
#include <ostream>

class Stats{
    public:
        Stats(double maxHp, double hp, double damage, double def, double spd);

        friend std::ostream& operator<<(std::ostream& os, const Stats& stats);
        
        //getteri

        double getHp() const;
        double getDamage() const;
        double getDef() const;
        double getSpd() const;
        double getMaxHp() const;

        //stats modifieri

        void damageTaken(const double damage_taken);
        void increaseHp(const double hp_adder);
        void increaseDef(const double def_increase);
        void increaseSpd(const double spd_increase);
        void increaseMaxHp(const double maxhp_adder);

    private:
        double maxHp;
        double hp;
        double damage;
        double def;
        double spd;
}; 