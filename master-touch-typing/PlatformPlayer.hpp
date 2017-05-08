//
//  PlatformPlayer.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef PlatformPlayer_hpp
#define PlatformPlayer_hpp

#include "PlatformCharacter.hpp"
#include "EventManager.hpp"

class PlatformPlayer : public PlatformCharacter{
public:
    PlatformPlayer(PlatformEntityManager* l_entityMgr);
    ~PlatformPlayer();
  
    void Move();
    // collision with other entity
//    void OnEntityCollision(PlatformEntityBase* l_collider, bool l_attack);
//    void React(EventDetails* l_details);
};

#endif /* PlatformPlayer_hpp */
