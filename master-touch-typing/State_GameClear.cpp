//
//  State_GameClear.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/7.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "State_GameClear.hpp"
#include "StateManager.hpp"


State_GameClear::State_GameClear(StateManager* l_stateManager)
: BaseState(l_stateManager){}

State_GameClear::~State_GameClear(){}

void State_GameClear::OnCreate(){
    sf::Vector2u windowSize = m_stateMgr->GetContext()
    ->m_wind->GetRenderWindow()->getSize();
    m_elapsed = 0;
    m_font.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(50);
    m_text.setString("Congratulations! You beat the game!");
    m_text.setFillColor(sf::Color::White);
    m_text.setOrigin(m_text.getLocalBounds().width / 2,
                     m_text.getLocalBounds().height / 2);
    m_text.setPosition(windowSize.x / 2.0f , windowSize.y /2.0f);
    
    m_stateMgr->Remove(StateType::Game);
}

void State_GameClear::OnDestroy(){}

void State_GameClear::Activate(){}
void State_GameClear::Deactivate(){}

void State_GameClear::Update(const sf::Time& l_time){
    m_elapsed += l_time.asSeconds();
    if(m_elapsed >= 1.0f){
        m_stateMgr->Remove(StateType::Clear);
        m_stateMgr->SwitchTo(StateType::MainMenu);
    }
}

void State_GameClear::Draw(){
    sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_text);
}
