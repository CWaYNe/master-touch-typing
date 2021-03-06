//
//  State_Game.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/29.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef State_Game2_hpp
#define State_Game2_hpp

#include "BaseState.hpp"
#include "EventManager.hpp"
#include "Map.hpp"

class State_Game2 : public BaseState{
public:
    State_Game2(StateManager* l_stateManager);
    ~State_Game2();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();
    
    void ToggleOverlay(EventDetails* l_details);
    void MainMenu(EventDetails* l_details);
    void Pause(EventDetails* l_details);
private:
    Map* m_gameMap;
};

#endif /* State_Game_hpp */
