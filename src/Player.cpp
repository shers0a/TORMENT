#include "Player.hpp"
#include <stdexcept>

Player::Player(const std::string& name, const Stats& stats, 
        const double iframe_cooldown, const double dodge_cooldown) :

        name(name), stats(stats), iframe_cooldown(iframe_cooldown), 
        iframe_remaining_cooldown(0),
        dodge_cooldown(dodge_cooldown),
        remaining_dodge_cooldown(0){
            if( dodge_cooldown <= iframe_cooldown){
                throw std::invalid_argument("The duration of the invincibility state must be less than the dodge cooldown.");
            }
        }

Player::~Player() = default;

std::ostream& operator<<(std::ostream& os, const Player& player){
    os << "PLAYER: " << player.name << "\n";
    os << "\t" << player.stats << "\n";

    return os;
}

bool Player::dodge(){
    if(remaining_dodge_cooldown){
        return false; //nu a reusit dodge ul :((
    }   

    iframe_remaining_cooldown = iframe_cooldown;
    remaining_dodge_cooldown = dodge_cooldown;

    return true; // a reusit dodge ul :DDDD
}

bool Player::isInvulnerable() const{
    if(iframe_remaining_cooldown){
        return true; //inca mai e invincibil (yay)
    }

    return false; //nu mai e invincibil ce lachete
}

void Player::takeDamage(double x){
    stats.damageTaken(x);
}

double Player::getAttackDamage() const{
    return stats.getDamage();
}

void Player::update(double dt){
    if( dt < 0 ){
        throw std::invalid_argument("/include/Player.cpp must be positive.");
    }

    iframe_remaining_cooldown -= dt;
    remaining_dodge_cooldown -= dt;

    if( iframe_remaining_cooldown < 0 ){
        iframe_remaining_cooldown = 0;
    }

    if(remaining_dodge_cooldown < 0){
        remaining_dodge_cooldown = 0;
    }
}

bool Player::isAlive() const{
    if(stats.getHp() > 0 ){
        return true;
    }

    return false;
}