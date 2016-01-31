#include "Pipe.h"
#include "Definitions.h"
#include <iostream>

USING_NS_CC;

Pipe::Pipe() {
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
}

void  Pipe::SpawnPipe( cocos2d::Layer *layer )
{
    CCLOG( "SPAWN PIPE");
    
    // build pipe barrier based on the "pipe.png", create the body
    auto topPipe = Sprite::create( "iphone/Pipe.png" );
    auto bottomPipe = Sprite::create( "iphone/Pipe.png" );
    
    auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize());
    auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize());
    
    // random = 0.35 ~ 0.65, in order to random create the position of y
    auto random = CCRANDOM_0_1();
    
    if ( random < LOWER_SCREEN_PIPE_THRESHOLD ) {
        random = LOWER_SCREEN_PIPE_THRESHOLD;
    }
    else if ( random > UPPER_SCREEN_PIPE_THRESHOLD ) {
        random = UPPER_SCREEN_PIPE_THRESHOLD;
    }
    
    // find pipe's random y coordinate in screen
    auto topPipePosition = ( random * visibleSize.height ) + ( topPipe->getContentSize().height / 2 );
    
    // std::cout << topPipePosition << "\n";
    // std::cout << visibleSize.width << "  " << visibleSize.height << std::endl;
    
    // let pipe fix on the screen position, otherwise it will fall to the bottom and fall aside
    // haing gravity
    topPipeBody->setDynamic(false);
    bottomPipeBody->setDynamic(false);
    
    // set collision
    topPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    bottomPipeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    topPipeBody->setContactTestBitmask(true);
    bottomPipeBody->setContactTestBitmask(true);
    
    // provide physicbody for pipe
    topPipe->setPhysicsBody( topPipeBody);
    bottomPipe->setPhysicsBody( bottomPipeBody);
    
    
    /*
    // set pipe position            480/2 = 240      +          30/2 = 15
    topPipe->setPosition( Point( visibleSize.width/2 + topPipe->getContentSize().width + origin.x + CCRANDOM_MINUS1_1()*250, topPipePosition ) );
    */
    topPipe->setPosition( Point( visibleSize.width + topPipe->getContentSize().width + origin.x, topPipePosition ) );
    
    
    // the same as topPipe, find the (x, y) coordinate, and put the "pipe.png" on that point
    // so based on that point, the image will show on the top-right of that point
    // x should be the same as topPipe
    // y would be lower baed on a gap which can let bird fly through
    // gap is calculated by small ball's radius * 10
    bottomPipe->setPosition( Point( topPipe->getPositionX(), topPipePosition - ( Sprite::create( "iphone/Ball.png" )->getContentSize().height * PIPE_GAP ) - topPipe->getContentSize().height ) );
    
    // std::cout << topPipe->getPositionX() << "\n";
    
    // show the pipe
//    layer->addChild( topPipe);
    layer->addChild( bottomPipe);
    
    // moveby::create(<#float duration#>, <#const cocos2d::Vec2 &deltaPosition#>)
    // duration means 運動週期 // 移动持续时间/秒
    // deltaPosition:移动到当前坐标+增量坐标的位置
    // var actionTo = cc.MoveBy.create(2, cc.p(40, 40));//当前坐标为x,y ,2秒移动到x+40,y+40
    //
    // fix the background, move the pipe one time 0.01*screen's width.
    // the value of 1.5 : the higher means faster when moving the pipe
    // make different of top and bottom, can create the time gap of two pipes
//    auto topPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    auto bottomPipeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
//    topPipe->runAction( topPipeAction);
    bottomPipe->runAction( bottomPipeAction);
    
    
    // set score
    auto pointNode = Node::create();
    auto pointBody = PhysicsBody::createBox( Size(1, Sprite::create("iphone/Ball.png")->getContentSize().height * PIPE_GAP ));
    
    pointBody->setDynamic(false);
    pointBody->setCollisionBitmask( POINT_COLLISION_BITMASK);
    pointBody->setContactTestBitmask(true);
 
    pointNode->setPhysicsBody(pointBody);
    // ?????????????????????????????????????
    pointNode->setPosition( Point( topPipe->getPositionX(), topPipe->getPositionY() - ( topPipe->getContentSize().height /2 ) - ( ( Sprite::create("iphone/Ball.png")->getContentSize().height * PIPE_GAP ) / 2 ) ));
    
    std::cout <<topPipe->getPositionX() << "  " << topPipe->getPositionY() << "   " << topPipe->getContentSize().height << "\n";
    
    layer->addChild(pointNode);
    
    auto pointNodeAction = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Point( -visibleSize.width * 1.5, 0 ) );
    
    pointNode->runAction(pointNodeAction);
}




