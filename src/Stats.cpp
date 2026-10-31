#include "Stats.hpp"

Stats::Stats(double maxHp, double hp, double damage, double def, double spd) : maxHp(maxHp), hp(hp), damage(damage), def (def), spd(spd){}

double Stats::getHp() const{
    return this -> hp;
}

double Stats::getDamage() const{
    return this -> damage;
}

double Stats::getDef() const{
    return this -> def;
}

double Stats::getSpd() const{
    return this -> spd;
}

double Stats::getMaxHp() const{
    return this -> maxHp;
}

/**************************/

void Stats::damageTaken(const double damage_taken){
    if( damage_taken > (this -> hp) ){
        this -> hp = 0;

        return;
    }

    this -> hp -= damage_taken;
}

void Stats::increaseHp(const double hp_adder){
    if( (this -> hp + hp_adder) > (this -> maxHp) ){
        this -> hp = this -> maxHp;

        return;
    }

    this -> hp += hp_adder;
}

void Stats::increaseDef(const double def_increase){
        this -> def += def_increase;
}

void Stats::increaseSpd(const double spd_increase){
    this -> spd += spd_increase;
}

void Stats::increaseMaxHp(const double maxhp_adder){
    double percent = ( this -> hp ) * 100.0 / (this -> maxHp);
    
    this -> maxHp += maxhp_adder;
    this -> hp = percent * 100.0 / (this -> maxHp);
}

std::ostream& operator<<(std::ostream& os, const Stats& stats){
    os << "Stats: " << "\n" << "MAX HP: " << stats.getMaxHp() << "\n";
    os << "CURRENT HP: " << stats.getHp() << "\n";
    os << "DEF: " << stats.getDef() << "\n";
    os << "DMG: " << stats.getDamage() << "\n";
    os << "SPD: " << stats.getSpd();

    return os;
}