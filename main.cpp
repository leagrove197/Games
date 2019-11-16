//
//  main.cpp
//  L2AC
//
//  Created by Eris Suryaputra on 12/06/19.
//  Copyright © 2019 Eris Suryaputra. All rights reserved.
//

#include "Menu.hpp"
#include "SnL.hpp"
#include "WWG.hpp"
#include "RI.hpp"
#include "SK.hpp"

using namespace std;

// Data Structure.
template <class T>
struct Node{
    const char *name;
    int width, height;
    Node(string name, int width, int height){
        this->name = name.c_str();
        this->width = width;
        this->height = height;
    }
    T *game = nullptr;
    Node<SnL> *game1;
    Node<WWG> *game2;
    Node<RI> *game3;
    Node<SK> *game4;
    Node<Menu> *prev = nullptr;
};

const int FPS = 60;
int frameDelay = 2000.0f / FPS;

template <typename T>
void run_game(T *game){
    
    Uint32 frameStart, frameTime;
    game->game->init(game->name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, game->width, game->height, false);
    while (game->game->running()) {
        
        frameStart = SDL_GetTicks();
        
        game->game->handleEvents();
        game->game->update();
        game->game->render();
        
        frameTime = SDL_GetTicks() - frameStart;
        
        if(frameTime < frameDelay) {
            SDL_Delay((int)(frameDelay - frameTime));
        }
    }
    game->game->clean();
    
    switch (game->game->getFlag()) {
        case 0:
            frameDelay = 2000.0f / FPS;
            game->prev->game->counter2 = 0;
            game->prev->game->right_page = false;
            run_game(game->prev);
            break;
            
        case 1:
            frameDelay = 500.0f / FPS;
            game->game1->game = new SnL();
            run_game(game->game1);
            break;
            
        case 2:
            frameDelay = 1000.0f / FPS;
            game->game2->game = new WWG();
            run_game(game->game2);
            break;
            
        case 3:
            game->game3->game = new RI();
            run_game(game->game3);
            break;
            
        case 4:
            game->game4->game = new SK();
            run_game(game->game4);
            break;
            
        case 5:
            break;
            
        default:
            break;
    }
}

int main() {
//    Menu_node *start = new Menu_node();
//
//    Node<SnL, Menu_node> *game1 = new Node<SnL, Menu_node>();
//    game1->prev = start;
//    start->game1 = game1;
//
//    start->menu = new Menu();
//    run_game(start);
//    game1->game = new SnL();
//    run_game(game1, "Snake and Ladder", 587, 608);
    
    Node<Menu> *start = new Node<Menu>("Main Menu", 800, 600);
    start->game = new Menu();
    
    Node<SnL> *game1 = new Node<SnL>("Snake and Ladder", 587, 608);
    game1->prev = start;
    start->game1 = game1;
    
    Node<WWG> *game2 = new Node<WWG>("Wild West Gun", 800, 600);
    game2->prev = start;
    start->game2 = game2;
    
    Node<RI> *game3 = new Node<RI>("Racoon Island", 800, 600);
    game3->prev = start;
    start->game3 = game3;
    
    Node<SK> *game4 = new Node<SK>("Sneak Ninja", 800, 600);
    game4->prev = start;
    start->game4 = game4;
    
    run_game(start);
    
    return 0;
}
