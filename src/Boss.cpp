#include "Boss.hpp"
#include <random>

Boss::Boss(const std::string& name, const std::vector<Attack>& attacks, const Stats& stats):
        name(name), attacks(attacks), stats(stats){}

std::ostream& operator<<(std::ostream& os, const Boss& boss){
    os << "BOSS" << "\n";
    os << "\t NAME: " << boss.name << "\n";
    os << "\t" << boss.stats << "\n";
    
    for( const auto& attack : boss.attacks ){
        os << "\t" << attack << "\n";
    }

    return os;
}

std::string Boss::getName() const{
    return ( this -> name );
}
void Boss::chooseAttack(){

}

bool Boss::currentHp() const{
    if(stats.getHp() > 0 ){
        return true;
    }

    return false;
}

int Boss::currentPhase(){
    if(stats.getHp() < stats.getMaxHp() ){
        return 2;
    }

    return 1;
}

void Boss::takeDamage(double x){
    stats.damageTaken(x);
}