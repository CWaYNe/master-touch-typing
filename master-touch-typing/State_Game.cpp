//
//  State_Game.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/4.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "State_Game.hpp"
#include "StateManager.hpp"
#include <stdlib.h>

State_Game::State_Game(StateManager* l_stateManager): BaseState(l_stateManager), m_correct(false), m_shakeTimer(0.0f), PI(3.1415926f), m_defaultText("Input:"){
    m_english_words = {"English", "Chinese"};
    it = m_english_words.begin();
};

State_Game::~State_Game(){};

void State_Game::OnCreate(){
    sf::Vector2u windowSize = m_stateMgr->GetContext()
    ->m_wind->GetRenderWindow()->getSize();
    TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
    sf::FloatRect viewSpace = this->m_stateMgr->GetContext()->m_wind->GetViewSpace();
    
    textureMgr->RequireResource("GameStateBg");
    textureMgr->RequireResource("Stage1");
    
    
    m_background.setTexture(*textureMgr->GetResource("GameStateBg"));
    m_battleSprite.setTexture(*textureMgr->GetResource("Stage1"));
    
    
    m_battleSprite.setScale(windowSize.x/m_battleSprite.getLocalBounds().width, 1);
    m_background.setScale(windowSize.x/m_background.getLocalBounds().width, windowSize.y/m_background.getLocalBounds().height);
    m_battleSprite.setPosition(viewSpace.left, viewSpace.top);
    m_background.setPosition(viewSpace.left, viewSpace.top);
    
    
    m_font.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(36);
    m_text.setFillColor(sf::Color::Black);
    m_text.setString(sf::String(m_defaultText + m_userInputs));
    
    m_word.setFont(m_font);
    m_word.setString(sf::String(*it));
    m_word.setCharacterSize(36);
    m_word.setFillColor(sf::Color::Black);
    
    
    sf::FloatRect wordRect = m_word.getLocalBounds();
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_word.setOrigin(wordRect.left + wordRect.width / 2.0f, wordRect.top + wordRect.height / 2.0f);
    
    m_text.setPosition(windowSize.x / 2.0f, m_battleSprite.getLocalBounds().height + 80);
    m_word.setPosition(windowSize.x / 2.0f, m_battleSprite.getLocalBounds().height + 20);
    defaultScale = m_text.getScale();
    
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
    AddTypingCallback();
}

void State_Game::OnDestroy(){
    TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
    textureMgr->ReleaseResource("GameStateBg");
    textureMgr->ReleaseResource("Stage1");
    
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Game, "Key_Escape");
    RemoveTypingCallback();
}

void State_Game::AddTypingCallback(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Game, "Key_Typing", &State_Game::KeyPressed, this);
    evMgr->AddCallback(StateType::Game, "Key_Enter", &State_Game::EnterKeyPressed, this);
}

void State_Game::RemoveTypingCallback(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Game, "Key_Typing");
    evMgr->RemoveCallback(StateType::Game, "Key_Enter");
}

void State_Game::KeyPressed(EventDetails* l_details){
    if (l_details->m_textEntered == '\b'){
        if(!m_userInputs.empty())
            m_userInputs.erase(m_userInputs.size()-1, 1);
    }
    else if (l_details->m_textEntered < 128 && l_details->m_textEntered != 10){
        m_userInputs += static_cast<char>(l_details->m_textEntered);
    }
}

void State_Game::EnterKeyPressed(EventDetails* l_details){
    if (m_userInputs == *it){
        m_correct = true;
        m_userInputs = "";
        m_text.setFillColor(sf::Color::White);
    } else{
        m_text.setFillColor(sf::Color::Red);
        m_shakeTimer = 0.4f;
    }
}


void State_Game::Update(const sf::Time& l_time){
    sf::Vector2u windowSize = m_stateMgr->GetContext()
    ->m_wind->GetRenderWindow()->getSize();
    if(m_correct && it == m_english_words.end()){
        m_correct = false;
        m_stateMgr->SwitchTo(StateType::GameOver);
    }else if (m_correct){
        m_correct = false;
        if(++it == m_english_words.end()){
            m_correct = true;
        }
        if (it != m_english_words.end()){
            m_word.setString(sf::String(*it));
            sf::FloatRect wordRect = m_word.getLocalBounds();
            m_word.setOrigin(wordRect.left + wordRect.width / 2.0f, wordRect.top + wordRect.height / 2.0f);
            m_word.setPosition(windowSize.x / 2.0f, m_battleSprite.getLocalBounds().height + 20);
        }
    }
    
    SharedContext* context = m_stateMgr->GetContext();
    m_text.setString(sf::String(m_defaultText + m_userInputs));
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    
    m_text.setPosition(windowSize.x / 2.0f, m_battleSprite.getLocalBounds().height + 80);
    
    if (m_shakeTimer > 0.0f){
        m_shakeTimer -= l_time.asSeconds();
        float offset = rand() % 1 ? 1.5366 : -1.54642;
        m_text.move(offset,offset);
        m_text.setScale(m_text.getScale().x * 1.0004f, m_text.getScale().y * 1.0004f);
    }else {
        m_text.setRotation(0.0f);
        m_text.setScale(defaultScale);
    }
}

void State_Game::Draw(){
    sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_background);
    window->draw(m_battleSprite);
    window->draw(m_word);
    window->draw(m_text);
}

void State_Game::MainMenu(EventDetails* l_details){
    m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails *l_details){
    m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate(){}
void State_Game::Deactivate(){}
