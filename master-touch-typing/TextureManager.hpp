//
//  TextureManager.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/1.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef TextureManager_h
#define TextureManager_h
#include "ResourceManager.hpp"
#include <SFML/Graphics/Texture.hpp>

class TextureManager: public ResourceManager<TextureManager, sf::Texture>{
public:
    TextureManager(): ResourceManager("textures.cfg"){}
    
    sf::Texture* Load(const std::string& l_path){
        sf::Texture* texture = new sf::Texture();
        if(!texture->loadFromFile(
                                  resourcePath() + l_path))
        {
            delete texture;
            texture = nullptr;
            std::cerr << "! Failed to load texture: "
            << l_path << std::endl;
        }
        return texture;
    }
};

#endif /* TextureManager_h */
