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
    m_font.loadFromFile(resourcePath() + "media/Fonts/arial.ttf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(22);
    m_text.setString(sf::String(m_defaultText + m_userInputs));
    
    m_word.setFont(m_font);
    m_word.setString(sf::String(*it));
    m_word.setCharacterSize(22);
    
    
    
    sf::FloatRect wordRect = m_word.getLocalBounds();
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_word.setOrigin(wordRect.left + wordRect.width / 2.0f, wordRect.top + wordRect.height / 2.0f);
    
    m_text.setPosition(400, 350);
    m_word.setPosition(400, 100);
    defaultScale = m_text.getScale();
    
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
    AddTypingCallback();
}

void State_Game::OnDestroy(){
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
            m_word.setPosition(400, 100);
        }
    }
    
    SharedContext* context = m_stateMgr->GetContext();
    m_text.setString(sf::String(m_defaultText + m_userInputs));
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    
    m_text.setPosition(400, 250);
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
