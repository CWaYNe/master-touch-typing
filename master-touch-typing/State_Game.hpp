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
#include "RoundedRectangleShape.hpp"
#include "Keyboard.hpp"


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
    void PressedLShift(EventDetails* l_details);
    void PressedRShift(EventDetails* l_details);
    
private:
    // Custom callback
    void AddTypingCallback();
    void RemoveTypingCallback();
    
    
    bool m_correct;
    float m_shakeTimer;
    const float PI;
    
    sf::Sprite m_background;
    sf::Sprite m_info;
    sf::Sprite m_battleSprite;
    
    
    std::string m_defaultText;
    std::string m_userInputs;
    std::vector<std::string> m_english_words;
    std::vector<std::string>::iterator it;
    
    sf::Vector2f defaultScale;
    sf::Font m_font;
    sf::Text m_text;
    sf::Text m_word;
    

    
    Keyboard* m_keyboard;
    
};

#endif /* State_Game_hpp */
