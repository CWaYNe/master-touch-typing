//
//  Enemy.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/2.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Enemy_hpp
#define Enemy_hpp

#include "Character.hpp"
#include "EventManager.hpp"

class Enemy : public Character{
public:
    Enemy(EntityManager* l_entityMgr);
    ~Enemy();
    
    void OnEntityCollision(EntityBase* l_collider, bool l_attack);
    void Update(float l_dT);
    
private:
    sf::Vector2f m_destination;
    bool m_hasDestination;
};

#endif /* Enemy_hpp */
