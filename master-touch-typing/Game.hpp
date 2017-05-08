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
#include "TextureManager.hpp"
#include "EntityManager.hpp"
#include "PlatformEntityManager.hpp"

class Game{
public:
    Game();
    ~Game();
    
    void Update();
    void Render();
    void LateUpdate();
    
    sf::Time GetElapsed();
    
    Window* GetWindow();
private:
    void RestartClock();
    
    sf::Clock m_clock;
    sf::Time m_elapsed;
    Window m_window;
    SharedContext m_context;
    EntityManager m_entityManager;
    PlatformEntityManager m_platformEntityManager;
    TextureManager m_textureManager;
    StateManager m_stateManager;
};

#endif /* Game_hpp */
