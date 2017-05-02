//
//  Utilities.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/1.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Utilities_h
#define Utilities_h

#include <iostream>
#include <string>
#include <algorithm>
#include "ResourcePath.hpp"

namespace Utils{


#ifdef _WIN32
#include <windows.h>
#include <Shlwapi.h>
    inline std::string GetWorkingDirectory(){
        HMODULE hModule = GetModuleHandle(nullptr);
        if(hModule){
            char path[256];
            GetModuleFileName(hModule,path,sizeof(path));
            PathRemoveFileSpec(path);
            strcat_s(path,"\\");
            return std::string(path);
        }
        return "";
    }
#else
#include <unistd.h>
    inline std::string GetWorkingDirectory(){
        char cwd[1024];
        if(getcwd(cwd, sizeof(cwd)) != nullptr){
            return std::string(cwd) + std::string("/");
        }
        return "";
    }
#endif
    
}
#endif /* Utilities_h */
