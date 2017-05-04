//
//  State_Game.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/29.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "State_Game2.hpp"
#include "StateManager.hpp"


State_Game2::State_Game2(StateManager* l_stateManager)
: BaseState(l_stateManager){}

State_Game2::~State_Game2(){}

void State_Game2::OnCreate(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    
    evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game2::MainMenu, this);
    evMgr->AddCallback(StateType::Game, "Key_P", &State_Game2::Pause, this);
    evMgr->AddCallback(StateType::Game, "Key_O", &State_Game2::ToggleOverlay, this);
    
    sf::Vector2u size = m_stateMgr->GetContext()->m_wind->GetWindowSize();
    m_view.setSize(size.x,size.y);
    m_view.setCenter(size.x/2,size.y/2);
    m_view.zoom(0.6f);
    m_stateMgr->GetContext()->m_wind->GetRenderWindow()->setView(m_view);
    
    // Load First stage's map
    m_gameMap = new Map(m_stateMgr->GetContext(), this);
    m_gameMap->LoadMap("media/Maps/map1.map");
    std::cout << "[DEBUG] " << "map loaded" << std::endl;
}

void State_Game2::OnDestroy(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Game, "Key_Escape");
    evMgr->RemoveCallback(StateType::Game, "Key_P");
    evMgr->RemoveCallback(StateType::Game, "Key_O");
    
    delete m_gameMap;
    m_gameMap = nullptr;
}

void State_Game2::Update(const sf::Time& l_time){
    SharedContext* context = m_stateMgr->GetContext();
    EntityBase* player = context->m_entityManager->Find("Player");
    if(!player){
        std::cout << "Respawning player..." << std::endl;
        context->m_entityManager->Add(EntityType::Player,"Player");
        player = context->m_entityManager->Find("Player");
        player->SetPosition(m_gameMap->GetPlayerStart());
    } else {
        m_view.setCenter(player->GetPosition());
        context->m_wind->GetRenderWindow()->setView(m_view);
    }
    
    sf::FloatRect viewSpace = context->m_wind->GetViewSpace();
    if(viewSpace.left <= 0){
        m_view.setCenter(viewSpace.width / 2,m_view.getCenter().y);
        context->m_wind->GetRenderWindow()->setView(m_view);
    } else if (viewSpace.left + viewSpace.width > (m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size){
        m_view.setCenter(((m_gameMap->GetMapSize().x + 1) * Sheet::Tile_Size) - (viewSpace.width / 2), m_view.getCenter().y);
        context->m_wind->GetRenderWindow()->setView(m_view);
    }
    // update game
    m_gameMap->Update(l_time.asSeconds());
    m_stateMgr->GetContext()->m_entityManager->Update(l_time.asSeconds());
}

void State_Game2::Draw(){
    // draw game
    m_gameMap->Draw();
    m_stateMgr->GetContext()->m_entityManager->Draw();
}

void State_Game2::MainMenu(EventDetails* l_details){
    m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game2::Pause(EventDetails* l_details){
    m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game2::Activate(){}
void State_Game2::Deactivate(){}

// Test/debug methods.
void State_Game2::ToggleOverlay(EventDetails* l_details){
    m_stateMgr->GetContext()->m_debugOverlay.SetDebug(!m_stateMgr->GetContext()->m_debugOverlay.Debug());
}
