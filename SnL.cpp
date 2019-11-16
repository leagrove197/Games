//
//  Game.cpp
//  L2AC
//
//  Created by Eris Suryaputra on 12/06/19.
//  Copyright © 2019 Eris Suryaputra. All rights reserved.
//

#include "SnL.hpp"
std::random_device dev;
std::mt19937 rng(dev());
std::uniform_int_distribution<std::mt19937::result_type> dist6(1,6);

SDL_Texture *player1;
SDL_Texture *player2;
SDL_Texture *bgImage;
SDL_Texture *dice1;
SDL_Texture *dice2;
SDL_Texture *dice3;
SDL_Texture *dice4;
SDL_Texture *dice5;
SDL_Texture *dice6;
SDL_Texture *winning;
SDL_Texture *back_button;
SDL_Rect box;
SDL_Rect srcR, destR, srcR1, destR1, destRdice, destRwin;

Mix_Music *music;
Mix_Chunk *win_sound;
Mix_Chunk *diceSound;
Mix_Chunk *ladderSound;
Mix_Chunk *snakeSound;
SnL::SnL() {}
SnL::~SnL() {}

void SnL::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen) {
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
//    else isRunning = false;
    
    Mix_OpenAudio( 22050, MIX_DEFAULT_FORMAT, 2, 4096);
    
    player1 = SnL::LoadTexture("assets/images/player1.png", renderer);
    player2 = SnL::LoadTexture("assets/images/player2.png", renderer);
    bgImage = SnL::LoadTexture("assets/images/bgSnake1.jpg", renderer);
    dice1 = SnL::LoadTexture("assets/images/dice1.png", renderer);
    dice2 = SnL::LoadTexture("assets/images/dice2.png", renderer);
    dice3 = SnL::LoadTexture("assets/images/dice3.png", renderer);
    dice4 = SnL::LoadTexture("assets/images/dice4.png", renderer);
    dice5 = SnL::LoadTexture("assets/images/dice5.png", renderer);
    dice6 = SnL::LoadTexture("assets/images/dice6.png", renderer);
    winning = SnL::LoadTexture("assets/images/win-png--313.png/", renderer);
    back_button = SnL::LoadTexture("assets/images/button_back.png", renderer);
    SDL_SetTextureBlendMode(back_button, SDL_BLENDMODE_BLEND);
    box.h = 64;
    box.w = 64;
    box.x = 0;
    box.y = 0;
    //The music that will be played
    music = Mix_LoadMUS("assets/sound/bgmMusic.mp3");
    Mix_VolumeMusic(64);
    Mix_PlayMusic(music, -1);
    //The sound effects that will be used
    win_sound = Mix_LoadWAV( "assets/sound/win.wav" );
    diceSound = Mix_LoadWAV("assets/sound/dice.mp3");
    ladderSound = Mix_LoadWAV("assets/sound/ladder.mp3");
    snakeSound = Mix_LoadWAV("assets/sound/snake.mp3");
    
}

void SnL::handleEvents() {
    SDL_Event event;
    SDL_PollEvent(&event);
    int x;
    int y;
    switch (event.type) {
        case SDL_QUIT:
            flag = 5;
            isRunning = false;;
            break;
            
        case SDL_MOUSEMOTION:
            x = event.button.x;
            y = event.button.y;
            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                back_button = SnL::LoadTexture("assets/images/button_back_hover.png", renderer);
                Uint8 a = 255;
                SDL_SetTextureAlphaMod(back_button, a);
            }
            else {
                back_button = SnL::LoadTexture("assets/images/button_back.png", renderer);
                Uint8 a = 128;
                SDL_SetTextureAlphaMod(back_button, a);
            }
            break;
            
        case SDL_MOUSEBUTTONDOWN:
            if( event.button.button == SDL_BUTTON_LEFT )
            {
                //Get the mouse offsets
                x = event.button.x;
                y = event.button.y;
                
                //If the mouse is over the button
                if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
                {
                    flag = 0;
                    isRunning = false;
                }
                else if (!rolldice && !endGame) {
                    Mix_VolumeChunk(diceSound, 1024);
                    Mix_PlayChannel(-1, diceSound, 0);
                    dice_number = dist6(rng);
                    //                dice_number = 23;
                    dice_number_leftover = 0;
                    rolldice = true;
                }
            }
            break;
            
        default:
            break;
    }
}

void SnL::update() {
    destR.h = 32;
    destR.w = 32;
    destR.x = p1_x;
    destR.y = p1_y;
    destR1.h = 32;
    destR1.w = 32;
    destR1.x = p2_x;
    destR1.y = p2_y;
    destRdice.h = 128;
    destRdice.w = 128;
    destRdice.x = 230;
    destRdice.y = 240;
    destRwin.h = 500;
    destRwin.w = 500;
    destRwin.x = 40;
    destRwin.y = 30;
    
    if (rolldice)
    {
        if (timer > 1)
        {
            endTurn = false;
            if (counter < dice_number)
            {
                if (p2_turn)
                {
                    if (p2_counter == 10)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = true;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 20)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = false;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 30)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = true;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 40)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = false;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 50)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = true;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 60)
                    {
                        if (i == 60) {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = false;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 70)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = true;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 80)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = false;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 90)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p2_reverse = true;
                            p2_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 100)
                    {
                        win =  true;
                        endGame = true;
                    }
                    else
                    {
                        if (!p2_reverse)
                        {
                            if (p2_x != p2_x+60*(dice_number-dice_number_leftover))
                            {
                                if (i == 60)
                                {
                                    p2_counter++;
                                    counter++;
                                    i = 0;
                                }
                                else
                                {
                                    i++;
                                    p2_x++;
                                }
                            }
                        }
                        else if (p2_reverse)
                        {
                            if (p2_counter == 99)
                            {
                                i++;
                                p2_x--;
                                if (i == 60)
                                {
                                    win = true;
                                    endGame = true;
                                    p2_counter++;
                                    counter++;
                                    i = 0;
                                }
                            }
                            else
                            {
                                if (p2_x != p2_x-60*(dice_number-dice_number_leftover))
                                {
                                    if (i == 60)
                                    {
                                        p2_counter++;
                                        counter++;
                                        i = 0;
                                    }
                                    else
                                    {
                                        i++;
                                        p2_x--;
                                    }
                                }
                            }
                        }
                    }
                }
                else {
                    if (p1_counter == 10)
                    {
                        if (i == 60) {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = true;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 20)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = false;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 30)
                    {
                        if (i == 60) {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = true;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 40)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = false;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 50)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = true;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 60)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = false;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 70)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = true;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 80)
                    {
                        if (i == 60) {
                            
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = false;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 90)
                    {
                        if (i == 60)
                        {
                            dice_number_leftover = dice_number-1 - counter;
                            p1_reverse = true;
                            p1_counter++;
                            counter++;
                            i = 0;
                        }
                        else
                        {
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 100)
                    {
                        win = true;
                        endGame = true;
                    }
                    else {
                        if (!p1_reverse)
                        {
                            if (p1_x != p1_x+60*(dice_number-dice_number_leftover))
                            {
                                if (i == 60)
                                {
                                    p1_counter++;
                                    counter++;
                                    i = 0;
                                }
                                else
                                {
                                    i++;
                                    p1_x++;
                                }
                            }
                        }
                        else if (p1_reverse)
                        {
                            if (p1_counter == 99)
                            {
                                i++;
                                p1_x--;
                                if (i == 60)
                                {
                                    win = true;
                                    endGame = true;
                                    p1_counter++;
                                    counter++;
                                    i = 0;
                                }
                            }
                            else
                            {
                                if (p1_x != p1_x-60*(dice_number-dice_number_leftover))
                                {
                                    if (i == 60)
                                    {
                                        p1_counter++;
                                        counter++;
                                        i = 0;
                                    }
                                    else
                                    {
                                        i++;
                                        p1_x--;
                                    }
                                }
                            }
                        }
                    }
                }
            }
            else {
                if (p2_turn) {
                    if (p2_counter == 8) {
                        Mix_VolumeChunk(ladderSound, 16);
                        Mix_PlayChannel(-1, ladderSound, 1);
                        if (i == 180) {
                            p2_reverse = true;
                            p2_counter = 31;
                            i = 0;
                        }
                        else {
                            if (p2_x <= 554) {
                                p2_x+=0.6;
                            }
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 15) {
                        if (i == 480) {
                            Mix_VolumeChunk(ladderSound, 16);
                            Mix_PlayChannel(-1, ladderSound, 1);
                            p2_reverse = true;
                            p2_counter = 97;
                            i = 0;
                        }
                        else {
                            if (p2_x >= 194) {
                                p2_x-=0.251;
                            }
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 24) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 120) {
                            p2_counter = 1;
                            i = 0;
                        }
                        else {
                            if (p2_x >= 14) {
                                p2_x-=1.5;
                            }
                            i++;
                            p2_y++;
                        }
                    }
                    else if (p2_counter == 42) {
                        Mix_VolumeChunk(ladderSound, 16);
                        Mix_PlayChannel(-1, ladderSound, 1);
                        if (i == 240) {
                            p2_reverse = false;
                            p2_counter = 81;
                            i = 0;
                        }
                        else {
                            if (p2_x >= 14) {
                                p2_x-=0.25;
                            }
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 55) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 240) {
                            p2_reverse = true;
                            p2_counter = 13;
                            i = 0;
                        }
                        else {
                            if (p2_x <= 434) {
                                p2_x+=0.47;
                            }
                            i++;
                            p2_y++;
                        }
                    }
                    else if (p2_counter == 66) {
                        Mix_VolumeChunk(ladderSound, 16);
                        Mix_PlayChannel(-1, ladderSound, 1);
                        if (i == 120) {
                            p2_counter = 87;
                            i = 0;
                        }
                        else {
                            if (p2_x <= 374) {
                                p2_x+=0.44;
                            }
                            i++;
                            p2_y--;
                        }
                    }
                    else if (p2_counter == 71) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 300) {
                            p2_reverse = false;
                            p2_counter = 29;
                            i = 0;
                        }
                        else {
                            if (p2_x >= 484) {
                                p2_x-=0.25;
                            }
                            i++;
                            p2_y++;
                        }
                    }
                    else if (p2_counter == 88) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 120) {
                            p2_reverse = false;
                            p2_counter = 67;
                            i = 0;
                        }
                        else {
                            if (p2_x >= 314) {
                                p2_x-=0.55;
                            }
                            i++;
                            p2_y++;
                        }
                    }
                    else if (p2_counter == 99) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 540) {
                            p2_reverse = false;
                            p2_counter = 6;
                            i = 0;
                        }
                        else {
                            if (p2_x <= 314) {
                                p2_x+=0.43;
                            }
                            i++;
                            p2_y++;
                        }
                    }
                    else {
                        i = 0;
                        counter = 0;
                        rolldice = false;
                        p2_turn = false;
                        endTurn = true;
                        timer = 0;
                    }
                }
                else {
                    if (p1_counter == 8) {
                        Mix_VolumeChunk(ladderSound, 16);
                        Mix_PlayChannel(-1, ladderSound, 1);
                        if (i == 180) {
                            p1_reverse = true;
                            p1_counter = 31;
                            i = 0;
                        }
                        else {
                            if (p1_x <= 554) {
                                p1_x+=0.6;
                            }
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 15) {
                        Mix_VolumeChunk(ladderSound, 16);
                        Mix_PlayChannel(-1, ladderSound, 1);
                        if (i == 480) {
                            p1_reverse = true;
                            p1_counter = 97;
                            i = 0;
                        }
                        else {
                            if (p1_x >= 194) {
                                p1_x-=0.251;
                            }
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 24) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 120) {
                            p1_counter = 1;
                            i = 0;
                        }
                        else {
                            if (p1_x >= 14) {
                                p1_x-=1.5;
                            }
                            i++;
                            p1_y++;
                        }
                    }
                    else if (p1_counter == 42) {
                        Mix_VolumeChunk(ladderSound, 16);
                        Mix_PlayChannel(-1, ladderSound, 1);
                        if (i == 240) {
                            p1_reverse = false;
                            p1_counter = 81;
                            i = 0;
                        }
                        else {
                            if (p1_x >= 14) {
                                p1_x-=0.25;
                            }
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 55) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 240) {
                            p1_reverse = true;
                            p1_counter = 13;
                            i = 0;
                        }
                        else {
                            if (p1_x <= 434) {
                                p1_x+=0.47;
                            }
                            i++;
                            p1_y++;
                        }
                    }
                    else if (p1_counter == 66) {
                        Mix_VolumeChunk(ladderSound, 16);
                        Mix_PlayChannel(-1, ladderSound, 1);
                        if (i == 120) {
                            p1_counter = 87;
                            i = 0;
                        }
                        else {
                            if (p1_x <= 374) {
                                p1_x+=0.44;
                            }
                            i++;
                            p1_y--;
                        }
                    }
                    else if (p1_counter == 71) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 300) {
                            p1_reverse = false;
                            p1_counter = 29;
                            i = 0;
                        }
                        else {
                            if (p1_x >= 484) {
                                p1_x-=0.25;
                            }
                            i++;
                            p1_y++;
                        }
                    }
                    else if (p1_counter == 88) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 120) {
                            p1_reverse = false;
                            p1_counter = 67;
                            i = 0;
                        }
                        else {
                            if (p1_x >= 314) {
                                p1_x-=0.55;
                            }
                            i++;
                            p1_y++;
                        }
                    }
                    else if (p1_counter == 99) {
                        Mix_VolumeChunk(snakeSound, 64);
                        Mix_PlayChannel(-1, snakeSound, 0);
                        if (i == 540) {
                            p1_reverse = false;
                            p1_counter = 6;
                            i = 0;
                        }
                        else {
                            if (p1_x <= 314) {
                                p1_x+=0.43;
                            }
                            i++;
                            p1_y++;
                        }
                    }
                    else {
                        i = 0;
                        counter = 0;
                        rolldice = false;
                        p2_turn = true;
                        endTurn = true;
                        timer = 0;
                    }
                }
            }
        }
        else timer+=0.01;
    }
}

void SnL::render() {
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, bgImage, NULL, NULL);
    SDL_RenderCopy(renderer, player2, NULL, &destR1);
    SDL_RenderCopy(renderer, player1, NULL, &destR);
    SDL_RenderCopy(renderer, back_button, NULL, &box);
    if (win)
    {
        Mix_VolumeChunk(win_sound, 16);
        Mix_PlayChannel(-1, win_sound, 0);
        SDL_RenderCopy(renderer, winning, NULL, &destRwin);
    }
    else if (endTurn){
        SDL_RenderCopy(renderer, dice6, NULL, &destRdice);
        if (dice_number == 1)
        {
            SDL_RenderCopy(renderer, dice1, NULL, &destRdice);
        }
        else if (dice_number == 2)
        {
            SDL_RenderCopy(renderer, dice2, NULL, &destRdice);
        }
        else if (dice_number == 3)
        {
            SDL_RenderCopy(renderer, dice3, NULL, &destRdice);
        }
        else if (dice_number == 4)
        {
            SDL_RenderCopy(renderer, dice4, NULL, &destRdice);
        }
        else if (dice_number == 5)
        {
            SDL_RenderCopy(renderer, dice5, NULL, &destRdice);
        }
        else
        {
            SDL_RenderCopy(renderer, dice6, NULL, &destRdice);
        }
    }
    SDL_RenderPresent(renderer);
}

void SnL::clean() {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    Mix_Quit();
    SDL_Quit();
}

SDL_Texture* SnL::LoadTexture(const char*  texture, SDL_Renderer* ren)
{
    SDL_Surface* tempSurface = IMG_Load(texture);
    SDL_Texture* tex = SDL_CreateTextureFromSurface(ren, tempSurface);
    SDL_FreeSurface(tempSurface);
    
    return tex;
}
