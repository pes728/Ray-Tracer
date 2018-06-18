//
//  RayCast.hpp
//  Ray Tracer
//
//  Created by Peter Sandquist on 6/12/18.
//  Copyright © 2018 Peter Sandquist. All rights reserved.
//

#ifndef RayCast_hpp
#define RayCast_hpp

#include <stdio.h>
#include "Vec3.hpp"
#include "Ray.hpp"
class RayCast{
public:
template<typename T>
inline float Area(const Vec3<T> &a,const Vec3<T> &b,const Vec3<T> &c) {return abs(a.y() * (b.z() - c.z()) + b.y() * (c.z() - a.z()) +  c.y() * (a.z() - b.z()))/2;}

template <typename T>
    bool rayCast(const Vec3<T> &a, const Vec3<T> &b, const Vec3<T> &c, const Vec3<T> &pos, const Vec3<T> &vec, Vec3<T> &hitPoint){
    Vec3<T> n = NormalOfTri(a, b, c);
    float d = ((a - pos).Dot(n)) / vec.Dot(n);
    Vec3<T> point = pos + vec * d;
    if(Area(a, b, c) == Area(point, a, b) + Area(point, b, c) + Area(point, c,a))
    {
        hitPoint = point;
        return true;
        }else return false;
    }
};


#endif /* RayCast_hpp */
