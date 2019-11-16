//
//  Game.hpp
//  L2AC
//
//  Created by Eris Suryaputra on 12/06/19.
//  Copyright © 2019 Eris Suryaputra. All rights reserved.
//

#ifndef RI_hpp
#define RI_hpp

#include <iostream>

class RI {
    int flag = 0;
    bool isRunning = true;
    
public:
    RI();
    ~RI();
    
    void init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();
    
    bool running() { return isRunning; }
    int getFlag() { return flag; }
};

#endif /* RI_hpp */
