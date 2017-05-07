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
#include "Platform.hpp"


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
    void LoadGameData(const std::string& l_dataFile);
    
    bool m_correct;
    float m_shakeTimer;
    float m_correctTimer;
    const float PI;
    
    sf::Vector2f m_wordBoxPos;
    sf::Vector2f m_inputBoxPos;
    sf::Vector2f m_boxSize;
    
    sf::RoundedRectangleShape m_WordBox;
    sf::RoundedRectangleShape m_InputBox;
    
    sf::Sprite m_background;
    sf::Sprite m_info;
    sf::Sprite m_great;
    
    std::wstring m_defaultText;
    std::wstring m_userInputs;
    
    std::unordered_map<std::wstring, std::wstring> m_vocabulary;
    std::unordered_map<std::wstring, std::wstring>::iterator itr2;
    
    
    sf::Vector2f m_defaultScale;
    sf::Font m_font;
    sf::Text m_text; // user input box
    sf::Text m_word; // vocabulary box
    
    

    Platform* m_gamePlatform;
    Keyboard* m_keyboard;
    
};

#endif /* State_Game_hpp */
