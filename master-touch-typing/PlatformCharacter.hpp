//
//  PlatformCharacter.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef PlatformCharacter_hpp
#define PlatformCharacter_hpp

#include "PlatformEntityBase.hpp"
#include "SpriteSheet.hpp"
#include "EventManager.hpp"

class PlatformCharacter : public PlatformEntityBase{
    friend class PlatformEntityManager;
public:
    PlatformCharacter(PlatformEntityManager* l_entityMgr);
    virtual ~PlatformCharacter();
    
    void Load(const std::string& l_path); // load character info
    
    virtual void Update(float l_dT);
    void Draw(sf::RenderWindow* l_wind);
    
    
private:
    void Animate();
    SpriteSheet m_spriteSheet;
    
    int m_hitpoints;

};
#endif /* PlatformCharacter_hpp */
