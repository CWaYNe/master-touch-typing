//
//  PlatformEnemy.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef PlatformEnemy_hpp
#define PlatformEnemy_hpp
#include "PlatformCharacter.hpp"
#include "EventManager.hpp"
class PlatformEnemy : public PlatformCharacter{
public:
    PlatformEnemy(PlatformEntityManager* l_entityMgr);
    ~PlatformEnemy();
    
    // collision with other entity
    //    void OnEntityCollision(PlatformEntityBase* l_collider, bool l_attack);
    //    void React(EventDetails* l_details);
};

#endif /* PlatformEnemy_hpp */
