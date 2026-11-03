#include "Boss.hpp"
#include <stdexcept>

Boss::Boss(const std::string& name, const std::vector<Attack>& attacks, const Stats& stats, const double phase2Constant, std::mt19937::result_type seed):
        name(name), attacks(attacks), stats(stats), gen(seed), phase2Constant(phase2Constant){
            if(phase2Constant > 1.0 || phase2Constant < 0.0 ){
                throw std::invalid_argument("The phase transitioning constant must be in the interval [0,1].");
            }
        }


Boss::Boss(const Boss& _boss) : 
    name(_boss.name), attacks(_boss.attacks), stats(_boss.stats), gen(_boss.gen), phase2Constant(_boss.phase2Constant){}

Boss::~Boss() = default;

Boss& Boss::operator=(const Boss& _boss){
    if( this == &_boss){
        return *this;
    }

    name = _boss.name;
    attacks = _boss.attacks;
    stats = _boss.stats;
    gen = _boss.gen;
    phase2Constant = _boss.phase2Constant;
    
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

bool Boss::isAlive() const{
    if(stats.getHp() > 0 ){
        return true;
    }

    return false;
}

int Boss::currentPhase() const{
    if(stats.getHp() < stats.getMaxHp() * phase2Constant ){
        return 2;
    }

    return 1;
}

void Boss::takeDamage(double x){
    stats.damageTaken(x);
}

const Attack* Boss::chooseAttack(){
    std::vector<std::size_t> positions;

    int current_phase = currentPhase();

    for( std::size_t i = 0; i < attacks.size(); i++ ){
        if(attacks[i].isAvailableInPhase(current_phase) && attacks[i].finishedCooldown()){
            positions.push_back(i); //adaugam attack ul 
        }
    }
    
    if(positions.empty()){
        return nullptr; //no attacks available
    }

    std::uniform_int_distribution<std::size_t> choose_attack_randomizer(0, positions.size() - 1);

    std::size_t chosen_attack = choose_attack_randomizer(gen);

    attacks[positions[chosen_attack]].use();
    
    return &attacks[positions[chosen_attack]];
}

void Boss::update(double dt){
    for( auto& attack : attacks ){
        attack.update(dt);
    }
}