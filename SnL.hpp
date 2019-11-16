//
//  Game.hpp
//  L2AC
//
//  Created by Eris Suryaputra on 12/06/19.
//  Copyright © 2019 Eris Suryaputra. All rights reserved.
//

#ifndef SnL_hpp
#define SnL_hpp

#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "SDL2_mixer/SDL_mixer.h"
#include <random>
#include <iostream>

class SnL {
    int flag;
    int counter = 0, p1_counter = 1, p2_counter = 1;
    int i = 0, dice_number = 0, dice_number_leftover = 0;
    double timer = 0;
    bool p1_reverse = false, p2_reverse = false;
    bool rolldice = false;
    bool p1_turn = true, p2_turn = false;
    double p1_x = 14, p1_y = 565, p2_x =14 , p2_y =565;
    bool isRunning;
    bool endTurn = true;
    bool win = false;
    bool endGame = false;
    SDL_Window *window;
    SDL_Renderer *renderer;
    
public:
    SnL();
    ~SnL();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running() { return isRunning; }
    int getFlag() { return flag; }
    
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};

#endif /* SnL_hpp */
