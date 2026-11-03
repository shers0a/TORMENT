// assert() disappears when NDEBUG is defined (Release, RelWithDebInfo): keep the checks on in every build type.
#undef NDEBUG
#include <cassert>

#include "Stats.hpp"
#include "Attack.hpp"
#include "Boss.hpp"
#include "Player.hpp"
#include "Fight.hpp"

int main() {
    // TODO: assert-uri pe interfața publică, de exemplu:
    //   - damageTaken cu def mai mare decât damage-ul nu schimbă HP-ul
    //   - damageTaken mai mare decât HP-ul îl lasă pe 0, nu negativ
    //   - dodge() a doua oară, în timpul cooldown-ului, întoarce false
    //   - Attack: după use(), finishedCooldown() e false; după update(cooldown) e true
    //   - Boss cu seed fix: chooseAttack() întoarce un atac din faza curentă
    return 0;
}
