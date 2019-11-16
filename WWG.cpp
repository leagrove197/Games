//
//  Game.cpp
//  L2AC
//
//  Created by Eris Suryaputra on 12/06/19.
//  Copyright © 2019 Eris Suryaputra. All rights reserved.
//

#include "WWG.hpp"

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> random_num(1,7);

SDL_Texture *wwg_bg;
SDL_Texture *wwg_bg1, *wwg_bg2;

TTF_Font* Font; //this opens a font style and sets a size
SDL_Color White;  // this is the color in rgb format, maxing out all would give you the color white, and it will be your text's color

SDL_Surface *stext; // as TTF_RenderText_Solid could only be used on SDL_Surface then you have to create the surface first

SDL_Texture *text, *wwg_back; //now you can convert it into a texture
SDL_Rect text_rect, wwg_back_rect; //create a rect

int phase = 5;
double milisecond, second;
bool penalty = false;
bool left = false;
bool right = false;

//Mix_Music *music;
//Mix_Chunk *win_sound;

WWG::WWG() {}
WWG::~WWG() {}

void WWG::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
        }
        isRunning = true;
    }
    
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);
    TTF_Init();
    
    wwg_bg = WWG::LoadTexture("assets/images/New-Project.jpg", renderer);
    Font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 64);
    White = {255, 255, 255};
    stext = TTF_RenderText_Solid(Font, "Get Ready!", White);
    
    text = SDL_CreateTextureFromSurface(renderer, stext);
    text_rect.x = 180;  //controls the rect's x coordinate
    text_rect.y = 240; // controls the rect's y coordinte
    text_rect.w = 450; // controls the width of the rect
    text_rect.h = 100; // controls the height of the rect
    
    wwg_back = WWG::LoadTexture("assets/images/button_back.png", renderer);
    SDL_SetTextureBlendMode(wwg_back, SDL_BLENDMODE_BLEND);
    wwg_back_rect.h = 64;
    wwg_back_rect.w = 64;
    wwg_back_rect.x = 0;
    wwg_back_rect.y = 0;
}

void WWG::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    int x, y;
    switch (event.type) {
        case SDL_QUIT:
            flag = 5;
            isRunning = false;;
            break;
        
        case SDL_MOUSEMOTION:
            x = event.button.x;
            y = event.button.y;
            if ( ( x > wwg_back_rect.x ) && ( x < wwg_back_rect.x + wwg_back_rect.w ) && ( y > wwg_back_rect.y ) && ( y < wwg_back_rect.y + wwg_back_rect.h ) )
            {
                wwg_back = WWG::LoadTexture("assets/images/button_back_hover.png", renderer);
                Uint8 a = 255;
                SDL_SetTextureAlphaMod(wwg_back, a);
            }
            else {
                wwg_back = WWG::LoadTexture("assets/images/button_back.png", renderer);
                Uint8 a = 128;
                SDL_SetTextureAlphaMod(wwg_back, a);
            }
            break;
            
        case SDL_MOUSEBUTTONDOWN:
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                //Get the mouse offsets
                x = event.button.x;
                y = event.button.y;
                
                //If the mouse is over the button
                if( ( x > wwg_back_rect.x ) && ( x < wwg_back_rect.x + wwg_back_rect.w ) && ( y > wwg_back_rect.y ) && ( y < wwg_back_rect.y + wwg_back_rect.h ) )
                {
                    flag = 0;
                    isRunning = false;
                }
            }
            break;
            
        case SDL_KEYDOWN:
            switch( event.key.keysym.sym ){
                    
                case SDLK_a:
                    if (phase != 0) {
                        penalty = true;
                        left = true;
                    }
                    if (phase == 0 && !left && !right) {
                        left = true;
                    }
                    break;
                    
                case SDLK_l:
                    if (phase != 0) {
                        penalty = true;
                        right = true;
                    }
                    if (phase == 0 && !left && !right) {
                        right = true;
                    }
                    break;
                    
                default:
                    break;
            }
            break;
            
        default:
            break;
    }
}

void WWG::update() {
    milisecond += 1.5;
    if (milisecond > 99) {
        second++;
//        printf("%f second has passed.", second);
        milisecond = 0;
    }
    if (penalty) {
        if (second == 2) {
            phase = 5;
            second = 0;
            left = false;
            right = false;
            penalty = false;
        }
    }
    else if (left || right) {
        if (second == 4) {
            left = false;
            right = false;
            phase = 5;
            second = 0;
        }
    }
    else {
        if (phase == 4) {
            if (second == 3) {
                phase--;
                second = 0;
            }
        }
        if (phase == 1) {
            if (second == random_num(gen)) {
                phase--;
            }
        }
        if (phase == 0) {}
        else {
            if (second == 1) {
                phase--;
                second = 0;
            }
        }
    }
}

void WWG::render() {
    SDL_RenderClear(renderer);
//    SDL_RenderCopy(renderer, wwg_bg, NULL, NULL);
    SDL_RenderCopy(renderer, wwg_back, NULL, &wwg_back_rect);
    if (penalty) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        if (left) {
            stext = TTF_RenderText_Solid(Font, "Player 1 Violated!", White);
            text = SDL_CreateTextureFromSurface(renderer, stext);
            text_rect.x = 30;  //controls the rect's x coordinate
            text_rect.y = 240; // controls the rect's y coordinte
            text_rect.w = 750; // controls the width of the rect
            text_rect.h = 100; // controls the height of the rect
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
        }
        else if (right) {
            stext = TTF_RenderText_Solid(Font, "Player 2 Violated!", White);
            text = SDL_CreateTextureFromSurface(renderer, stext);
            text_rect.x = 30;  //controls the rect's x coordinate
            text_rect.y = 240; // controls the rect's y coordinte
            text_rect.w = 750; // controls the width of the rect
            text_rect.h = 100; // controls the height of the rect
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
        }
    }
    else if (left) {
        SDL_SetRenderDrawColor(renderer, 255, 64, 64, 255);
        stext = TTF_RenderText_Solid(Font, "Player 1 Win!", White);
        text = SDL_CreateTextureFromSurface(renderer, stext);
        text_rect.x = 150;  //controls the rect's x coordinate
        text_rect.y = 240; // controls the rect's y coordinte
        text_rect.w = 550; // controls the width of the rect
        text_rect.h = 100; // controls the height of the rect
        SDL_RenderCopy(renderer, text, NULL, &text_rect);
    }
    else if (right) {
        SDL_SetRenderDrawColor(renderer, 64, 64, 255, 255);
        stext = TTF_RenderText_Solid(Font, "Player 2 Win!", White);
        text = SDL_CreateTextureFromSurface(renderer, stext);
        text_rect.x = 150;  //controls the rect's x coordinate
        text_rect.y = 240; // controls the rect's y coordinte
        text_rect.w = 550; // controls the width of the rect
        text_rect.h = 100; // controls the height of the rect
        SDL_RenderCopy(renderer, text, NULL, &text_rect);
    }
    else {
        SDL_SetRenderDrawColor(renderer, 255, 128, 0, 255);
        if (phase == 4) {
            SDL_RenderCopy(renderer, wwg_bg, NULL, NULL);
            stext = TTF_RenderText_Solid(Font, "Get Ready!", White);
            text = SDL_CreateTextureFromSurface(renderer, stext);
            text_rect.x = 180;  //controls the rect's x coordinate
            text_rect.y = 240; // controls the rect's y coordinte
            text_rect.w = 450; // controls the width of the rect
            text_rect.h = 100; // controls the height of the rect
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
        }
        if (phase == 3) {
            stext = TTF_RenderText_Solid(Font, "3", White);
            text = SDL_CreateTextureFromSurface(renderer, stext);
            text_rect.x = 380;  //controls the rect's x coordinate
            text_rect.y = 240; // controls the rect's y coordinte
            text_rect.w = 50; // controls the width of the rect
            text_rect.h = 100; // controls the height of the rect
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
        }
        if (phase == 2) {
            stext = TTF_RenderText_Solid(Font, "2", White);
            text = SDL_CreateTextureFromSurface(renderer, stext);
            text_rect.x = 380;  //controls the rect's x coordinate
            text_rect.y = 240; // controls the rect's y coordinte
            text_rect.w = 50; // controls the width of the rect
            text_rect.h = 100; // controls the height of the rect
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
        }
        if (phase == 1) {
            stext = TTF_RenderText_Solid(Font, "1", White);
            text = SDL_CreateTextureFromSurface(renderer, stext);
            text_rect.x = 380;  //controls the rect's x coordinate
            text_rect.y = 240; // controls the rect's y coordinte
            text_rect.w = 50; // controls the width of the rect
            text_rect.h = 100; // controls the height of the rect
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
        }
        if (phase == 0) {
            SDL_SetRenderDrawColor(renderer, 64, 255, 64, 255);
            stext = TTF_RenderText_Solid(Font, "GO!", White);
            text = SDL_CreateTextureFromSurface(renderer, stext);
            text_rect.x = 320;  //controls the rect's x coordinate
            text_rect.y = 240; // controls the rect's y coordinte
            text_rect.w = 170; // controls the width of the rect
            text_rect.h = 100; // controls the height of the rect
            SDL_RenderCopy(renderer, text, NULL, &text_rect);
        }
    }
//    Mix_VolumeChunk(win_sound, 16);
//    Mix_PlayChannel(-1, win_sound, 0);
    
    SDL_RenderPresent(renderer);
}

void WWG::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_Quit();
    SDL_Quit();
}

SDL_Texture* WWG::LoadTexture(const char*  texture, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return tex;
}
