//
//  EventManager.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/4/26.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef EventManager_hpp
#define EventManager_hpp

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <sstream>
#include <iostream>


enum class EventType{
    KeyDown = sf::Event::KeyPressed,// 5
    KeyUp = sf::Event::KeyReleased,// 6
    MButtonDown = sf::Event::MouseButtonPressed,//8
    MButtonUp = sf::Event::MouseButtonReleased,//9
    MouseWheel = sf::Event::MouseWheelMoved,//7
    WindowResized = sf::Event::Resized,//1
    GainedFocus = sf::Event::GainedFocus,//3
    LostFocus = sf::Event::LostFocus,//2
    MouseEntered = sf::Event::MouseEntered,//11
    MouseLeft = sf::Event::MouseLeft,//12
    Closed = sf::Event::Closed,//0
    TextEntered = sf::Event::TextEntered,//4
    Keyboard = sf::Event::Count + 1, //25
    Mouse,//26
    Joystick //27
};

struct EventInfo{
    EventInfo(){ m_code = 0; }
    EventInfo(int l_event){ m_code = l_event; }
    union{
        int m_code;
    };
};

struct EventDetails{
    EventDetails(const std::string& l_bindName)
    : m_name(l_bindName){
        Clear();
    }
    std::string m_name;
    
    sf::Vector2i m_size;
    sf::Uint32 m_textEntered;
    sf::Vector2i m_mouse;
    int m_mouseWheelDelta;
    int m_keyCode; // Single key code.
    
    void Clear(){
        m_size = sf::Vector2i(0, 0);
        m_textEntered = 0;
        m_mouse = sf::Vector2i(0, 0);
        m_mouseWheelDelta = 0;
        m_keyCode = -1;
    }
};

using Events = std::vector<std::pair<EventType, EventInfo>>;

struct Binding{
    Binding(const std::string& l_name) : m_name(l_name), m_details(l_name), c(0){}
    ~Binding(){}
    // Bind event from keys.cfg
    void BindEvent(EventType l_type, EventInfo l_info = EventInfo()){
        m_events.emplace_back(l_type, l_info);
    }
    
    Events m_events;
    std::string m_name;
    int c; // Count of events that are "happening".
    
    EventDetails m_details;
};


enum class StateType;
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};



using Bindings = std::unordered_map<std::string, Binding*>;
// Callback container.
using CallbackContainer = std::unordered_map<std::string, std::function<void(EventDetails*)>>;
// State callback container.
using Callbacks = std::unordered_map<StateType, CallbackContainer, EnumClassHash>;

class EventManager{
public:
    EventManager();
    ~EventManager();
    
    bool AddBinding(Binding *l_binding);
    bool RemoveBinding(std::string l_name);
    
    void SetCurrentState(StateType l_state);
    void SetFocus(const bool& l_focus);
    
    // Needs to be defined in the header!
    template<class T>
    bool AddCallback(StateType l_state, const std::string& l_name,
                     void(T::*l_func)(EventDetails*), T* l_instance)
    {
        auto itr = m_callbacks.emplace(l_state, CallbackContainer()).first;
        auto temp = std::bind(l_func, l_instance, std::placeholders::_1);
        return itr->second.emplace(l_name, temp).second;
    }
    
    bool RemoveCallback(StateType l_state, const std::string& l_name){
        auto itr = m_callbacks.find(l_state);
        if (itr == m_callbacks.end()){ return false; }
        auto itr2 = itr->second.find(l_name);
        if (itr2 == itr->second.end()){ return false; }
        itr->second.erase(l_name);
        return true;
    }
    
    void HandleEvent(sf::Event& l_event);
    void Update();
    
    // Getters.
    sf::Vector2i GetMousePos(sf::RenderWindow* l_wind = nullptr){
        return (l_wind ? sf::Mouse::getPosition(*l_wind) : sf::Mouse::getPosition());
    }
private:
    void LoadBindings();
    
    StateType m_currentState;
    Bindings m_bindings;
    Callbacks m_callbacks;
    
    bool m_hasFocus;
};

#endif /* EventManager_hpp */
