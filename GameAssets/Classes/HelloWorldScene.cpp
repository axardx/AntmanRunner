#include "HelloWorldScene.h"

USING_NS_CC;

int WIDTH = 1200, HEIGHT = 750;
int DISTANCE = 0;
int MYPOSITIONX = 180, MYPOSITIONY = 180;
int jumpflag = 0;
float JY = 400;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	


    // add a label shows "Hello World"
    // create and initialize a label
    
    /*auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);*/

    // add "HelloWorld" splash screen"
	back1 = Sprite::create("tesmap.jpg");
	back2 = Sprite::create("tesmap.jpg");

	back1->setAnchorPoint(ccp(0, 0));
	back2->setAnchorPoint(ccp(0, 0));

    // position the sprite on the center of the screen
	back1->setPosition(Vec2(0, 0));
	back2->setPosition(Vec2(visibleSize.width +0, 0));

    // add the sprite as a child to this layer
    this->addChild(back1, 0);
	this->addChild(back2, 0);

	mySprite = Sprite::create("i1.png");
	mySprite->setPosition(Vec2(MYPOSITIONX, MYPOSITIONY));
	this->addChild(mySprite, 0);

	this->scheduleUpdate();

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	if (jumpflag == 0)
	{
		jumpflag = 1;
		JY = 400;
	}
	else if (jumpflag == 1 || jumpflag == 2)
	{
		jumpflag = 3;
		JY = mySprite->getPositionY()+200;
	}
   /* Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif*/
}

void HelloWorld::update(float deltaA)
{
	// 定義背景要移動的速度
	deltaA = -4;
	

	if (back1->getPositionX() <= -WIDTH) {
		back1->setPositionX(WIDTH);
	}
	else {
		back1->setPositionX(back1->getPositionX() + deltaA);
	}
	if (back2->getPositionX() <= -WIDTH) {
		back2->setPositionX(WIDTH);
	}
	else {
		back2->setPositionX(back2->getPositionX() + deltaA);
	}
	if (jumpflag == 1)
	{
		if (mySprite->getPositionY() <= JY)
			mySprite->setPositionY(mySprite->getPositionY() - deltaA);
		else
			jumpflag = 2;
	}
	else if (jumpflag == 3)
	{
		if (mySprite->getPositionY() <= JY)
			mySprite->setPositionY(mySprite->getPositionY() - deltaA);
		else
			jumpflag = 2;
	}
	else if (jumpflag == 2)
	{
		if (mySprite->getPositionY() >= MYPOSITIONX)
			mySprite->setPositionY(mySprite->getPositionY() + deltaA);
		else 
			jumpflag = 0;
	}
}
