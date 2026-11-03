#include "Stats.hpp"

Stats::Stats(double maxHp, double hp, double damage, double def, double spd) : maxHp(maxHp), hp(hp), damage(damage), def (def), spd(spd){}

double Stats::getHp() const{
    return this -> hp;
}

double Stats::getDamage() const{
    return this -> damage;
}

double Stats::getMaxHp() const{
    return this -> maxHp;
}

/**************************/

void Stats::damageTaken(const double damage_taken){
    double damage_to_be_taken = damage_taken - def;
    if(damage_to_be_taken < 0){
        damage_to_be_taken = 0;
    }
    
    if( damage_to_be_taken > (this -> hp) ){
        this -> hp = 0;

        return;
    }

    this -> hp -= damage_to_be_taken;
}

std::ostream& operator<<(std::ostream& os, const Stats& stats){
    os << "Stats: " << "\n" << "MAX HP: " << stats.getMaxHp() << "\n";
    os << "CURRENT HP: " << stats.hp << "\n";
    os << "DEF: " << stats.def << "\n";
    os << "DMG: " << stats.damage << "\n";
    os << "SPD: " << stats.spd;

    return os;
}