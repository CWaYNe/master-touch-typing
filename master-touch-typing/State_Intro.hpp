//
//  State_Intro.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/29.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef State_Intro_hpp
#define State_Intro_hpp

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_Intro : public BaseState{
public:
    State_Intro(StateManager* l_stateManager);
    ~State_Intro();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();
    
    void Continue(EventDetails* l_details);
private:
    sf::Sprite m_introSprite;
    sf::Font m_font;
    sf::Text m_text;
};

#endif //State_Intro_hpp
