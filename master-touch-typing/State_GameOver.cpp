//
//  State_GameOver.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/2.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "State_GameOver.hpp"
#include "StateManager.hpp"


State_GameOver::State_GameOver(StateManager* l_stateManager)
: BaseState(l_stateManager){}

State_GameOver::~State_GameOver(){}

void State_GameOver::OnCreate(){
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

void State_GameOver::OnDestroy(){}

void State_GameOver::Activate(){}
void State_GameOver::Deactivate(){}

void State_GameOver::Update(const sf::Time& l_time){
    m_elapsed += l_time.asSeconds();
    if(m_elapsed >= 1.0f){
        m_stateMgr->Remove(StateType::GameOver);
        m_stateMgr->SwitchTo(StateType::MainMenu);
    }
}

void State_GameOver::Draw(){
    sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_text);
}
