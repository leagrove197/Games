//
//  Game.cpp
//  L2AC
//
//  Created by Eris Suryaputra on 12/06/19.
//  Copyright © 2019 Eris Suryaputra. All rights reserved.
//

#include "Menu.hpp"

SDL_Texture *menu_bg;
SDL_Texture *logo;
SDL_Texture *menu_play;
SDL_Texture *menu_back;
SDL_Texture *img1, *img2, *img3, *img4;
SDL_Rect img1_rect, img2_rect, img3_rect, img4_rect;
SDL_Rect menu_bg_rect, logo_rect, menu_play_rect, menu_back_rect, game1_rect, game2_rect, game3_rect, game4_rect;
int counter = 0;
bool reached_right = false;
//Mix_Music *music;
//Mix_Chunk *win_sound;

Menu::Menu() {}
Menu::~Menu() {}

void Menu::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        }
        isRunning = true;
    }
    
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    menu_bg = Menu::LoadTexture("assets/images/27d90765290819.5aef9188431e5.jpg", renderer);
    logo = Menu::LoadTexture("assets/images/imageedit_1_7276171393.png", renderer);
    menu_play = Menu::LoadTexture("assets/images/play.png", renderer);
    menu_back = Menu::LoadTexture("assets/images/button_back.png", renderer);
    img1 = Menu::LoadTexture("assets/images/messageImage_1561778407436.jpg", renderer);
    img2 = Menu::LoadTexture("assets/images/messageImage_1561779164500.jpg", renderer);
    img3 = Menu::LoadTexture("assets/images/messageImage_1561779226207.jpg", renderer);
    img4 = Menu::LoadTexture("assets/images/messageImage_1561779261251.jpg", renderer);
    SDL_SetTextureBlendMode(menu_back, SDL_BLENDMODE_BLEND);
    
    menu_bg_rect.h = 1054;
    menu_bg_rect.w = 1920;
    menu_bg_rect.x = 0;
    menu_bg_rect.y = 0;
    
    logo_rect.h = 300;
    logo_rect.w = 300;
    logo_rect.x = 245;
    logo_rect.y = 60;
    
    menu_play_rect.h = 118;
    menu_play_rect.w = 221;
    menu_play_rect.x = 280;
    menu_play_rect.y = 370;
    
    menu_back_rect.h = 64;
    menu_back_rect.w = 64;
    menu_back_rect.x = 10;
    menu_back_rect.y = 10;
    
    img1_rect.h = 210;
    img1_rect.w = 280;
    img1_rect.x = 880;
    img1_rect.y = 80;
    
    img2_rect.h = 210;
    img2_rect.w = 280;
    img2_rect.x = 1260;
    img2_rect.y = 80;
    
    img3_rect.h = 210;
    img3_rect.w = 280;
    img3_rect.x = 880;
    img3_rect.y = 320;
    
    img4_rect.h = 210;
    img4_rect.w = 280;
    img4_rect.x = 1260;
    img4_rect.y = 320;
}

void Menu::handleEvents() {
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
            if ( ( x > menu_back_rect.x ) && ( x < menu_back_rect.x + menu_back_rect.w ) && ( y > menu_back_rect.y ) && ( y < menu_back_rect.y + menu_back_rect.h ) )
            {
                menu_back = Menu::LoadTexture("assets/images/button_back_hover.png", renderer);
                menu_back_rect.h = 80;
                menu_back_rect.w = 80;
                menu_back_rect.x = 4;
                menu_back_rect.y = 4;
                Uint8 a = 255;
                SDL_SetTextureAlphaMod(menu_back, a);
            }
            else if ( ( x > menu_play_rect.x ) && ( x < menu_play_rect.x + menu_play_rect.w ) && ( y > menu_play_rect.y ) && ( y < menu_play_rect.y + menu_play_rect.h ) && counter2 == 0 )
            {
                menu_play_rect.h = 140;
                menu_play_rect.w = 245;
                menu_play_rect.x = 270;
                menu_play_rect.y = 360;
            }
            else {
                menu_back = Menu::LoadTexture("assets/images/button_back.png", renderer);
                menu_back_rect.h = 64;
                menu_back_rect.w = 64;
                menu_back_rect.x = 10;
                menu_back_rect.y = 10;
                Uint8 a = 255;
                SDL_SetTextureAlphaMod(menu_back, a);
                
                if (counter2 == 0) {
                    menu_play_rect.h = 118;
                    menu_play_rect.w = 221;
                    menu_play_rect.x = 280;
                    menu_play_rect.y = 370;
                }
            }
            break;
            
        case SDL_MOUSEBUTTONDOWN:
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                //Get the mouse offsets
                x = event.button.x;
                y = event.button.y;
                
                //If the mouse is over the button
                if( ( x > menu_back_rect.x ) && ( x < menu_back_rect.x + menu_back_rect.w ) && ( y > menu_back_rect.y ) && ( y < menu_back_rect.y + menu_back_rect.h ) )
                {
                    if (right_page) {
                        right_page = false;
                    }
                    else {
                        flag = 5;
                        isRunning = false;
                    }
                }
                else if ( ( x > menu_play_rect.x ) && ( x < menu_play_rect.x + menu_play_rect.w ) && ( y > menu_play_rect.y ) && ( y < menu_play_rect.y + menu_play_rect.h ) )
                {
                    right_page = true;
                }
                else if ( ( x > img1_rect.x ) && ( x < img1_rect.x + img1_rect.w ) && ( y > img1_rect.y ) && ( y < img1_rect.y + img1_rect.h ) )
                {
                    flag = 1;
                    isRunning = false;
                }
                else if ( ( x > img2_rect.x ) && ( x < img2_rect.x + img1_rect.w ) && ( y > img2_rect.y ) && ( y < img2_rect.y + img2_rect.h ) )
                {
                    flag = 2;
                    isRunning = false;
                }
                else if ( ( x > img3_rect.x ) && ( x < img3_rect.x + img3_rect.w ) && ( y > img3_rect.y ) && ( y < img3_rect.y + img3_rect.h ) )
                {
                    flag = 3;
                    isRunning = false;
                }
                else if ( ( x > img4_rect.x ) && ( x < img4_rect.x + img4_rect.w ) && ( y > img4_rect.y ) && ( y < img4_rect.y + img4_rect.h ) )
                {
                    flag = 4;
                    isRunning = false;
                }
            }
            break;
            
        default:
            break;
    }
}

void Menu::update() {
    if (counter == 0) {
        reached_right = false;
    }
    else if (counter == 1120){
        reached_right = true;
    }
    if (!reached_right) {
        counter++;
        menu_bg_rect.x--;
    }
    else {
        counter--;
        menu_bg_rect.x++;
    }
    if (right_page) {
        if (counter2 != 800){
            counter2+=20;
            menu_play_rect.x-=20;
            logo_rect.x-=20;
            img1_rect.x-=20;
            img2_rect.x-=20;
            img3_rect.x-=20;
            img4_rect.x-=20;
        }
    }
    else if (counter2 != 0) {
        counter2-=20;
        menu_play_rect.x+=20;
        logo_rect.x+=20;
        img1_rect.x+=20;
        img2_rect.x+=20;
        img3_rect.x+=20;
        img4_rect.x+=20;
    }
}

void Menu::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, menu_bg, NULL, &menu_bg_rect);
    SDL_RenderCopy(renderer, logo, NULL, &logo_rect);
    SDL_RenderCopy(renderer, menu_play, NULL, &menu_play_rect);
    SDL_RenderCopy(renderer, menu_back, NULL, &menu_back_rect);
    SDL_RenderCopy(renderer, img1, NULL, &img1_rect);
    SDL_RenderCopy(renderer, img2, NULL, &img2_rect);
    SDL_RenderCopy(renderer, img3, NULL, &img3_rect);
    SDL_RenderCopy(renderer, img4, NULL, &img4_rect);
    
//    Mix_VolumeChunk(win_sound, 16);
//    Mix_PlayChannel(-1, win_sound, 0);
    
    SDL_RenderPresent(renderer);
}

void Menu::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_Quit();
    SDL_Quit();
}

SDL_Texture* Menu::LoadTexture(const char*  texture, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return tex;
}
