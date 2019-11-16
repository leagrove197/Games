//
//  Game.hpp
//  L2AC
//
//  Created by Eris Suryaputra on 12/06/19.
//  Copyright © 2019 Eris Suryaputra. All rights reserved.
//

#ifndef WWG_hpp
#define WWG_hpp

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include "SDL2_ttf/SDL_ttf.h"
#include <random>
#include <iostream>

class WWG {
    int flag;
    bool isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
public:
    WWG();
    ~WWG();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running() { return isRunning; }
    int getFlag() { return flag; }
    
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};

#endif /* WWG_hpp */
