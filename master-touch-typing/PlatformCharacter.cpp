//
//  PlatformCharacter.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "PlatformCharacter.hpp"
#include "EntityManager.hpp"
#include "StateManager.hpp"



PlatformCharacter::PlatformCharacter(PlatformEntityManager* l_entityMgr):PlatformEntityBase(l_entityMgr){
    // DEV LOAD SAMPLE
    m_type = PlatformEntityType::Player;
    Load("Player");
    
    m_name = "Character";
}

PlatformCharacter::~PlatformCharacter(){};

void PlatformCharacter::Load(const std::string& l_path){
    
    // TESTING SAMPLE
    if (l_path == "Player"){
        m_sprite.setSize(sf::Vector2f(32, 32));
        m_sprite.setFillColor(sf::Color::Green);
        m_sprite.setOrigin(m_sprite.getSize().x / 2.0f, m_sprite.getSize().y / 2.0f);
        m_sprite.setPosition(16.0f, 194);
    }else if (l_path == "Enemy"){
        m_sprite.setSize(sf::Vector2f(32, 32));
        m_sprite.setFillColor(sf::Color::Red);
        m_sprite.setOrigin(m_sprite.getSize().x / 2.0f, m_sprite.getSize().y / 2.0f);
        m_sprite.setPosition(1008, 194);
    }

    // END TESTING
}

void PlatformCharacter::Update(float l_dT){
}

void PlatformCharacter::Draw(sf::RenderWindow* l_wind){
    l_wind->draw(m_sprite);
}
