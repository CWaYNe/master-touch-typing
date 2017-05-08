//
//  PlatformEntityBase.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "PlatformEntityBase.hpp"


PlatformEntityBase::PlatformEntityBase(PlatformEntityManager* l_entityMgr):m_platformEntityManager(l_entityMgr), m_name("BaseEntity"), m_type(PlatformEntityType::Base), m_id(0), m_state(PlatformEntityState::Idle){};

PlatformEntityBase::~PlatformEntityBase(){}

std::string PlatformEntityBase::GetName() const{
    return m_name;
}

void PlatformEntityBase::Update(float l_dT){
    
}
