//
//  PlatformEnemy.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "PlatformEnemy.hpp"
#include "PlatformEntityManager.hpp"
#include "StateManager.hpp"

PlatformEnemy::PlatformEnemy(PlatformEntityManager* l_entityMgr)
: PlatformCharacter(l_entityMgr)
{
    Load("PlatformEnemy.char");
    std::cout << "[DEBUG] " << "Enemy loaded" << std::endl;
    m_type = PlatformEntityType::Enemy;
    SetPosition(994, 194);
    
}

PlatformEnemy::~PlatformEnemy(){}
