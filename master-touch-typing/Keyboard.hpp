//
//  Keyboard.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/5.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Keyboard_hpp
#define Keyboard_hpp
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include "BaseState.hpp"
#include "Key.hpp"


using Keys = std::unordered_map<unsigned int, Key*>;

class Keyboard{
public:
    Keyboard(SharedContext* l_context, BaseState* l_currentState);
    ~Keyboard();
    
    unsigned int GetKeyId(unsigned int unicode)const;
    KeyType GetKeyType(unsigned int unicode)const;
    Keys GetKeys()const;
    
    
    void Update(float l_dT);
    void Draw();
private:
    void LoadKeys();
    void CreateSkeleton();
    void PurgeKeys();
    
    sf::RoundedRectangleShape m_keyboardContour;
    sf::Vector2f keyboardSize;
    
    
    BaseState* m_currentState;
    SharedContext* m_context;
    Keys m_keys;
};


#endif /* Keyboard_hpp */
