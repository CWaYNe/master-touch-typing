//
//  State_MainMenu.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/28.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "State_MainMenu.hpp"
#include "StateManager.hpp" // forward declaration in BaseState


State_MainMenu::State_MainMenu(StateManager* l_stateManager)
: BaseState(l_stateManager){}

State_MainMenu::~State_MainMenu(){}

void State_MainMenu::OnCreate(){
    sf::Vector2u windowSize = m_stateMgr->GetContext()
    ->m_wind->GetRenderWindow()->getSize();
    
    m_font.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setString(sf::String("MAIN MENU:"));
    m_text.setCharacterSize(48);
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f,
                     textRect.top + textRect.height / 2.0f);
    
    m_text.setPosition(windowSize.x / 2.0f,windowSize.y / 3.8f);
    
    m_buttonSize = sf::Vector2f(300.0f,32.0f);
    m_buttonPos = sf::Vector2f(windowSize.x / 2.0f,windowSize.y / 3.0f);
    m_buttonPadding = 4; // 4px.
    
//    std::string str[3];
    sf::String str[3];
    str[0] = "PLAY";
    str[1] = "CREDITS";
    str[2] = "EXIT";
    
    for(int i = 0; i < 3; ++i){
        sf::Vector2f buttonPosition(
                                    m_buttonPos.x,m_buttonPos.y +
                                    (i * (m_buttonSize.y + m_buttonPadding)));
        m_rects[i].setSize(m_buttonSize);
        m_rects[i].setFillColor(sf::Color::Red);
        
        m_rects[i].setOrigin(
                             m_buttonSize.x / 2.0f, m_buttonSize.y / 2.0f);
        m_rects[i].setPosition(buttonPosition);
        
        m_labels[i].setFont(m_font);
        m_labels[i].setString(str[i]);
        m_labels[i].setCharacterSize(12);
        
        sf::FloatRect rect = m_labels[i].getLocalBounds();
        m_labels[i].setOrigin(
                              rect.left + rect.width / 2.0f,
                              rect.top + rect.height / 2.0f);
        
        m_labels[i].setPosition(buttonPosition);
    }
    
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::MainMenu, "Mouse_Left",&State_MainMenu::MouseClick,this);
//    AddTypingCallback();
}


void State_MainMenu::OnDestroy(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::MainMenu, "Mouse_Left");
//    RemoveTypingCallback();
}

void State_MainMenu::AddTypingCallback(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    std::string Key = "Key_";
    for(char a='A'; a < 'A' + 24; ++a){
        evMgr->AddCallback(StateType::MainMenu, Key + a, &State_MainMenu::KeyPressed, this);
    }
    evMgr->AddCallback(StateType::MainMenu, "Key_Space", &State_MainMenu::SpaceKeyPressed, this);
    evMgr->AddCallback(StateType::MainMenu, "Key_Enter", &State_MainMenu::EnterKeyPressed, this);
}

void State_MainMenu::RemoveTypingCallback(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    std::string Key = "Key_";
    for(char a='A'; a < 'A' + 24; ++a){
        evMgr->RemoveCallback(StateType::MainMenu, Key + a);
    }
    evMgr->RemoveCallback(StateType::MainMenu, "Key_Space");
    evMgr->RemoveCallback(StateType::MainMenu, "Key_Enter");
}

void State_MainMenu::KeyPressed(EventDetails* l_details){
    std::cout << char('a' + l_details->m_keyCode) << " KeyPressed" << std::endl;
}

void State_MainMenu::SpaceKeyPressed(EventDetails* l_details){
    std::cout << "Space key pressed" << std::endl;
}

void State_MainMenu::EnterKeyPressed(EventDetails* l_details){
    std::cout << "Enter key pressed" << std::endl;
}

void State_MainMenu::Activate(){
    if (m_stateMgr->HasState(StateType::Game)
        && m_labels[0].getString() != "RESUME")
    {
        m_labels[0].setString(sf::String("RESUME"));
    } else {
        m_labels[0].setString(sf::String("PLAY"));
    }
    
    sf::FloatRect rect = m_labels[0].getLocalBounds();
    m_labels[0].setOrigin(rect.left + rect.width / 2.0f,
                          rect.top + rect.height / 2.0f);
}

void State_MainMenu::MouseClick(EventDetails* l_details){
    SharedContext* context = m_stateMgr->GetContext();
    sf::Vector2i mousePos = l_details->m_mouse;
    
    float halfX = m_buttonSize.x / 2.0f;
    float halfY = m_buttonSize.y / 2.0f;
    for(int i = 0; i < 3; ++i){
        if(mousePos.x>=m_rects[i].getPosition().x - halfX &&
           mousePos.x<=m_rects[i].getPosition().x + halfX &&
           mousePos.y>=m_rects[i].getPosition().y - halfY &&
           mousePos.y<=m_rects[i].getPosition().y + halfY)
        {
            if(i == 0){
                m_stateMgr->SwitchTo(StateType::Game);
            } else if(i == 1){
                // Credits state.
            } else if(i == 2){
                m_stateMgr->GetContext()->m_wind->Close();
            }
        }
    }
}

void State_MainMenu::Draw(){
    sf::RenderWindow* window = m_stateMgr->
    GetContext()->m_wind->GetRenderWindow();
    window->draw(m_text);
    for(int i = 0; i < 3; ++i){
        window->draw(m_rects[i]);
        window->draw(m_labels[i]);
    }
}

void State_MainMenu::Update(const sf::Time& l_time){}
void State_MainMenu::Deactivate(){}
