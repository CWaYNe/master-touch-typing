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
    
    m_backgroundSprite.setScale(windowSize.x /m_backgroundSprite.getLocalBounds().width, 1);
    m_backgroundSprite.setPosition(m_backgroundPosition.x, m_backgroundPosition.y);
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
}
