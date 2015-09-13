#include "HelloWorldScene.h"
#include "JNIHelper.h"
#include "FBHelper_Android.h"
#include <iostream>
USING_NS_CC;
using namespace std;
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
    //CallMyJavaSideJNI(10);
    //CallMyJavaMethod("Mishal");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Vec2 screenSize = Director::getInstance()->getWinSize();
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

   /*     FBButton = MenuItemImage::create("FBLoginButton.jpeg","FBLoginButton.jpeg",CC_CALLBACK_1(HelloWorld::FBCallback, this));
        FBButton->setPosition(Vec2(origin.x + screenSize.x/2 , origin.y + screenSize.y * 0.8));
        FBButton->setTag(1);

        GoogleButton = MenuItemImage::create("GoogleSignButton.jpeg","GoogleSignButton.jpeg",CC_CALLBACK_1(HelloWorld::GPlusCallback, this));
        GoogleButton->setPosition(Vec2(origin.x + screenSize.x/2 , origin.y + screenSize.y * 0.5 ));
        GoogleButton->setTag(2);

        emailButton = MenuItemImage::create("loginWithEmail.jpeg","loginWithEmail.jpeg",CC_CALLBACK_1(HelloWorld::emailLoginCallback, this));
        emailButton->setPosition(Vec2(origin.x + screenSize.x/2 , origin.y + screenSize.y * 0.2 ));
        emailButton->setTag(2);

        auto upmenu8 = Menu::create(FBButton,GoogleButton,emailButton,NULL);
        upmenu8->setPosition(Vec2::ZERO);
        this->addChild(upmenu8,1);  */
        log("Social scene called!");

    
    return true;
}
void HelloWorld::emailLoginCallback(Ref* gsender)
{
    log("email login called");
}

void HelloWorld::FBCallback(Ref* sender)
{
    MenuItemImage *pSender = (MenuItemImage*)sender;
    CallMyFBMethod(100);
    log("Facebook button pressed!");
}
void HelloWorld::GPlusCallback(Ref* gsender)
{
    MenuItemImage *pSender = (MenuItemImage*)gsender;
    log("Google plus button pressed!");
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
