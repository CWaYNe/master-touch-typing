//
//  PlatformEntityBase.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "PlatformEntityBase.hpp"


PlatformEntityBase::PlatformEntityBase(PlatformEntityManager* l_entityMgr):m_platformEntityManager(l_entityMgr), m_name("PlatformBaseEntity"), m_type(PlatformEntityType::Base), m_id(0), m_state(PlatformEntityState::Idle){};

PlatformEntityBase::~PlatformEntityBase(){}


void PlatformEntityBase::Update(float l_dT){
    
}

PlatformEntityState PlatformEntityBase::GetState()const{ return m_state; }
std::string PlatformEntityBase::GetName()const { return m_name; }
unsigned int PlatformEntityBase::GetId()const { return m_id; }
PlatformEntityType PlatformEntityBase::GetType()const {return m_type; }


void PlatformEntityBase::SetPosition(float l_x, float l_y){
    m_position = sf::Vector2f(l_x,l_y);
    UpdateAABB();
}

void PlatformEntityBase::SetPosition(const sf::Vector2f& l_pos){
    m_position = l_pos;
    UpdateAABB();
}

void PlatformEntityBase::SetSize(float l_x, float l_y){
    m_size = sf::Vector2f(l_x,l_y);
    UpdateAABB();
}


void PlatformEntityBase::SetState(const PlatformEntityState& l_state){
    if (m_state == PlatformEntityState::Dying){ return; }
    m_state = l_state;
}

void PlatformEntityBase::UpdateAABB(){
    m_AABB = sf::FloatRect(m_position.x - (m_size.x / 2),m_position.y - m_size.y, m_size.x,m_size.y);
}
