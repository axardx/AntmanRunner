#include "GameScene.h"
#include "Definitions.h"
#include "GameOverScene.h"
#include "ui/CocosGUI.h"

using namespace cocos2d::ui;

USING_NS_CC;

Scene* GameScene::createScene()
{
    
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL);
    
    // set gravity
    scene->getPhysicsWorld()->setGravity( Vec2(0, 0));
    
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld( ));

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // set up background image
    auto backgroundSprite = Sprite::create("iphone/Background.png");
    backgroundSprite->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    
    this->addChild(backgroundSprite);
    
    // set edgeBox
    auto edgeBody = PhysicsBody::createEdgeBox( visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
    // set collision
    edgeBody->setCollisionBitmask(OBSTACLE_COLLISION_BITMASK);
    // if set true : when bird collide the ground or any edge, it will switch to gameover scene
    // if set false : it will bound from the ground when collide the ground
    edgeBody->setContactTestBitmask(true);
    
    
    auto edgeNode = Node::create();
    edgeNode->setPosition( Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y) );
    
    edgeNode->setPhysicsBody(edgeBody);
    
    this->addChild(edgeNode);
    

    // set pipe, which means obstacle
    this->schedule( schedule_selector( GameScene::SpawnPipe ), PIPE_SPAWN_FREQUENCY*visibleSize.width );
    
    ground.createGround(this);
    // set ground                                                   1
    this->schedule( schedule_selector( GameScene::SpawnGround ));
    
    // set bird 
    // "this" means layer
    bird = new Bird(this);
    
    // set collision
    auto contactListener = EventListenerPhysicsContact::create( );
    contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    //
    // set button for shrink and magnify
    //
    Button *btn = Button::create( "iphone/Play Button.png", "iphone/Play Button Clicked.png" );
    btn->setPosition(Vec2(100,100));
    // btn->setPosition( Point( visibleSize.width/2 + origin.x, visibleSize.height /2  ));
    
    btn->addTouchEventListener(CC_CALLBACK_2(GameScene::buttonEvent, this));
    this->addChild(btn);
    
    
    // set movement when touch the screen
    // auto touchListener = EventListenerTouchAllAtOnce::create();
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches( true );
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegin, this);
    Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority( touchListener, this);
    
    // initialize score
    score = 0;
    
    jump = 1;
    
    // it will automatically call the function "void GameScene:: update( float dt )"
    this->scheduleUpdate( );
    
    return true;
}

void GameScene::SpawnPipe(float dt)
{
    pipe.SpawnPipe( this );
}

bool GameScene::onContactBegin( cocos2d::PhysicsContact &contact )
{
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && OBSTACLE_COLLISION_BITMASK == a->getCollisionBitmask() ) ) {
        
        CCLOG("SCORE: %i", score);
        
        auto scene = GameOverScene::createScene();
        Director::getInstance()->replaceScene(TransitionFade::create( TRANSITION_TIME, scene ));
    }
    
    else if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && POINT_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && POINT_COLLISION_BITMASK == a->getCollisionBitmask() ) ) {
        
        CCLOG( "Point Scored");
        score++;
        
    }
    
    // wait until touch the ground, then bird can jump again
    if ( ( BIRD_COLLISION_BITMASK == a->getCollisionBitmask() && GROUND_COLLISION_BITMASK == b->getCollisionBitmask() ) || ( BIRD_COLLISION_BITMASK == b->getCollisionBitmask() && GROUND_COLLISION_BITMASK == a->getCollisionBitmask() ) ) {
        
        
        // if ( jump > 0 )
            bird->UpOffset();
        
        jump = 0;
        
    }
    
    return true;
}

bool GameScene::onTouchBegin( cocos2d::Touch *touch, cocos2d::Event *event )
{
    // only jump twice
    jump++;
    if ( jump > 2 ) {
        this->scheduleOnce( schedule_selector( GameScene::StopFlying ), BIRD_FLY_DURATION);
        return true;
    }
    bird->Fly( );
    
    this->scheduleOnce( schedule_selector( GameScene::StopFlying ), BIRD_FLY_DURATION);
    
    return true;
}

void GameScene::StopFlying( float dt )
{
    bird->StopFlying();
}
void GameScene:: update( float dt )
{
    bird->Fall();
}

// ground
void GameScene::SpawnGround(float dt)
{
    ground.SpawnGround( this );
}

void GameScene::buttonEvent( cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type )
{
    cocos2d::ui::Button* button = dynamic_cast<ui::Button*>(sender);
    
    if ( type == ui::Widget::TouchEventType::BEGAN ) {
        bird->Shrink_Magnify( this );
    }
/*
    switch (type)
    {
        case ui::Widget::TouchEventType::BEGAN://按下时
            
            break;
        case ui::Widget::TouchEventType::MOVED: //按着并移动时
            break;
        case ui::Widget::TouchEventType::ENDED: //按下后，并在按钮的范围内释放，最常用的。
            break;
        case ui::Widget::TouchEventType::CANCELED: //按下后，在按钮以外的地方释放
            break;
        default:
            break;
    }
*/
}






