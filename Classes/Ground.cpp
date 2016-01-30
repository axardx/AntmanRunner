#include "Ground.h"
#include "Definitions.h"
#include <iostream>

USING_NS_CC;

Ground::Ground() {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void Ground::createGround( cocos2d::Layer *layer )
{
    ground1 = Sprite::create( "iphone/ground.png" );
    ground2 = Sprite::create( "iphone/ground.png" );
    ground3 = Sprite::create( "iphone/ground.png" );
    // create ground body
    
    auto groundBody1 = PhysicsBody::createBox( ground1->getContentSize());
    auto groundBody2 = PhysicsBody::createBox( ground2->getContentSize());
    auto groundBody3 = PhysicsBody::createBox( ground3->getContentSize());
    
    // fix the ground
    groundBody1->setDynamic(false);
    groundBody2->setDynamic(false);
    groundBody3->setDynamic(false);
    
    // set collision
    groundBody1->setCollisionBitmask(GROUND_COLLISION_BITMASK);
    groundBody1->setContactTestBitmask(true);
    
    groundBody2->setCollisionBitmask(GROUND_COLLISION_BITMASK);
    groundBody2->setContactTestBitmask(true);
    
    groundBody3->setCollisionBitmask(GROUND_COLLISION_BITMASK);
    groundBody3->setContactTestBitmask(true);
    
    // provide physic body for ground
    ground1->setPhysicsBody( groundBody1);
    ground2->setPhysicsBody( groundBody2);
    ground3->setPhysicsBody( groundBody3);
    
    // set position
    ground1->setPosition( Point( origin.x + ground1->getContentSize().width * 0.5 , origin.y+10 ) );
    ground2->setPosition( Point( origin.x + ground1->getContentSize().width * 1.5 , origin.y+10 ) );
    ground3->setPosition( Point( origin.x + ground1->getContentSize().width * 2.5 , origin.y+10 ) );
    
    // show ground
    layer->addChild(ground1);
    layer->addChild(ground2);
    layer->addChild(ground3);
    
    auto groundAction1 = MoveBy::create( GROUND_MOVEMENT_SPEED * visibleSize.width, Point( -ground1->getContentSize().width, 0 ) );
    auto groundAction2 = MoveBy::create( GROUND_MOVEMENT_SPEED * visibleSize.width*2, Point( -ground1->getContentSize().width * 2, 0 ) );
    auto groundAction3 = MoveBy::create( GROUND_MOVEMENT_SPEED * visibleSize.width*3, Point( -ground1->getContentSize().width * 3, 0 ) );
    
    ground1->runAction( groundAction1);
    ground2->runAction( groundAction2);
    ground3->runAction( groundAction3);
    
    
}


void  Ground::SpawnGround( cocos2d::Layer *layer )
{
    /*
    CCLOG( "SPAWN GROUND");
    
    auto ground = Sprite::create( "iphone/ground.png" );
    // create ground body
    auto groundBody = PhysicsBody::createBox( ground->getContentSize());
    // fix the ground
    groundBody->setDynamic(false);
    
    // set collision
    groundBody->setCollisionBitmask(GROUND_COLLISION_BITMASK);
    groundBody->setContactTestBitmask(true);
    
    // provide physic body for ground
    ground->setPhysicsBody( groundBody);
    
    // set position
    ground->setPosition( Point( origin.x + visibleSize.width , origin.y+10 ) );
    
    // show ground
    layer->addChild(ground);
    
    //                                      0.17
    auto groundAction = MoveBy::create( GROUND_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
    ground->runAction( groundAction);
    */
    
    //                                      0.17
    
    if ( ground1->getPositionX() <= origin.x-ground1->getContentSize().width * 0.5 ) {
        ground1->setPosition( Point(  ground1->getContentSize().width * 2.5 , origin.y+10 ) );
        auto groundAction = MoveBy::create( GROUND_MOVEMENT_SPEED * visibleSize.width*3, Point( -ground1->getContentSize().width * 3, 0 ) );
        ground1->runAction( groundAction);
    }
    if ( ground2->getPositionX() <= origin.x-ground1->getContentSize().width * 0.5 ) {
        ground2->setPosition( Point( ground1->getContentSize().width * 2.5 , origin.y+10 ) );
        auto groundAction = MoveBy::create( GROUND_MOVEMENT_SPEED * visibleSize.width*3, Point( -ground1->getContentSize().width * 3, 0 ) );
        ground2->runAction( groundAction);
    }
    if ( ground3->getPositionX() <= origin.x-ground1->getContentSize().width * 0.5 ) {
        ground3->setPosition( Point( ground1->getContentSize().width * 2.5 , origin.y+10 ) );
        auto groundAction = MoveBy::create( GROUND_MOVEMENT_SPEED * visibleSize.width*3, Point( -ground1->getContentSize().width * 3, 0 ) );
        ground3->runAction( groundAction);
    }
    
/*
    // set collision
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    bottomPipeBody->setContactTestBitmask(true);
 
*/
    
}




