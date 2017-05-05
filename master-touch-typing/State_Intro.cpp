//
//  State_Intro.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/29.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "State_Intro.hpp"
#include "StateManager.hpp"


State_Intro::State_Intro(StateManager* l_stateManager)
: BaseState(l_stateManager), m_elapsedTime(0.0f), m_elapsedTime2(0.0f), m_titlePunc{"|"}{}

State_Intro::~State_Intro(){}

void State_Intro::OnCreate(){
    sf::Vector2u windowSize = m_stateMgr->GetContext()
    ->m_wind->GetRenderWindow()->getSize();
    
    TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
    textureMgr->RequireResource("IntroBg");
    
    // setup intro background image
    m_introSprite.setTexture(*textureMgr->GetResource("IntroBg"));
    m_introSprite.setScale(windowSize.x/m_introSprite.getLocalBounds().width, windowSize.y/m_introSprite.getLocalBounds().height);
    sf::FloatRect viewSpace = this->m_stateMgr->GetContext()->m_wind->GetViewSpace();
    m_introSprite.setPosition(viewSpace.left, viewSpace.top);
    
    // setup title, subtitle and continue text
    m_font.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    m_title.setFont(m_font);
    m_text.setFont(m_font);
    m_subtitle.setFont(m_font);
    m_title.setCharacterSize(72);
    m_subtitle.setCharacterSize(36);
    m_text.setCharacterSize(25);
    
    m_title.setString(sf::String("Master Touch Typing"));
    m_subtitle.setString(sf::String("alongside learning english!"));
    m_subtitle.setStyle(sf::Text::Italic);
    m_text.setString(sf::String("Press SPACE to continue"));
    
    sf::FloatRect bgRect = m_introSprite.getLocalBounds();
    sf::FloatRect titleRect = m_title.getLocalBounds();
    sf::FloatRect subtitleRect = m_subtitle.getLocalBounds();
    sf::FloatRect textRect = m_text.getLocalBounds();
    
    m_title.setOrigin(titleRect.left + titleRect.width / 2.0f, titleRect.top + titleRect.height / 2.0f);
    m_title.setPosition(windowSize.x / 2.0f, windowSize.y / 2.89f);
    
    m_subtitle.setOrigin(subtitleRect.left + subtitleRect.width / 2.0f, subtitleRect.top + subtitleRect.height / 2.0f);
    m_subtitle.setPosition(windowSize.x / 2.0f + subtitleRect.width / 3.0f , windowSize.y / 2.89f + titleRect.height);
    
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_text.setPosition(windowSize.x / 2.0f, windowSize.y / 1.29f);
    
    

    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Intro, "Intro_Continue",&State_Intro::Continue,this);
}

void State_Intro::OnDestroy(){
    TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
    textureMgr->ReleaseResource("IntroBg");
    
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Intro,"Intro_Continue");
}

void State_Intro::Draw(){
    sf::RenderWindow* window = m_stateMgr->
    GetContext()->m_wind->GetRenderWindow();
    
    window->draw(m_introSprite);
    window->draw(m_title);
    window->draw(m_subtitle);
    window->draw(m_text);
}

void State_Intro::Continue(EventDetails* l_details){
    m_stateMgr->SwitchTo(StateType::MainMenu);
    m_stateMgr->Remove(StateType::Intro);
}

void State_Intro::Update(const sf::Time& l_time){
    m_elapsedTime += l_time.asSeconds();
    m_elapsedTime2 += l_time.asSeconds();
    if(m_elapsedTime > 1.0f){
        m_text.setString({""});
        m_elapsedTime = -1.0f;
    } else if(m_elapsedTime > 0.0f) {
        m_text.setString({"Press SPACE to continue"});
    }
    
    if(m_elapsedTime2 > 0.6f){
        m_title.setString({"Master Touch Typing"+m_titlePunc});
        m_elapsedTime2 = -0.6f;
    } else if(m_elapsedTime2 > 0.0f) {
        m_title.setString({"Master Touch Typing"});
    }
}
void State_Intro::Activate(){}
void State_Intro::Deactivate(){}
