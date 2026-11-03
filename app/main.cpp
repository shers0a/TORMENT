#include <iostream>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>
#include <cmath>
#include "Boss.hpp"
#include "Player.hpp"
#include "Fight.hpp"

using json = nlohmann::json;

namespace{
    json readJson(const std::string& path){
        std::ifstream file(path);
        if(!file){
            throw std::runtime_error("I couldn't open " + path);
        }

        return json::parse(file);
    }

    Stats loadStats(const json& j){
        return Stats(j.at("max_hp").get<double>(),
        j.at("hp").get<double>(),
        j.at("damage").get<double>(),
        j.at("def").get<double>(),
        j.at("spd").get<double>());
    }

    Attack loadAttack(const json& j){
        return Attack(j.at("name").get<std::string>(),
        j.at("damage").get<double>(),
        j.at("cooldown").get<double>(),
        j.at("phase").get<int>(),
        j.at("before_att").get<double>());
    }

    Boss loadBoss(const json& j, std::mt19937::result_type seed){
        std::vector<Attack> attacks;
        for( const auto& attack : j.at("attacks") ){
            attacks.push_back(loadAttack(attack));
        }
        
        return Boss(j.at("name").get<std::string>(),
        attacks,
        loadStats(j.at("stats")),
        j.at("phase2_constant").get<double>(),
        seed);
    }

    Player loadPlayer(const json& j){
        return Player(j.at("name").get<std::string>(),
        loadStats(j.at("stats")),
        j.at("iframe_cooldown").get<double>(),
        j.at("dodge_cooldown").get<double>());
    }
}


int main(){
    try{
        const json fightData = readJson("assets/data/fight.json");
        const double win = fightData.at("vulnerability_window").get<double>(),
                dt = fightData.at("dt").get<double>();
        
        const std::mt19937::result_type seed = fightData.at("seed").get<unsigned>(); //pt ca e randomizerul 

        Boss minos = loadBoss(readJson("assets/data/boss_minos.json"), seed);
        Player player = loadPlayer(readJson("assets/data/player.json"));
        
        std::cout << "!===YOU'RE GOING DOWN===!\n";
        std::cout << minos << "\n";
        std::cout << player << "\n";

        const Boss minosStart = minos;
        const Player playerStart = player;

        bool run = true;
        while(run){
            Fight fight(player, minos, win);

            while(!fight.bossWon() && !fight.playerWon()){
                std::cout << fight << "\n";

                char cmd{};
                double seconds{};

                if(!(std::cin >> cmd >> seconds)){
                    run = false;
                    break;
                }

                switch(cmd){
                    case 'a':
                        std::cout << (fight.playerAttack() ? "!=== HIT ===!\n" : "!=== BOSS IS NOT VULNERABLE ===!") << "\n";
                        break;

                    case 'd':
                        std::cout <<(fight.playerDodge() ? "!=== DODGED ===!" : "!=== DODGE ON COOLDOWN ===!") << "\n";
                        break;

                    case 'w':
                        break;
                        
                    default:
                        std::cout << "!=== UNKNOWN COMMAND ===!" << "\n";
                        break;
                }

                const long ticks = std::lround(seconds / dt);
                for( long i = 0 ; i < ticks && (!fight.bossWon() && !fight.playerWon()); ++i ){
                    fight.update(dt);
                }

            }
            if(fight.playerWon()){
                std::cout << "!=== VICTORY ===!" << "\n";

                run = false;
                break;
            }
            else if(fight.bossWon()){
                std::cout << "!=== YOU LOST ===!" << "\n";
                std::cout << "!=== REMATCH? ===!" << "\n";
                std::cout << "!=== YES OR NO ===!" << "\n";
                std::cout << "!=== ANSWER: ===!" << "\n";

                std::string answer;
                std::cin >> answer;

                if (answer == "YES") {
                    minos = minosStart;
                    player = playerStart;
                } 
                else if (answer == "NO") {
                    std::cout << "!== YOU WERE ALWAYS BOUND TO FAIL ==!" << "\n";
                    run = false;
                    break;
                } 
                else {
                    std::cout << "!=== only YES or NO ===!" << "\n";
                    run = false;
                    break;
                }
            }
        }
    }
    catch(const std::exception& e){
        std::cerr << "Error: " << e.what() << "\n";
        return 1;
    }


    return 0;
}