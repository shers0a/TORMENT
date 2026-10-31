#pragma once

#include <string>
#include <ostream>

class Attack{
    public:
        Attack(const std::string& name, double damage, double cooldown, int phase, double beforeAtt);

        friend std::ostream& operator<<(std::ostream& os, const Attack& attack);
    
        std::string getName() const;
        double getDamage() const;
        double getBeforeAtt() const;

        bool isAvailableInPhase(int current_phase) const;
        bool finishedCooldown() const;
        void use();
        void update(double dt);

    private:
        std::string name;
        
        double damage;
        double cooldown;
        double remainingCooldown;

        int phase;
        
        //practic cate secunde trec de la avertismentul atacului pana la atacul propriu-zis
        double beforeAtt;
};