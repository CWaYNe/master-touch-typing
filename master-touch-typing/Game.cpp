//
//  Game.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/26.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "Game.hpp"



Game::Game(): m_window("Master Touch Typing", sf::Vector2u(1024, 768)),
m_stateManager(&m_context), m_entityManager(&m_context, 100), m_platformEntityManager(&m_context, 100)
{
    m_clock.restart();
    srand(time(nullptr));
    
    m_context.m_wind = &m_window;
    m_context.m_eventManager = m_window.GetEventManager();
    m_context.m_textureManager = &m_textureManager;
    m_context.m_entityManager = &m_entityManager;
    m_context.m_platformEntityManager = &m_platformEntityManager;
    // Set first state of the game
    m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed = m_clock.restart();}
Window* Game::GetWindow(){ return &m_window; }

void Game::Update(){
    m_window.Update(); // Update window events.
    m_stateManager.Update(m_elapsed);   // let state manager update the state
}

void Game::Render(){
    m_window.BeginDraw(); // Clear.
    m_stateManager.Draw();
    if(m_context.m_debugOverlay.Debug()){
        m_context.m_debugOverlay.Draw(m_window.GetRenderWindow());
    }
    m_window.EndDraw(); // Display.
}

void Game::LateUpdate(){
    m_stateManager.ProcessRequests();
    RestartClock();
}


