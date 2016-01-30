#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "Pipe.h"
#include "Bird.h"
#include "Ground.h"
#include <CocosGUI.h>

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    
private:
    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
    void SpawnPipe( float dt);
    
    void SpawnGround( float dt);
    
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    
    // touch for fly
    bool onTouchBegin( cocos2d::Touch *touch, cocos2d::Event *event );
    
    void StopFlying( float dt );
    void update( float dt );
    
    void buttonEvent( cocos2d::Ref *sender, cocos2d::ui::Widget::TouchEventType type );
    
    cocos2d::PhysicsWorld *sceneWorld;
    
    Pipe pipe;
    Bird *bird;
    
    Ground ground;
    
    unsigned int score;
    
    unsigned int jump;
    
};

#endif // __GAME_SCENE_H__
