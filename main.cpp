#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "Vec3.hpp"
#include "Ray.hpp"
#include "RayCast.hpp"
/*
 //Documention because that's a thing
 //Axis Definition
 //X = Forward, Y = Right, Z = Up
 */
#define WIDTH 255
#define HEIGHT 255

#define NEARCLIPPINGPLANE 2
typedef Vec3<float> Vec3f;
float FOV = 60;
sf::Texture screen;
sf::Uint8* ColorBuffer;

inline void addPixel(int x, int y, float r = 0, float g = 0, float b = 0, float a = 255){
    ColorBuffer[(x + y*WIDTH) * 4 + 0] += r;
    ColorBuffer[(x + y*WIDTH) * 4 + 1] += g;
    ColorBuffer[(x + y*WIDTH) * 4 + 2] += b;
    ColorBuffer[(x + y*WIDTH) * 4 + 3] += a;
}

inline void addPixel(int x, int y, Vec3f color, float a = 255){
    ColorBuffer[(x + y*WIDTH) * 4 + 0] += color.x();
    ColorBuffer[(x + y*WIDTH) * 4 + 1] += color.y();
    ColorBuffer[(x + y*WIDTH) * 4 + 2] += color.z();
    ColorBuffer[(x + y*WIDTH) * 4 + 3] += a;
}

inline void setPixel(int x, int y, float r = 0, float g = 0, float b = 0, float a = 255){
    ColorBuffer[(x + y*WIDTH) * 4 + 0] = r;
    ColorBuffer[(x + y*WIDTH) * 4 + 1] = g;
    ColorBuffer[(x + y*WIDTH) * 4 + 2] = b;
    ColorBuffer[(x + y*WIDTH) * 4 + 3] = a;
}

inline void setPixel(int x, int y, Vec3f color, float a = 255){
    ColorBuffer[(x + y*WIDTH) * 4 + 0] = color.x();
    ColorBuffer[(x + y*WIDTH) * 4 + 1] = color.y();
    ColorBuffer[(x + y*WIDTH) * 4 + 2] = color.z();
    ColorBuffer[(x + y*WIDTH) * 4 + 3] = a;
}

inline void Clear(){
    for(int y =0; y < HEIGHT; y++){
        for(int x = 0; x < WIDTH; x++){
            ColorBuffer[(x + y*WIDTH) * 4 + 0] = 0;
            ColorBuffer[(x + y*WIDTH) * 4 + 1] = 0;
            ColorBuffer[(x + y*WIDTH) * 4 + 2] = 0;
            ColorBuffer[(x + y*WIDTH) * 4 + 3] = 0;
        }
    }
}

int main(){
    //setup sf variables
    ColorBuffer = new sf::Uint8[WIDTH*HEIGHT*4];
    screen.create(WIDTH, HEIGHT);
    sf::RenderWindow window(sf::VideoMode(WIDTH,HEIGHT), "Rasterizer", sf::Style::Close);
    sf::Sprite mSprite;
    mSprite.setTexture(screen);
    sf::Event evnt;
    Vec3f tri[3] = {Vec3f(20,20,20),Vec3f(0,200,0),Vec3f(0,0,200)};
    
    Ray<float> camera(Vec3f(-10,0,0), Vec3f(1,0,0));
    Vec3f hitPoint;
    RayCast r;
    while(window.isOpen()){
        Clear();
        sf::Clock clock;
        Vec3f color(255,0,0);
        for(int y = 0; y < HEIGHT; y++){
            for(int x = 0; x <WIDTH; x++){
                //orthographic
                Vec3f screenVec (camera.Vec() + Vec3f(NEARCLIPPINGPLANE,x,y));
                screenVec.Normalize();
                if(r.rayCast(tri[0], tri[1], tri[2], camera.Pos(), screenVec, hitPoint)){
                    setPixel(x,y,color);
                    //anti-aliasing
                    addPixel(x + 1, y, color/2);
                    addPixel(x - 1, y, color/2);
                    addPixel(x, y + 1, color/2);
                    addPixel(x, y - 1, color/2);
                }else{
                    ColorBuffer[(x + y * WIDTH) * 4 + 3] = 255;
                }
            }
        }
        std::cout << clock.restart().asMilliseconds() << std::endl;
        //push render to screen
        screen.update(ColorBuffer);
        
        while(window.pollEvent(evnt)){
            switch(evnt.type){
                case sf::Event::Closed:
                    window.close();
                    break;
                    case sf::Event::KeyPressed:
                        switch(evnt.key.code){
                            case sf::Keyboard::Escape:
                                window.close();
                                break;
                        }
                    break;
            }
        }
        window.clear(sf::Color::Black);
        
        window.draw(mSprite);
        
        window.display();
        
        
        //std::cout << clock.restart().asMilliseconds() << std::endl;
    }
}

