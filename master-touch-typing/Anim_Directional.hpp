//
//  Anim_Directional.hpp
//  master-touch-typing
//
//  Created by Wayne Chang on 2017/5/1.
//  Copyright © 2017年 WayneChang. All rights reserved.
//

#ifndef Anim_Directional_hpp
#define Anim_Directional_hpp

#include "Anim_Base.hpp"
#include "Directions.hpp"

class Anim_Directional : public Anim_Base{
protected:
    void FrameStep();
    void CropSprite();
    void ReadIn(std::stringstream& l_stream);
};

#endif /* Anim_Directional_hpp */
