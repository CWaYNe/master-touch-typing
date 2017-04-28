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
    KeyDown = sf::Event::KeyPressed,
    KeyUp = sf::Event::KeyReleased,
    MButtonDown = sf::Event::MouseButtonPressed,
    MButtonUp = sf::Event::MouseButtonReleased,
    MouseWheel = sf::Event::MouseWheelMoved,
    WindowResized = sf::Event::Resized,
    GainedFocus = sf::Event::GainedFocus,
    LostFocus = sf::Event::LostFocus,
    MouseEntered = sf::Event::MouseEntered,
    MouseLeft = sf::Event::MouseLeft,
    Closed = sf::Event::Closed,
    TextEntered = sf::Event::TextEntered,
    Keyboard = sf::Event::Count + 1, // the total number of event types
    Mouse, Joystick
};


// each event may have a event_code, if no defaulted to 0
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
        m_keyCode = -1; // unknown
    }
};


using Events = std::vector<std::pair<EventType, EventInfo>>;




// A single binding
struct Binding{
    Binding(const std::string& l_name): m_name(l_name), m_details(l_name), c(0){}
    void BindEvent(EventType l_type, EventInfo l_info = EventInfo()){
        m_events.emplace_back(l_type, l_info);
    }
    
    Events m_events;
    std::string m_name;
    int c; // Count of events that are "happening".
    
    EventDetails m_details;
};

// key bindings, using map to evade duplication
using Bindings = std::unordered_map<std::string, Binding*>;

using CallbackContainer = std::unordered_map<std::string, std::function<void (EventDetails*)>>;

// bindingd callback function, also using map to evade duplication
enum class StateType;

//namespace std {
//    template<>
//    struct hash<StateType> {
//        size_t operator()(const StateType &type) const {
//            return std::hash<int>()(static_cast<int>(type));
//        }
//    };
//}

struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(T t) const
    {
        return static_cast<std::size_t>(t);
    }
};

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
//        return m_callbacks.emplace(l_name, temp).second;
    }
    
    void RemoveCallback(StateType l_state, const std::string& l_name);
    
    void HandleEvent(sf::Event& l_event);
    void Update();
    
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
