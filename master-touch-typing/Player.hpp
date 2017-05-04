//
//  Player.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/2.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"
#include "EventManager.hpp"

class Player : public Character{
public:
    Player(EntityManager* l_entityMgr);
    ~Player();
    
    // collision with other entity
    void OnEntityCollision(EntityBase* l_collider, bool l_attack);
    void React(EventDetails* l_details);
};

#endif /* Player_hpp */
