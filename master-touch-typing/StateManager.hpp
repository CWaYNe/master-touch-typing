//
//  StateManager.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/27.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef StateManager_hpp
#define StateManager_hpp

#include <vector>
#include <unordered_map>
#include "SharedContext.hpp"
#include "State_Intro.hpp"
#include "State_MainMenu.hpp"
#include "State_Game.hpp"
#include "State_Paused.hpp"

enum class StateType{
    Intro=1, MainMenu, Game, Paused, GameOver, Credits
};


using StateContainer = std::vector<std::pair<StateType, BaseState*>>;
using TypeContainer = std::vector<StateType>;
using StateFactory = std::unordered_map<StateType, std::function<BaseState*(void)>, EnumClassHash>;

class StateManager{
public:
    StateManager(SharedContext* l_shared);
    ~StateManager();
    
    void Update(const sf::Time& l_time);
    void Draw();
    
    void ProcessRequests();
    
    SharedContext* GetContext();
    bool HasState(const StateType& l_type);
    
    void SwitchTo(const StateType& l_type);
    void Remove(const StateType& l_type);

private:
    void CreateState(const StateType& l_type);
    void RemoveState(const StateType& l_type);
    
    template<class T>
    void RegisterState(const StateType& l_type){
        m_stateFactory[l_type] = [this]()-> BaseState*
        {
            return new T(this);
        };
    }
    
    
    SharedContext* m_shared;
    StateContainer m_states;
    TypeContainer m_toRemove;
    StateFactory m_stateFactory;
};

#endif /* StateManager_hpp */
