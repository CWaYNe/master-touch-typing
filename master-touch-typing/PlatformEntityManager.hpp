//
//  PlatformEntityManager.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/8.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef PlatformEntityManager_hpp
#define PlatformEntityManager_hpp

#include <unordered_map>
#include <functional>
#include "PlatformPlayer.hpp"
#include "PlatformEnemy.hpp"



using PlatformEntityContainer = std::unordered_map<unsigned int,PlatformEntityBase*>;
using PlatformEntityFactory = std::unordered_map<PlatformEntityType, std::function<PlatformEntityBase*(void)>, EnumClassHash>;
using PlatformEnemyTypes = std::unordered_map<std::string,std::string>;


struct SharedContext;

class PlatformEntityManager{
public:
    PlatformEntityManager(SharedContext* l_context, unsigned int l_maxEntities);
    ~PlatformEntityManager();
    
    int Add(const PlatformEntityType& l_type, const std::string& l_name);
    PlatformEntityBase* Find(const std::string& l_name);
    PlatformEntityBase* Find(unsigned int l_id);
    void Remove(unsigned int l_id);

    void Update(float l_dT);
    void Draw();
    
    void Purge();
    SharedContext* GetContext();
private:

    void ProcessRemovals();
    
    template<class T>
    void RegisterEntity(const PlatformEntityType& l_type){
        m_platformEntityFactory[l_type] = [this]() -> PlatformEntityBase*
        {
            return new T(this);
        };
    }
    
    PlatformEntityContainer m_platformEntities;
    PlatformEnemyTypes m_enemyTypes;
    PlatformEntityFactory m_platformEntityFactory;
    SharedContext* m_context;
    unsigned int m_maxEntities;
    unsigned int m_idCounter;
    
    std::vector<unsigned int> m_entitiesToRemove;
};

#endif /* PlatformEntityManager_hpp */
