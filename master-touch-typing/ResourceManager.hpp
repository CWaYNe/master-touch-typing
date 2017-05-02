//
//  ResourceManager.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/1.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef ResourceManager_hpp
#define ResourceManager_hpp
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Utilities.hpp"

template<typename Derived, typename T>
class ResourceManager{
public:
    ResourceManager(const std::string& l_pathsFile){
        LoadPaths(l_pathsFile);
    }
    
    virtual ~ResourceManager(){ PurgeResources(); }
    
    T* GetResource(const std::string& l_id){
        auto res = Find(l_id);
        return(res ? res->first : nullptr);
    }
    
    std::string GetPath(const std::string& l_id){
        auto path = m_paths.find(l_id);
        return(path != m_paths.end() ? path->second : "");
    }
    
    bool RequireResource(const std::string& l_id){
        auto res = Find(l_id);
        if(res){
            ++res->second;
            return true;
        }
        auto path = m_paths.find(l_id);
        if (path == m_paths.end()){ return false; }
        T* resource = Load(path->second);
        if (!resource){ return false; }
        m_resources.emplace(l_id, std::make_pair(resource, 1));
        return true;
    }
    bool ReleaseResource(const std::string& l_id){
        auto res = Find(l_id);
        if(!res){ return false; }
        --res->second;
        if (!res->second){ Unload(l_id); }
        return true;
    }
    
    void PurgeResources(){
        while (m_resources.begin() != m_resources.end()) {
            delete m_resources.begin()->second.first;
            m_resources.erase(m_resources.begin());
        }
    }
protected:
    //Derived classes will implement their own versions of Load, but will not rely on resolving virtual pointers to functions during run-time.
    T* Load(const std::string& l_path){
        return static_cast<Derived*>(this)->Load(l_path);
    }
private:
    bool Unload(const std::string& l_id){
        auto itr = m_resources.find(l_id);
        if (itr == m_resources.end()){  return false; }
        delete itr->second.first;
        m_resources.erase(itr);
        return true;
    }
    
    std::pair<T*, unsigned int>* Find(const std::string& l_id){
        auto itr = m_resources.find(l_id);
        return (itr != m_resources.end() ? &itr->second : nullptr);
    }
    
    void LoadPaths(const std::string& l_pathFile){
        std::ifstream paths;
        paths.open(resourcePath() + "assets/" + l_pathFile);
        if(paths.is_open()){
            std::string line;
            while(std::getline(paths,line)){
                std::stringstream keystream(line);
                std::string pathName;
                std::string path;
                keystream >> pathName;
                keystream >> path;
                m_paths.emplace(pathName, path);
            }
            paths.close();
            return;
        }
        std::cerr << "! Failed loading the path file:" << l_pathFile << std::endl;
    }
    
    //With that being said, let's talk about the m_resources data member. It's using a map, which is going to tie a string handle to a pair of elements, the first of which is the template parameter of a resource and the second is an unsigned integer type that will be used as a counter for how many places are currently using this particular resource.
    std::unordered_map<std::string, std::pair<T*, unsigned int>> m_resources;
    std::unordered_map<std::string, std::string> m_paths;
};

#endif /* ResourceManager_hpp */
