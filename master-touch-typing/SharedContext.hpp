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

// keeps the pointer to the main window class and event manager

struct SharedContext{
    SharedContext(): m_wind(nullptr), m_eventManager(nullptr){};
    Window* m_wind;
    EventManager* m_eventManager;
};

#endif /* SharedContext_h */
