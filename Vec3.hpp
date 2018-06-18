//
//  Vec3.hpp
//  Ray Tracer
//
//  Created by Peter Sandquist on 6/11/18.
//  Copyright © 2018 Peter Sandquist. All rights reserved.
//

#ifndef Vec3_hpp
#define Vec3_hpp

#include <stdio.h>
#include <iostream>



template <typename T>
class Vec3{
public:
    Vec3(){ e[0] = T(0); e[1] = T(0); e[2] = T(0);}
    Vec3(T x, T y, T z){ e[0] = x; e[1] = y; e[2] = z;}
    
    
    inline T x()const{return e[0];}
    inline T y()const{return e[1];}
    inline T z()const{return e[2];}
    
    
    //functions
    inline T Dot(const Vec3<T> &v) const { return e[0] * v[0] + e[1] * v[1] + e[2] * v[2];}
    inline Vec3<T> Cross(const Vec3<T> &v){
        return Vec3<T>(e[1] * v[2] - e[2] * v[1], e[2] * v[0] - e[0] * v[2], e[0] * v[1] - e[1] * v[0]);
    }
    inline T length()const{return sqrt(e[0]*e[0] + e[1]*e[1] + e[2]*e[2]);}
    void Normalize(){
        if(this->length() > 0){
            T inverseLength = 1 / sqrt(Dot(*this));
            e[0] *= inverseLength; e[1] *= inverseLength; e[2] *= inverseLength;
        }
    }

    
    void Print(){
        std::cout << e[0] << ", " << e[1] << ", " << e[2] << std::endl;
    }
    
    
    //operators
    inline T operator[](int i)const{
        return e[i];
    }
    inline Vec3<T> operator-(const Vec3<T> &v) const{
        return Vec3<T>(e[0] - v[0],e[1] - v[1], e[2] - v[2]);
    }
    inline Vec3<T> operator+(const Vec3<T> &v) const{
        return Vec3<T>(e[0] + v[0],e[1] + v[1], e[2] + v[2]);
    }
    
    inline Vec3<T> operator/(const Vec3<T> &v)const{
        return Vec3<T>(e[0] / v[0], e[1] / v[1], e[2] / v[2]);
    }
    
    inline Vec3<T> operator*(const Vec3<T> &v)const{
        return Vec3<T>(e[0] * v[0], e[1] * v[1], e[2] * v[2]);
    }
    
    inline Vec3<T> operator*(const T t) const{
        return Vec3<T>(e[0] * t, e[1] * t, e[2] * t);
    }
    
    inline Vec3<T> operator/(const T t) const{
        return Vec3<T>(e[0] / t, e[1] / t, e[2] / t);
    }
    
    //members
    T e[3];
};
template <typename T>
inline Vec3<T> NormalOfTri(Vec3<T> a, Vec3<T> b, Vec3<T> c){
    return (a - c).Cross(a - b);
}

#endif /* Vec3_hpp */
