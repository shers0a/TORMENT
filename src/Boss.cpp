#include "Boss.hpp"

Boss::Boss(const std::string& name, const std::vector<Attack>& attacks, const Stats& stats):
        name(name), attacks(attacks), stats(stats), gen(std::random_device{}()){

        }


Boss::Boss(const Boss& _boss) : 
    name(_boss.name), attacks(_boss.attacks), stats(_boss.stats), gen(std::random_device{}()){}

Boss::~Boss() = default;

Boss& Boss::operator=(const Boss& _boss){
    if( this == &_boss){
        return *this;
    }

    name = _boss.name;
    attacks = _boss.attacks;
    stats = _boss.stats;

    return *this;
}

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

bool Boss::currentHp() const{
    if(stats.getHp() > 0 ){
        return true;
    }

    return false;
}

int Boss::currentPhase() const{
    if(stats.getHp() < stats.getMaxHp() / 2 ){
        return 2;
    }

    return 1;
}

void Boss::takeDamage(double x){
    stats.damageTaken(x);
}

void Boss::chooseAttack(){
    std::vector<std::size_t> positions;

    int current_phase = currentPhase();

    for( std::size_t i = 0; i < attacks.size(); i++ ){
        if(attacks[i].isAvailableInPhase(current_phase) && attacks[i].finishedCooldown()){
            positions.push_back(i); //adaugam attack ul 
        }
    }
    
    if(positions.empty()){
        return; //no attacks available
    }

    std::uniform_int_distribution<std::size_t> choose_attack_randomizer(0, positions.size() - 1);

    std::size_t chosen_attack = choose_attack_randomizer(gen);

   attacks[positions[chosen_attack]].use();
}