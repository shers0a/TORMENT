#include "Attack.hpp"
#include <stdexcept>

Attack::Attack(const std::string& name, const double damage, const double cooldown, const int phase, const double beforeAtt) :
        name(name), damage(damage), cooldown(cooldown), remainingCooldown(0), phase(phase), beforeAtt(beforeAtt){}
        
std::ostream& operator<<(std::ostream& os, const Attack& attack){
    os << "Attack: " << "\n";
    os << "\t NAME: " << attack.name << "\n";
    os << "\t DAMAGE: " << attack.damage << "\n";
    os << "\t COOLDOWN: " << attack.cooldown << "\n";
    os << "\t PHASE: " << attack.phase << "\n";
    os << "\t BEFORE ATTACK: " << attack.beforeAtt;

    return os;
}

std::string Attack::getName() const{
    return ( this -> name );
}

double Attack::getDamage() const{
    return ( this -> damage );
}

double Attack::getBeforeAtt() const{
    return ( this -> beforeAtt );
}

bool Attack::isAvailableInPhase(int current_phase) const{
    if( this -> phase == current_phase ){
        return true;
    }

    return false; 
}

bool Attack::finishedCooldown() const{
    if( this -> remainingCooldown <= 0 ){
        return true;
    }

    return false;
}

void Attack::use(){
    this -> remainingCooldown = this -> cooldown;
}

void Attack::update(double dt){
    if( dt < 0 ){
        throw std::invalid_argument("The time unit must not be less than 0.");
    }
    
    if(this -> remainingCooldown <= 0 ){ // a trecut cooldown ul
        return;
    }

    this -> remainingCooldown -= dt;
}