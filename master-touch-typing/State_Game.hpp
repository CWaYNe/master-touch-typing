//
//  State_Game.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/4.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef State_Game_hpp
#define State_Game_hpp

#include "BaseState.hpp"
#include "EventManager.hpp"

class State_Game : public BaseState{
public:
    State_Game(StateManager* l_stateManager);
    ~State_Game();
    
    void OnCreate();
    void OnDestroy();
    
    void Activate();
    void Deactivate();
    
    void Update(const sf::Time& l_time);
    void Draw();
    
    void ToggleOverlay(EventDetails* l_details);
    void MainMenu(EventDetails* l_details);
    void Pause(EventDetails* l_details);
    void KeyPressed(EventDetails* l_details);
    void EnterKeyPressed(EventDetails* l_details);
    
private:
    // Custom callback
    void AddTypingCallback();
    void RemoveTypingCallback();
    
    bool m_correct;
    
    std::string m_defaultText;
    std::string m_userInputs;
    std::vector<std::string> m_english_words;
    std::vector<std::string>::iterator it;
    
    sf::Font m_font;
    sf::Text m_text;
    sf::Text m_word;
    
};

#endif /* State_Game_hpp */
