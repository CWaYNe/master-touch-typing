//
//  PlatformEntityBase.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef PlatformEntityBase_hpp
#define PlatformEntityBase_hpp

#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

enum class PlatformEntityType{ Base, Enemy, Player, Magic };

enum class PlatformEntityState{ Idle, Walking, Jumping, Attacking, Casting, Hurt, Dying };

class PlatformEntityManager;

class PlatformEntityBase{
    friend class PlatformEntityManager;
public:
    PlatformEntityBase(PlatformEntityManager* l_entityMgr);
    virtual ~PlatformEntityBase();
    

    PlatformEntityState GetState()const;
    std::string GetName()const;
    unsigned int GetId()const;
    PlatformEntityType GetType()const;
    
    void SetPosition(float l_x, float l_y);
    void SetPosition(const sf::Vector2f& l_pos);
    void SetSize(float l_x, float l_y);
    void SetState(const PlatformEntityState& l_state);
    
    virtual void Update(float l_dT);
    virtual void Draw(sf::RenderWindow* l_wind) = 0;

    
protected:
    void UpdateAABB();
    sf::FloatRect m_AABB;// The bounding box for collisions.
    std::string m_name;
    sf::Vector2f m_size;
    PlatformEntityType m_type;
    PlatformEntityState m_state;
    unsigned int m_id;  // id in entity manager
    sf::Vector2f m_position;
    sf::Vector2f m_positionOld;
    
    PlatformEntityManager* m_platformEntityManager;
    
};

#endif /* PlatformEntityBase_hpp */
