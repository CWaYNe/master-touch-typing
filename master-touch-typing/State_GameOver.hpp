//
//  State_GameOver.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/2.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef State_GameOver_hpp
#define State_GameOver_hpp

#include "BaseState.hpp"
#include <SFML/Graphics.hpp>

class State_GameOver : public BaseState{
public:
    State_GameOver(StateManager* l_stateManager);
    ~State_GameOver();
    
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

#endif /* State_GameOver_hpp */
