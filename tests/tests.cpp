// assert() disappears when NDEBUG is defined (Release, RelWithDebInfo): keep the checks on in every build type.
#undef NDEBUG
#include <cassert>

#include "Stats.hpp"
#include "Attack.hpp"
#include "Boss.hpp"
#include "Player.hpp"
#include "Fight.hpp"

int main() {
    //damageTaken cu def mai mare decar damage ul nu schimba HP ul

    {
        Stats stats(100, 100, 15.0, 20.0, 1);

        stats.damageTaken(15);
        assert(stats.getHp() == 100);
    }

    //damageTaken mai mare decât HP-ul îl lasă pe 0, nu negativ
    
    {
        Stats stats(100, 100, 15.0, 20.0, 1);
        
        stats.damageTaken(130);
        assert(stats.getHp() == 0);
    }

    //dodge() a doua oară, în timpul cooldown-ului, întoarce false
    
    {
        Stats stats(100, 100, 15.0, 20.0, 1);
        Player player("player1", stats, 0.3, 1);

        bool dodge = player.dodge();
        assert(dodge);

        dodge = player.dodge();

        assert(!dodge); // vrem sa fie false asa ca verific daca negatia este true
    }

    //Attack: după use(), finishedCooldown() e false; după update(cooldown) e true

    {
        Attack attack("attack_name", 10.0, 1.0, 1, 0.5);
        attack.use();
        
        assert(!attack.finishedCooldown());
        
        attack.update(1.0);

        assert(attack.finishedCooldown());
    }

    //Boss cu seed fix: chooseAttack() întoarce un atac din faza curentă
    
   {
    std::vector<Attack> attacks;

        attacks.emplace_back("attack1", 10.0, 1.0, 1, 0.5);
        attacks.emplace_back("attack2", 5.0, 0.5, 2, 0.25);

        Stats stats(100, 100, 15.0, 20.0, 1);
        Boss boss("boss_name", attacks, stats, 0.25, 30);

        
        assert(boss.currentPhase() == 1);

        const Attack* chosen = boss.chooseAttack();

        assert(chosen != nullptr);

        assert(chosen->isAvailableInPhase(boss.currentPhase()));
    }
    return 0;
}
