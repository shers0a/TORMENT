#pragma once
#include <string>
#include <SDL3/SDL.h>

class Settings{
    public:
        explicit Settings(const std::string& path);

        const std::string& getTitle() const {return title;}
        int getWidth() const {return width;}
        int getHeight() const {return height;}
        
        bool isFullscreen()  const { return fullscreen; }
        bool isVsync()       const { return vsync; }

        SDL_Scancode getKey(const std::string& action) const;

    private:
        std::string title;
        int width;
        int height;

        bool fullscreen;
        bool vsync;
        std::unordered_map<std::string, SDL_Scancode> keys;
};