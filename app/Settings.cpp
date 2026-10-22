#include "Settings.hpp"
#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

Settings::Settings(const std::string& path){
    std::ifstream file(path);
    if(!file)
        throw std::runtime_error("I can't open the path" + path);

    json j = json::parse(file);

    const json& win = j.at("window");
    title = win.at("title").get<std::string>();
    width = win.at("width").get<int>();
    height = win.at("height").get<int>();
    fullscreen = win.at("fullscreen").get<bool>();
    vsync = win.at("fullscreen").get<bool>();

    if(width <= 0 ||  height <= 0)
        throw std::runtime_error("Invalid dimension values in " + path);
    
    for( const auto& [action, key] : j.at("keys").items()){
        std::string name = key.get<std::string>();
        SDL_Scancode sc = SDL_GetScancodeFromName(name.c_str());

        if( sc == SDL_SCANCODE_UNKNOWN )
            throw std::runtime_error("Unknown key " + name);
        
            key[action] = sc;
    }
}

SDL_Scancode Settings::getKey(const std::string& action) const{
    auto it = keys.find(action);
    if( it == keys.end() )
        throw std::runtime_error("No action related to this key: " + action);
    
    return it -> second;
}