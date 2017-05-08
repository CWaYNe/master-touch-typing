//
//  PlatformEntityManager.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "PlatformEntityManager.hpp"
#include "SharedContext.hpp"

PlatformEntityManager::PlatformEntityManager(SharedContext* l_context, unsigned int l_maxEntities)
:m_context(l_context), m_maxEntities(l_maxEntities), m_idCounter(0)
{
//    LoadEnemyTypes("EnemyList.list");
    RegisterEntity<PlatformCharacter>(PlatformEntityType::Player);
//    RegisterEntity<Enemy>(EntityType::Enemy);
}

PlatformEntityManager::~PlatformEntityManager(){
    Purge();
};


int PlatformEntityManager::Add(const PlatformEntityType& l_type, const std::string& l_name){
    auto itr = m_platformEntityFactory.find(l_type);
    if (itr == m_platformEntityFactory.end()){ return -1; }
    PlatformEntityBase* entity = itr->second();
    entity->m_id = m_idCounter;
    if (l_name != ""){ entity->m_name = l_name; }
    
    m_platformEntities.emplace(m_idCounter, entity);
    
    ++m_idCounter;
    return m_idCounter - 1;
}

void PlatformEntityManager::Purge(){
    for (auto &itr : m_platformEntities){
        delete itr.second;
    }
    m_platformEntities.clear();
    m_idCounter = 0;
}

void PlatformEntityManager::Update(float l_dT){
    
}

void PlatformEntityManager::Draw(){
    sf::RenderWindow* wnd = m_context->m_wind->GetRenderWindow();
    
    for (auto &itr : m_platformEntities){
        itr.second->Draw(wnd);
    }
}

// find by name
PlatformEntityBase* PlatformEntityManager::Find(const std::string& l_name){
    for(auto &itr : m_platformEntities){
        if(itr.second->GetName() == l_name){
            return itr.second;
        }
    }
    return nullptr;
}

// find by ID
PlatformEntityBase* PlatformEntityManager::Find(unsigned int l_id){
    auto itr = m_platformEntities.find(l_id);
    if (itr == m_platformEntities.end()){ return nullptr; }
    return itr->second;
}
