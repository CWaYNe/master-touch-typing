//
//  Game.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/26.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "Game.hpp"



Game::Game(): m_window("Chapter 5", sf::Vector2u(800,600)), m_stateManager(&m_context){
    // Setting up class members
    m_clock.restart();
    srand(time(nullptr));
    
    m_context.m_wind = &m_window;
    m_context.m_eventManager = m_window.GetEventManager();
    
    m_stateManager.SwitchTo(StateType::Intro);
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed = m_clock.restart();}
Window* Game::GetWindow(){ return &m_window; }

void Game::Update(){
    m_window.Update(); // Update window events.
    m_stateManager.Update(m_elapsed);
}

void Game::Render(){
    m_window.BeginDraw(); // Clear.
    m_stateManager.Draw();
    m_window.EndDraw(); // Display.
}

void Game::LateUpdate(){
    m_stateManager.ProcessRequests();
    RestartClock();
}


