//
//  SharedContext.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/27.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef SharedContext_h
#define SharedContext_h

#include "Window.hpp"
#include "EventManager.hpp"
#include "TextureManager.hpp"
#include "EntityManager.hpp"
#include "DebugOverlay.hpp"

// keeps the pointer to the main window class and event manager

class Map;

struct SharedContext{
    SharedContext():
        m_wind(nullptr),
        m_eventManager(nullptr),
        m_textureManager(nullptr),
        m_entityManager(nullptr),
        m_gameMap(nullptr){};
    
    Window* m_wind;
    EventManager* m_eventManager;
    TextureManager* m_textureManager;
    EntityManager* m_entityManager;
    Map* m_gameMap;
    DebugOverlay m_debugOverlay;
};

#endif /* SharedContext_h */
