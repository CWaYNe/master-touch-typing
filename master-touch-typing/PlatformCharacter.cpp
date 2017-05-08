//
//  PlatformCharacter.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "PlatformCharacter.hpp"
#include "EntityManager.hpp"
#include "StateManager.hpp"



PlatformCharacter::PlatformCharacter(PlatformEntityManager* l_entityMgr):PlatformEntityBase(l_entityMgr), m_spriteSheet(m_platformEntityManager->GetContext()->m_textureManager){
    m_name = "Character";
}

PlatformCharacter::~PlatformCharacter(){};

void PlatformCharacter::Load(const std::string& l_path){
    std::ifstream file;
    file.open(resourcePath() + std::string("media/Characters/") + l_path);
    
    if(!file.is_open()){
        std::cout << "! Failed loading the character file: " << l_path << std::endl;
        return;
    }
    std::string line;
    while(std::getline(file,line)){
        if (line[0] == '|'){ continue; }
        std::stringstream keystream(line);
        std::string type;
        keystream >> type;
        if(type == "Name"){
            keystream >> m_name;
        } else if(type == "Spritesheet"){
            std::string path;
            keystream >> path;
            m_spriteSheet.LoadSheet("media/SpriteSheets/" + path);
        } else if(type == "Hitpoints"){
            keystream >> m_hitpoints;
        } else if(type == "BoundingBox"){
            sf::Vector2f boundingSize;
            keystream >> boundingSize.x >> boundingSize.y;
            SetSize(boundingSize.x, boundingSize.y);
        } else {
            std::cout << "! Unknown type in character file: " << type << std::endl;
        }
    }
    file.close();
}


void PlatformCharacter::Animate(){
    PlatformEntityState state = GetState();
    
    if(state == PlatformEntityState::Walking && m_spriteSheet.
       GetCurrentAnim()->GetName() != "Walk")
    {
        m_spriteSheet.SetAnimation("Walk",true,true);
    }
    else if(state == PlatformEntityState::Jumping && m_spriteSheet.
            GetCurrentAnim()->GetName() != "Jump")
    {
        m_spriteSheet.SetAnimation("Jump",true,false);
    }
    else if(state == PlatformEntityState::Attacking && m_spriteSheet.
            GetCurrentAnim()->GetName() != "Attack")
    {
        m_spriteSheet.SetAnimation("Attack",true,false);
    } else if(state == PlatformEntityState::Hurt && m_spriteSheet.
              GetCurrentAnim()->GetName() != "Hurt")
    {
        m_spriteSheet.SetAnimation("Hurt",true,false);
    }
    else if(state == PlatformEntityState::Dying && m_spriteSheet.
            GetCurrentAnim()->GetName() != "Death")
    {
        m_spriteSheet.SetAnimation("Death",true,false);
    }
    else if(state == PlatformEntityState::Idle && m_spriteSheet.
            GetCurrentAnim()->GetName() != "Idle")
    {
        m_spriteSheet.SetAnimation("Idle",true,true);
    }
}



void PlatformCharacter::Update(float l_dT){
    if(GetState() != PlatformEntityState::Dying && GetState() != PlatformEntityState::Attacking && GetState() != PlatformEntityState::Hurt){
//        if(std::abs(m_velocity.y) >= 0.001f){
//            SetState(PlatformEntityState::Jumping);
//        } else if(std::abs(m_velocity.x) >= 0.1f){
//            SetState(PlatformEntityState::Walking);
//        } else {
            SetState(PlatformEntityState::Idle);
//        std::cout << m_spriteSheet.GetCurrentAnim()->GetName() << ":" << m_spriteSheet.GetCurrentAnim()->IsLooping() << ":" << m_spriteSheet.GetCurrentAnim()->IsPlaying() << std::endl;
//        }
    } else if(GetState() == PlatformEntityState::Attacking || GetState() == PlatformEntityState::Hurt){
        if(!m_spriteSheet.GetCurrentAnim()->IsPlaying()){
            SetState(PlatformEntityState::Idle);
        }
    } else if(GetState() == PlatformEntityState::Dying){
        if(!m_spriteSheet.GetCurrentAnim()->IsPlaying()){
            m_platformEntityManager->Remove(m_id);
        }
    }
    Animate();
    m_spriteSheet.Update(l_dT);
    m_spriteSheet.SetSpritePosition(m_position);
}

void PlatformCharacter::Draw(sf::RenderWindow* l_wind){
    m_spriteSheet.Draw(l_wind);
}
