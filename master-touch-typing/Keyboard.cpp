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
    widthMapping[0] = 48.0f;
    widthMapping[1] = 64.0f;
    widthMapping[2] = 76.0f;
    widthMapping[3] = 100.0f;
    widthMapping[4] = 240.0f;
    LoadKeys("Keyboard.cfg");
}

Keyboard::~Keyboard(){PurgeKeys();}

void Keyboard::LoadKeys(const std::string& l_keyFile){
    sf::Vector2f keyboardPos =  m_keyboardSkeleton.getPosition();
    // load file from keyboard.cfg
    float w, lw = 0; // current width, last width of key
    std::ifstream keysmapping;


    float defaultXPos = keyboardPos.x - keyboardSize.x / 2.0f + 24.0f;
    float xPos = defaultXPos;
    float yPos = keyboardPos.y - keyboardSize.y /2.0f + 24 + 5;
    
    int i = 0;
    
    keysmapping.open(resourcePath()+l_keyFile);
    if(keysmapping.is_open()){
        std::string line;
        while(std::getline(keysmapping, line)){
            
            
            if (line[0] == '|'){ continue; }
            std::stringstream keystream(line);
            int code1, code2, id, type;
            keystream >> code1 >> code2;
            keystream >> id >> type;
            if (code1 != -1){
                m_key_mapping.insert(std::make_pair(unsigned(code1), unsigned(id)));
            }
            if (code2 != -1){
                m_key_mapping.insert(std::make_pair(unsigned(code2), unsigned(id)));
            }
            if (code1 == -1 && code2 == -1){
                // handle special keys (shift ...)
            }
            
            // change row -> update x, y position
            if(id == 14 || id == 28 || id == 41 || id == 53){
                yPos += (48 + 5);
                lw = i = 0;
                xPos = defaultXPos;
                if (id == 53){
                    xPos += 4*(48+5);
                }
            }
            w = widthMapping[type];
            sf::Vector2f keySize(w, 48.0f);
        
            xPos += lw/2.0f + w/2.0f + 5;
            sf::Vector2f keyPosition(xPos, yPos);
            Key *key = new Key(id, static_cast<KeyType>(type));
            key->SetKey(keyPosition, keySize);
            m_keys.insert(std::make_pair(id, key));
            
            lw = w;
            i++;
        }
    }
    
    // TODO : handle path error
    
}

Keys Keyboard::GetKeys() const {
    return m_keys;
}

unsigned int Keyboard::GetKeyId(Unicode_code unicode) const {
    auto itr = m_key_mapping.find(unicode);
    return (itr != m_key_mapping.end() ? itr->second : 129);
}

void Keyboard::PurgeKeys(){
    for (auto &itr : m_keys){
        delete itr.second;
    }
    m_keys.clear();
}

void Keyboard::CreateSkeleton(){
    sf::Vector2u windowSize = m_context->m_wind->GetRenderWindow()->getSize();
    
    m_keyboardSkeleton.setSize(keyboardSize);
    m_keyboardSkeleton.setFillColor(sf::Color::White);
    m_keyboardSkeleton.setCornersRadius(5.0f);
    m_keyboardSkeleton.setCornerPointCount(4);
    m_keyboardSkeleton.setOrigin(400, 200);
    m_keyboardSkeleton.setOutlineColor(sf::Color::Black);
    m_keyboardSkeleton.setOutlineThickness(7);
    m_keyboardSkeleton.setPosition(windowSize.x / 2.0f, windowSize.y / 1.43);
    
}

void Keyboard::Update(float l_dT){
    for(auto it : m_keys){
        it.second->Update(l_dT);
    }
}

void Keyboard::Draw(){
    sf::RenderWindow* window = m_context->m_wind->GetRenderWindow();
    window->draw(m_keyboardSkeleton);
    for(auto& itr : m_keys){
        itr.second->Draw(window);
    }
}
