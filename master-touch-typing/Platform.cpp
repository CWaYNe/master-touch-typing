//
//  Platform.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/7.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "Platform.hpp"

Platform::Platform(SharedContext* l_context, BaseState* l_currentState, const sf::Vector2u& l_position):m_context(l_context), m_currentState(l_currentState), m_nextStage(false), m_backgroundPosition(l_position){
    LoadBackground();
}

Platform::~Platform(){
    // TODO
    PurgePlatform();
    
}

sf::FloatRect Platform::GetBackgroundBound() const{
    return m_backgroundSprite.getLocalBounds();
}

// TODO: refactor it later
void Platform::LoadBackground(){
    sf::Vector2u windowSize = m_context->m_wind->GetRenderWindow()->getSize();
    TextureManager* textureMgr = m_context->m_textureManager;
    m_backgroundTexture = "Stage1";
    textureMgr->RequireResource(m_backgroundTexture);
    
    m_backgroundSprite.setTexture(*textureMgr->GetResource(m_backgroundTexture));
    m_backgroundSprite.setScale(windowSize.x / m_backgroundSprite.getLocalBounds().width, 1);
    m_backgroundSprite.setOrigin(m_backgroundSprite.getLocalBounds().width / 2.0f, m_backgroundSprite.getLocalBounds().height / 2.0f);
    m_backgroundSprite.setPosition(m_backgroundPosition.x + m_backgroundSprite.getLocalBounds().width / 2.0f, m_backgroundPosition.y + m_backgroundSprite.getLocalBounds().height / 2.0f);
    
    m_context->m_platformEntityManager->Add(PlatformEntityType::Player, "");
    m_context->m_platformEntityManager->Add(PlatformEntityType::Enemy, "");
    
    // DEV TEST PLAYGROUND
//    m_player.setSize(sf::Vector2f(32, 32));
//    m_player.setFillColor(sf::Color::Green);
//    m_player.setOrigin(m_player.getSize().x / 2.0f, m_player.getSize().y / 2.0f);
//    m_player.setPosition(16.0f, m_backgroundSprite.getPosition().y + m_backgroundSprite.getLocalBounds().height / 2.0f - 16.0f);
//
//    m_enemy.setSize(sf::Vector2f(32, 32));
//    m_enemy.setFillColor(sf::Color::Red);
//    m_enemy.setOrigin(m_enemy.getSize().x / 2.0f, m_enemy.getSize().y / 2.0f);
//    m_enemy.setPosition(m_backgroundSprite.getPosition().x + m_backgroundSprite.getLocalBounds().width / 2.0f - 16.0f, m_backgroundSprite.getPosition().y + m_backgroundSprite.getLocalBounds().height / 2.0f -  16.0f);
//    

    // END DEV
    
}

void Platform::PurgePlatform(){
    if (m_backgroundTexture == ""){ return; }
    m_context->m_textureManager->ReleaseResource(m_backgroundTexture);
    m_backgroundTexture = "";
}

void Platform::LoadNext(){
    m_nextStage = true;
}

void Platform::Update(float l_dT){
    if(m_nextStage){
        m_nextStage = false;
        // release resource and load next
        // use l_current_state to get path
        
        // check if finish all stages
        // then go to StateType::GameOver
    }
}

void Platform::Draw(){
    sf::RenderWindow* window = m_context->m_wind->GetRenderWindow();
    window->draw(m_backgroundSprite);
    
    // DEV TEST PlAYGROUND
//    window->draw(m_player);
//    window->draw(m_enemy);
    // END DEV
}
