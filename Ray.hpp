//
//  Ray.hpp
//  Ray Tracer
//
//  Created by Peter Sandquist on 6/12/18.
//  Copyright © 2018 Peter Sandquist. All rights reserved.
//

#ifndef Ray_hpp
#define Ray_hpp
#define accuracy 0.001f

#include <stdio.h>
#include "Vec3.hpp"
#include <cmath>
template<typename T>
class Ray{
public:
    Ray(Vec3<T> Pos, Vec3<T> Vec){e[0] = Pos; e[1] = Vec;}
    
    inline Vec3<T> Pos()const{
        return e[0];
    }
    inline Vec3<T> Vec()const{
        return e[1];
    }
    
    Vec3<T> e[2];
};
#endif /* Ray_hpp */
