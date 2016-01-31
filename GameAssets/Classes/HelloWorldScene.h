#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void update(float) override;

private:
	cocos2d::Sprite* back1;
	cocos2d::Sprite* back2;
	cocos2d::Sprite* mySprite;
};

#endif // __HELLOWORLD_SCENE_H__
