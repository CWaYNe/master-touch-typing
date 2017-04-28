//
//  Game.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/26.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Window.hpp"
#include "EventManager.hpp"
#include "StateManager.hpp"
#include "SharedContext.hpp"

class Game{
public:
    Game();
    ~Game();
    
//    void HandleInput();
    void Update();
    void Render();
    Window* GetWindow();
    
    sf::Time GetElapsed();
    
    void MoveSprite(EventDetails* l_details);
    
    void LateUpdate();
private:
//    void MoveMushroom();
    Window m_window;
    SharedContext m_context;
    
    sf::Clock m_clock;
    sf::Time m_elapsed;
    
    sf::Texture m_texture;
    sf::Sprite m_sprite;
    
    StateManager m_stateManager;
    void RestartClock();
};

#endif /* Game_hpp */
