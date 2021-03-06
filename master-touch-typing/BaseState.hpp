//
//  BaseState.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/27.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef BaseState_hpp
#define BaseState_hpp

#include <SFML/Graphics.hpp>

class StateManager; // forward declaration

class BaseState{
    friend class StateManager;
public:
    BaseState(StateManager* l_stateManager):m_stateMgr(l_stateManager),
    m_transparent(false), m_transcendent(false){}
    virtual ~BaseState(){}
    
    // State created and pushed on the stack
    virtual void OnCreate() = 0;
    virtual void OnDestroy() = 0;
    
    // Invoke when state is moved to the top of the stack
    virtual void Activate() = 0;
    virtual void Deactivate() = 0;
    
    virtual void Update(const sf::Time& l_time) = 0;
    virtual void Draw() = 0;
    
    void SetTransparent(const bool& l_transparent){ m_transparent = l_transparent; }
    bool IsTransparent()const{ return m_transparent; }
    void SetTranscendent(const bool& l_transcendence){ m_transcendent = l_transcendence; }
    bool IsTranscendent()const{ return m_transcendent; }
    StateManager* GetStateManager(){ return m_stateMgr; }
    
    sf::View& GetView(){ return m_view; }
protected:
    StateManager* m_stateMgr;
    bool m_transparent;
    bool m_transcendent;
    sf::View m_view;
};

#endif /* BaseState_hpp */
