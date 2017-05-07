//
//  State_GameClear.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/7.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef State_GameClear_hpp
#define State_GameClear_hpp

#include "BaseState.hpp"
#include <SFML/Graphics.hpp>

class State_GameClear : public BaseState{
public:
    State_GameClear(StateManager* l_stateManager);
    ~State_GameClear();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();
private:
    sf::Font m_font;
    sf::Text m_text;
    float m_elapsed;
};


#endif /* State_GameClear_hpp */
