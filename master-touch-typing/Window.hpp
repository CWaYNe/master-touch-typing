//
//  Header.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/26.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Window_h
#define Window_h

#include <string>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "EventManager.hpp"

class Window{
public:
    Window();
    Window(const std::string& l_title, const sf::Vector2u& l_size);
    ~Window();
    
    void BeginDraw(); // Clear the window
    void EndDraw();   // Display the changes
    
    void Update();
    
    bool IsDone();
    bool IsFullscreen();
    bool IsFocused();
    
    void ToggleFullscreen(EventDetails* l_details);
    void Close(EventDetails* l_details = nullptr);
    
    sf::RenderWindow* GetRenderWindow();
    EventManager* GetEventManager();
    sf::Vector2u GetWindowSize();
    
    
//    void Draw(sf::Drawable& l_drawable);
private:
    void Setup(const std::string& l_title, const sf::Vector2u& l_size);
//    void Destroy();
    void Create();
    
    sf::RenderWindow m_window;
    EventManager m_eventManager;
    sf::Vector2u m_windowSize;
    std::string m_windowTitle;
    bool m_isDone;
    bool m_isFullscreen;
    bool m_isFocused;
};


#endif /* Window_h */
