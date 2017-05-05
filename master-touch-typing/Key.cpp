//
//  Key.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/5.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "Key.hpp"


Key::Key(unsigned int l_id, KeyType l_type): m_id(l_id), m_type(l_type){};

Key::~Key(){};



// Getters
unsigned int Key::GetId() const {
    return m_id;
};

KeyType Key::GetType() const {
    return m_type;
};

void Key::Flicker(){
    m_key.setFillColor(sf::Color::Yellow);
    m_elapsed = 0.3f;
}

// Set key TODO::::::::::: const pos
void Key::SetKey(sf::Vector2f position,const  sf::Vector2f& keySize){
    m_key.setSize(keySize);
    m_key.setCornersRadius(4.5f);
    m_key.setCornerPointCount(4);
    m_key.setFillColor(sf::Color::Black);
    m_key.setOrigin(keySize.x / 2.0f, keySize.y / 2.0f);
    m_key.setPosition(position);
}

void Key::Update(float l_DT){
    if (m_elapsed > 0){
        m_elapsed -= l_DT;
    }else if(m_elapsed <= 0){
        m_key.setFillColor(sf::Color::Black);
        m_elapsed = 0.0f;
    }
        
}

void Key::Draw(sf::RenderWindow* l_wind){
    l_wind->draw(m_key);
}
