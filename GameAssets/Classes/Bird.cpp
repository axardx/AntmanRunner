#include "Bird.h"
#include "Definitions.h"

USING_NS_CC;

Bird::Bird( cocos2d::Layer *layer ) {
    
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    flappyBird = Sprite::create( "iphone/Ball_bigger.png" );
    flappyBird->setPosition( Point( visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y ) );
    
    // set physic body is just radius of the "Ball.png", not the whole ball size
    auto flappyBody = PhysicsBody::createCircle( flappyBird->getContentSize().width );
    
    // set collision
    flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappyBody->setContactTestBitmask(true);
    
    flappyBird->setPhysicsBody( flappyBody);
    
    // show flappy bird
    // 100 means zOrder: zOrder ->	Z order for drawing priority
    // z：是指添加的ZOrder值，ZOrder是指该成员的层级（也可以说深度），z值大的成员在z值小的成员的上面；
    layer->addChild( flappyBird, 100);
    
    big = true;

	yspeed = 0;
    
    isFalling = true;
}

void Bird::Fall()
{
	if (true == isFalling) {
		flappyBird->setPositionX(visibleSize.width / 2 + origin.x);

		flappyBird->setPositionY(flappyBird->getPositionY() + yspeed);
		yspeed = yspeed - BIRD_FALLING_ACC;
	}
        
  /*
        // if stcuk into the ground when falling down
        if ( flappyBird->getPositionY() < 60 )
            flappyBird->setPositionY( 60 );
   */
    
    
    /*else {
        flappyBird->setPositionX( visibleSize.width/2 + origin.x );
        //flappyBird->setPositionY( flappyBird->getPositionY() + ( BIRD_FALLING_SPEED*visibleSize.height ) );
        flappyBird->setPositionY( flappyBird->getPositionY() + ( 0.01*visibleSize.height ) );
		yspeed = 0;
    }*/
}

void Bird::Shrink_Magnify( cocos2d::Layer *layer )
{
    float x = flappyBird->getPositionX();
    float y = flappyBird->getPositionY();
    
    flappyBird->removeFromParent();
    
    if ( big == true ) {
        flappyBird = Sprite::create( "iphone/Ball.png" );
        big = false;
    }
    else {
        flappyBird = Sprite::create( "iphone/Ball_bigger.png" );
        big = true;
    }
    
    flappyBird->setPosition( Point( x, y ) );
        
    // set physic body is just radius of the "Ball.png", not the whole ball size
    auto flappyBody = PhysicsBody::createCircle( flappyBird->getContentSize().width );
    
    // set collision
    flappyBody->setCollisionBitmask(BIRD_COLLISION_BITMASK);
    flappyBody->setContactTestBitmask(true);
    
    flappyBird->setPhysicsBody( flappyBody);
    
    // show bird
    layer->addChild( flappyBird, 100);
}

void Bird::UpOffset()
{
    // if stcuk into the ground when falling down
   // flappyBird->setPositionY( flappyBird->getPositionY() + 10 );
	isFalling = false;
	//flappyBird->setPositionX(visibleSize.width / 2 + origin.x);
	//flappyBird->setPositionY(flappyBird->getPositionY() + (0.01*visibleSize.height));
	yspeed = 0;
}


/*
#define BIRD_FALLING_SPEED 0.0025
#define BIRD_FLYING_SPEED 0.00475
#define BIRD_FLY_DURATION 0.25
*/





