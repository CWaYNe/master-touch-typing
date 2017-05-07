//
//  State_Game.cpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/4.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#include "State_Game.hpp"
#include "StateManager.hpp"
#include <stdlib.h>

State_Game::State_Game(StateManager* l_stateManager): BaseState(l_stateManager), m_correct(false), m_shakeTimer(0.0f), PI(3.1415926f),
    m_boxSize(200.0f, 80.0f),
    m_defaultText(L"Input:"),
    m_correctTimer(0.0f){
    LoadGameData("gameData/stage1.gameData");
    itr2 = m_vocabulary.begin();
};

State_Game::~State_Game(){};

void State_Game::LoadGameData(const std::string& l_dataFile){
    std::wifstream vocabularyMapping;
    vocabularyMapping.open(resourcePath()+l_dataFile);
    std::cout << resourcePath() << std::endl;
    // TODO: Solve unicode problem
    if(vocabularyMapping.is_open()){
        std::wstring line;
        while(std::getline(vocabularyMapping, line)){
            if (line[0] == '|'){ continue; }
            std::wistringstream vocabularystream(line);
            std::wstring english, nativeLanguage, voc;
            bool i = true;
            while(std::getline(vocabularystream, voc, L'/')) {
                i ? english = voc : nativeLanguage = voc;
                i = false;
            }
            
            std::wcout << nativeLanguage << std::endl;
            m_vocabulary.insert(std::make_pair( english, nativeLanguage));
        }
    }
}

void State_Game::OnCreate(){
    
    sf::Vector2u windowSize = m_stateMgr->GetContext()
    ->m_wind->GetRenderWindow()->getSize();
    TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
    sf::FloatRect viewSpace = this->m_stateMgr->GetContext()->m_wind->GetViewSpace();
    
    textureMgr->RequireResource("GameStateBg");
    textureMgr->RequireResource("Correct");
    
    
    
    
    m_background.setTexture(*textureMgr->GetResource("GameStateBg"));
    
    sf::Vector2u platformPos(viewSpace.left, viewSpace.top);
    // set up game battle platform
    m_gamePlatform = new Platform(m_stateMgr->GetContext(), this, platformPos);
    
    
    
    m_background.setScale(windowSize.x/m_background.getLocalBounds().width, windowSize.y/m_background.getLocalBounds().height);

    m_background.setPosition(viewSpace.left, viewSpace.top);
    
    
    // set box position
    m_wordBoxPos = sf::Vector2f(windowSize.x / 2.0f, m_gamePlatform->GetBackgroundBound().height + m_boxSize.y / 2.0f + 30.0f);
    m_inputBoxPos = sf::Vector2f(windowSize.x / 2.0f, m_wordBoxPos.y + m_boxSize.y + 60.0f);
    
    // set correct image
    m_great.setTexture(*textureMgr->GetResource("Correct"));
    m_great.setColor(sf::Color::Color(0,240,0,0));
    m_great.setScale(m_boxSize.x / m_great.getLocalBounds().width, m_boxSize.x / m_great.getLocalBounds().width);
    m_great.setOrigin(m_great.getLocalBounds().width /2.0f, m_great.getLocalBounds().width / 2.0f);
    m_great.setPosition((m_wordBoxPos + m_inputBoxPos)/2.0f);
    
    // set box parameter
    m_WordBox.setSize(m_boxSize);
    m_WordBox.setFillColor(sf::Color::Color(5, 80, 140));
    m_WordBox.setCornersRadius(7.5f);
    m_WordBox.setCornerPointCount(8);
    m_WordBox.setOrigin(m_boxSize.x / 2.0f, m_boxSize.y / 2.0f);
    m_WordBox.setOutlineThickness(2.0f);
//    m_WordBox.setOutlineColor(sf::Color::Blue);
    m_WordBox.setPosition(m_wordBoxPos.x, m_wordBoxPos.y);
    
    
    m_InputBox.setSize(m_boxSize);
    m_InputBox.setFillColor(sf::Color::Color(5, 80, 140));
    m_InputBox.setCornersRadius(7.5f);
    m_InputBox.setCornerPointCount(8);
    m_InputBox.setOrigin(m_boxSize.x / 2.0f, m_boxSize.y / 2.0f);
    m_InputBox.setOutlineThickness(2.0f);
//    m_InputBox.setOutlineColor(sf::Color::Blue);
    m_InputBox.setPosition(m_inputBoxPos.x, m_inputBoxPos.y);
    
    
    m_font.loadFromFile(resourcePath() + "media/Fonts/NotoSansCJKtc-Bold.otf");
    m_text.setFont(m_font);
    m_text.setCharacterSize(36);
    m_text.setFillColor(sf::Color::White);
    m_text.setString(sf::String(m_defaultText + m_userInputs));
    
    m_word.setFont(m_font);
    m_word.setString(sf::String(itr2->first));
//    std::wcout << itr2->second << std::endl;
    m_word.setCharacterSize(36);
    m_word.setFillColor(sf::Color::White);
    
    
    sf::FloatRect wordRect = m_word.getLocalBounds();
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    m_word.setOrigin(wordRect.left + wordRect.width / 2.0f, wordRect.top + wordRect.height / 2.0f);
    
    m_text.setPosition(m_inputBoxPos.x, m_inputBoxPos.y);
    m_word.setPosition(m_wordBoxPos.x, m_wordBoxPos.y);
    m_defaultScale = m_text.getScale();
    
    // setup Keyboard
    m_keyboard = new Keyboard(m_stateMgr->GetContext(), this);
    
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Game, "Key_Escape", &State_Game::MainMenu, this);
    AddTypingCallback();
}

void State_Game::OnDestroy(){
    TextureManager* textureMgr = m_stateMgr->GetContext()->m_textureManager;
    textureMgr->ReleaseResource("GameStateBg");
    textureMgr->ReleaseResource("Correct");
    
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Game, "Key_Escape");
    RemoveTypingCallback();
    delete m_keyboard;
    m_keyboard = nullptr;
}

void State_Game::AddTypingCallback(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->AddCallback(StateType::Game, "Key_Typing", &State_Game::KeyPressed, this);
    evMgr->AddCallback(StateType::Game, "Key_Enter", &State_Game::EnterKeyPressed, this);
    evMgr->AddCallback(StateType::Game, "Press_L_SHIFT", &State_Game::PressedLShift,this);
    evMgr->AddCallback(StateType::Game, "Press_R_SHIFT", &State_Game::PressedRShift,this);
}

void State_Game::PressedLShift(EventDetails* l_details){
    auto itr = m_keyboard->GetKeys().find(41);
    itr->second->Flicker();
}
void State_Game::PressedRShift(EventDetails* l_details){
    auto itr = m_keyboard->GetKeys().find(52);
    itr->second->Flicker();
}


void State_Game::RemoveTypingCallback(){
    EventManager* evMgr = m_stateMgr->
    GetContext()->m_eventManager;
    evMgr->RemoveCallback(StateType::Game, "Key_Typing");
    evMgr->RemoveCallback(StateType::Game, "Key_Enter");
}

void State_Game::KeyPressed(EventDetails* l_details){
    if (l_details->m_textEntered == '\b'){
        if(!m_userInputs.empty())
            m_userInputs.erase(m_userInputs.size()-1, 1);
        auto itr = m_keyboard->GetKeys().find(13);
        itr->second->Flicker();
    }
    else if (l_details->m_textEntered < 128 && l_details->m_textEntered != 10){
        m_userInputs += static_cast<wchar_t>(l_details->m_textEntered);
        auto id = m_keyboard->GetKeyId(l_details->m_textEntered);
        if (id != 129){
            auto itr_key = m_keyboard->GetKeys().find(id);
            if (itr_key != m_keyboard->GetKeys().end()){
                itr_key->second->Flicker();
            }
        }
    }
}

void State_Game::EnterKeyPressed(EventDetails* l_details){
    auto itr = m_keyboard->GetKeys().find(40);
    itr->second->Flicker();
    if (m_userInputs == itr2->first){
        m_correct = true;
        m_userInputs = L"";
        m_text.setFillColor(sf::Color::White);
        m_correctTimer = 0.2f;
    } else{
        m_text.setFillColor(sf::Color::Red);
        m_shakeTimer = 0.4f;
    }
}


void State_Game::Update(const sf::Time& l_time){
    sf::Vector2u windowSize = m_stateMgr->GetContext()
    ->m_wind->GetRenderWindow()->getSize();
    
    if(m_correct && itr2 == m_vocabulary.end()){
        m_correct = false;
        m_stateMgr->SwitchTo(StateType::GameOver);
    }else if (m_correct){
        m_correct = false;
        if(++itr2 == m_vocabulary.end()){
            m_correct = true;
        }
        if (itr2 != m_vocabulary.end()){
            m_word.setString(sf::String(itr2->first));
            sf::FloatRect wordRect = m_word.getLocalBounds();
            m_word.setOrigin(wordRect.left + wordRect.width / 2.0f, wordRect.top + wordRect.height / 2.0f);
            m_word.setPosition(m_wordBoxPos);
            m_WordBox.setSize({wordRect.width + 20, m_boxSize.y});
            m_WordBox.setOrigin(wordRect.width / 2.0f + 10,m_boxSize.y / 2.0f);
            m_InputBox.setPosition(m_inputBoxPos.x, m_inputBoxPos.y);
        }
    }
    
    SharedContext* context = m_stateMgr->GetContext();
    m_text.setString(sf::String(m_defaultText + m_userInputs));
    
    sf::FloatRect textRect = m_text.getLocalBounds();
    m_text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
    
    m_text.setPosition(m_inputBoxPos);
    
    if (m_shakeTimer > 0.0f){
        m_shakeTimer -= l_time.asSeconds();
        float offset = rand() % 1 ? 1.5366 : -1.54642;
        m_text.move(offset,offset);
        m_text.setScale(m_text.getScale().x * 1.0004f, m_text.getScale().y * 1.0004f);
    }else {
        m_text.setRotation(0.0f);
        m_text.setScale(m_defaultScale);
    }
    
    if (m_correctTimer > 0.0f){
        m_correctTimer -= l_time.asSeconds();
        m_great.setColor(sf::Color::Color(0,240,0,200));
    }else {
        m_great.setColor(sf::Color::Color(0,240,0, 0));
    }
    
    sf::FloatRect inputBound = m_text.getLocalBounds();

    
    
    if (inputBound.width > m_boxSize.x){
        m_InputBox.setSize({inputBound.width + 20, m_boxSize.y});
        m_InputBox.setOrigin(inputBound.width / 2.0f + 10,m_boxSize.y / 2.0f);
        m_InputBox.setPosition(m_inputBoxPos.x, m_inputBoxPos.y);
    }
    m_gamePlatform->Update(l_time.asSeconds());
    m_keyboard->Update(l_time.asSeconds());
    
}

void State_Game::Draw(){
    sf::RenderWindow* window = m_stateMgr->GetContext()->m_wind->GetRenderWindow();
    window->draw(m_background);
    window->draw(m_WordBox);
    window->draw(m_InputBox);
    window->draw(m_word);
    window->draw(m_text);
    window->draw(m_great);
    m_gamePlatform->Draw();
    m_keyboard->Draw();
    
}

void State_Game::MainMenu(EventDetails* l_details){
    m_stateMgr->SwitchTo(StateType::MainMenu);
}

void State_Game::Pause(EventDetails *l_details){
    m_stateMgr->SwitchTo(StateType::Paused);
}

void State_Game::Activate(){}
void State_Game::Deactivate(){}
