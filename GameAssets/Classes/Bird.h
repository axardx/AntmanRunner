#ifndef __BIRD_H__
#define __BIRD_H__

#include "cocos2d.h"

class Bird
{
public:
    
    Bird( cocos2d::Layer *layer );
    
    // touch and fly 
    void Fall( );
    // void Fly( ) { isFalling = false; }
    
    void Fly( ) {
        //JumpBy::create(<#float duration#>, <#const cocos2d::Vec2 &position#>, <#float height#>, <#int jumps#>)
		isFalling = true;
		yspeed = 3;
    }
    
    void StopFlying( ) { isFalling = true; }
    
    void Shrink_Magnify( cocos2d::Layer *layer );
    
    void UpOffset();
    
private:
    cocos2d::Size visibleSize;
    cocos2d::Vec2 origin;
    
    cocos2d::Sprite *flappyBird;

	float yspeed;
    
    bool isFalling;
    
    bool big;
};

#endif // __BIRD_H__
