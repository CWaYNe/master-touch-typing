//
//  Key.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/5.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Key_hpp
#define Key_hpp
#include "SharedContext.hpp"
#include "RoundedRectangleShape.hpp"

enum class KeyType{ NORMAL, LONG_1, LONG_2, LONG_3, LONG_4, SPACE };

class Key{
public:
    Key(unsigned int l_id, KeyType l_type);
    ~Key();
    
    unsigned int GetId() const;
    KeyType GetType() const;
    
    void SetKey(sf::Vector2f position, const sf::Vector2f& keySize,
                const sf::String& keyLabel, const sf::Font& font);
    
    void Update(float l_DT);
    void Draw(sf::RenderWindow* l_wind);
    void Flicker();
    
private:
    unsigned int m_id; // keyboard index
    KeyType m_type;
    float m_elapsed;
    
    sf::RoundedRectangleShape m_key;
    sf::Text m_label;
};

#endif /* Key_hpp */
