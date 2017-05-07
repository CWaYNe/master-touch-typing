//
//  Platform.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/7.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

// 2d platform where hero and boss battle

#ifndef Platform_hpp
#define Platform_hpp

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <map>
#include <array>
#include <fstream>
#include <sstream>
#include "Utilities.hpp"
#include "SharedContext.hpp"
#include "BaseState.hpp"

class Platform{
public:
    Platform(SharedContext* l_context, BaseState* l_currentState, const sf::Vector2u& l_position);
    ~Platform();
    
    // Load background
    void LoadBackground();
    void LoadNext();
    
    sf::FloatRect GetBackgroundBound() const;
    
    void Update(float l_dT);
    void Draw();

private:
    void PurgePlatform(); // purge current platform
    
    
    SharedContext* m_context;
    BaseState* m_currentState;
    
    
    bool m_nextStage;
    sf::Vector2u m_backgroundPosition;
    std::string m_backgroundTexture;
    
    
    sf::Sprite m_backgroundSprite;
    
};

#endif /* Platform_hpp */
