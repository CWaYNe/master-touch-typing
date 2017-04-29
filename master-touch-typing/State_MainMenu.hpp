//
//  State_MainMenu.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/28.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef State_MainMenu_hpp
#define State_MainMenu_hpp

#include "BaseState.hpp"
#include "EventManager.hpp"


class State_MainMenu : public BaseState {
public:
    State_MainMenu(StateManager* l_stateManager);
    ~State_MainMenu();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();

    void MouseClick(EventDetails* l_details);
private:
    sf::Text m_text;
    sf::Font m_font;
    
    sf::Vector2f m_buttonSize;
    sf::Vector2f m_buttonPos;
    unsigned int m_buttonPadding;
    
    sf::RectangleShape m_rects[3];
    sf::Text m_labels[3];
};

#endif /* State_MainMenu_hpp */
