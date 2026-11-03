#include "Fight.hpp"

Fight::Fight(Player& player, Boss& boss, const double vulnerability_window) :
        player(player), boss(boss), attack(nullptr), remaining_beforeAtt(0),
        vulnerability_window(vulnerability_window),
        remaining_vulnerability_window(0){}

Fight::~Fight() = default;


void Fight::update(double dt){
    player.update(dt);
    boss.update(dt);

    if(attack != nullptr){
        remaining_beforeAtt -= dt;
        
        if(remaining_beforeAtt < 0){
            remaining_beforeAtt = 0;
        }
    
        if( remaining_beforeAtt == 0 ){
            if(!player.isInvulnerable()){
                player.takeDamage(attack -> getDamage());
            }

            remaining_vulnerability_window = vulnerability_window;
            // dupa ce ataca e vulnerabil asa ca se deschide fereastra de timp de in care e vulnerabil
            
            attack = nullptr;
        }
    }
    else if(remaining_vulnerability_window > 0){
        remaining_vulnerability_window -= dt;

        if(remaining_vulnerability_window < 0){
            remaining_vulnerability_window = 0;
        }
    }
    else{
        attack = boss.chooseAttack();

        //basically daca nu e niciun atac disponibil attack ramane nullptr
        if(attack != nullptr){
            remaining_beforeAtt = attack -> getBeforeAtt();
        }
    }
}

bool Fight::bossWon() const{
    return (!player.isAlive());
}

bool Fight::playerWon() const{
    return (!boss.isAlive());
}

bool Fight::playerDodge(){
    return player.dodge();
}

bool Fight::playerAttack(){
    if(remaining_vulnerability_window > 0){
        boss.takeDamage(player.getAttackDamage());
        
        remaining_vulnerability_window = 0;

        return true;
    }

    return false;
}

std::ostream& operator<<(std::ostream& os, const Fight& fight){
    os << "FIGHT BETWEEN: "<< "\n";
    os << "\t" << fight.player << "\n";
    os << "\t" << fight.boss << "\n";

    if(fight.attack != nullptr){
        os << "ONGOING: " << "\n\t";    
        os << "\t" << *fight.attack;
    }
    else if(fight.remaining_vulnerability_window > 0){
        os << "VULNERABLE FOR: " << fight.remaining_vulnerability_window;
    }
    else{
        os << "BOSS IS CHOOSING THE ATTACK.";
    }

    return os;
}