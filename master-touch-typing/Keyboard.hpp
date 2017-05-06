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

using Unicode_code = unsigned int;
using Key_id = unsigned int;


using KeyMapping = std::unordered_map<Unicode_code, Key_id>;
using Keys = std::unordered_map<Key_id, Key*>;


class Keyboard{
public:
    Keyboard(SharedContext* l_context, BaseState* l_currentState);
    ~Keyboard();
    
    unsigned int GetKeyId(Unicode_code unicode)const;
    KeyType GetKeyType(Key_id unicode)const;
    Keys GetKeys()const;
    
    
    void Update(float l_dT);
    void Draw();
private:
    void LoadKeys(const std::string& l_keyFile); // load keymapping then m_keys
    void InitKeyWidthMapping();
    void CreateSkeleton();
    void PurgeKeys();
    
    sf::Font m_font;
    
    sf::RoundedRectangleShape m_keyboardSkeleton;
    sf::Vector2f keyboardSize;
    
    std::unordered_map<KeyType, float, EnumClassHash> widthMapping;
    BaseState* m_currentState;
    SharedContext* m_context;
    KeyMapping m_key_mapping;
    Keys m_keys;
};


#endif /* Keyboard_hpp */
