//
//  State_Paused.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/29.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef State_Paused_hpp
#define State_Paused_hpp

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_Paused : public BaseState{
public:
    State_Paused(StateManager* l_stateManager);
    ~State_Paused();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();
    
    void Unpause(EventDetails* l_details);
private:
    sf::Font m_font;
    sf::Text m_text;
    sf::RectangleShape m_rect;
};
#endif /* State_Paused_hpp */
