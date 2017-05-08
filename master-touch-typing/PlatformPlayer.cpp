//
//  PlatformPlayer.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "PlatformPlayer.hpp"
#include "PlatformEntityManager.hpp"
#include "StateManager.hpp"

PlatformPlayer::PlatformPlayer(PlatformEntityManager* l_entityMgr)
: PlatformCharacter(l_entityMgr)
{
    Load("PlatformPlayer.char");
    std::cout << "[DEBUG] " << "player loaded" << std::endl;
    m_type = PlatformEntityType::Player;
    SetPosition(16.0f, 194);
    
}
PlatformPlayer::~PlatformPlayer(){}

void PlatformPlayer::Move(){
    SetState(PlatformEntityState::Walking);
}
