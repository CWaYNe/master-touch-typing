//
//  Keyboard.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/5.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "Keyboard.hpp"

Keyboard::Keyboard(SharedContext* l_context, BaseState* l_currentState):m_currentState(l_currentState),m_context(l_context), keyboardSize(800, 400){
    CreateSkeleton();
    LoadKeys();
}

Keyboard::~Keyboard(){PurgeKeys();}

void Keyboard::LoadKeys(){
    sf::Vector2f keyboardPos =  m_keyboardContour.getPosition();
    // manually setup for dev
    sf::Vector2f keySize(48.0f, 48.0f);
    for (unsigned int i=0; i<14; i++){
        sf::Vector2f keyPosition(keyboardPos.x - keyboardSize.x / 2.0f + i * ( 5 + 48 ) + 24 + 5, keyboardPos.y - keyboardSize.y /2.0f + 24 + 5);
        
        Key *key = new Key(97+i, i, KeyType::NORMAL);
        key->SetKey(keyPosition, keySize);
        m_keys.insert(std::make_pair(97+i, key));
    }
}

Keys Keyboard::GetKeys() const {
    return m_keys;
}

void Keyboard::PurgeKeys(){
    for (auto &itr : m_keys){
        delete itr.second;
    }
    m_keys.clear();
}

void Keyboard::CreateSkeleton(){
    sf::Vector2u windowSize = m_context->m_wind->GetRenderWindow()->getSize();
    
    
    m_keyboardContour.setSize(keyboardSize);
    m_keyboardContour.setFillColor(sf::Color::White);
    m_keyboardContour.setCornersRadius(5.0f);
    m_keyboardContour.setCornerPointCount(4);
    m_keyboardContour.setOrigin(400, 200);
    m_keyboardContour.setOutlineColor(sf::Color::Black);
    m_keyboardContour.setOutlineThickness(7);
    m_keyboardContour.setPosition(windowSize.x / 2.0f, windowSize.y / 1.43);
    
}

void Keyboard::Update(float l_dT){
    for(auto it : m_keys){
        it.second->Update(l_dT);
    }
}

void Keyboard::Draw(){
    sf::RenderWindow* window = m_context->m_wind->GetRenderWindow();
    window->draw(m_keyboardContour);
    for(auto& itr : m_keys){
        itr.second->Draw(window);
    }
}
