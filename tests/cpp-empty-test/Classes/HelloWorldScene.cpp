#include "HelloWorldScene.h"
#include "AppMacros.h"
#include "2d/CCParticleSystemQuad.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "cocostudio/CCComAudio.h"

USING_NS_CC;


Scene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

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
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        CC_CALLBACK_1(HelloWorld::menuCloseCallback,this));
    
    closeItem->setPosition(origin + Vec2(visibleSize) - Vec2(closeItem->getContentSize() / 2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = Label::createWithTTF("Hello World", "fonts/arial.ttf", TITLE_FONT_SIZE);
    
    // position the label on the center of the screen
    label->setPosition(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height);

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Vec2(visibleSize / 2) + origin);

    // add the sprite as a child to this layer
    //this->addChild(sprite);
    
    auto particle = ParticleSystemQuad::create("Particles/Flower.plist");
    auto sound = cocostudio::ComAudio::create();
    sound->setFile("background.wav");
    sound->play();
    this->addChild(sound);

    this->addChild(particle);
    particle->start();
    auto stopBtn = cocos2d::ui::Button::create();
    this->addChild(stopBtn);
    stopBtn->setTitleText("stop");
    stopBtn->setPosition(Vec2(50, 50));
    stopBtn->addClickEventListener([particle, sound, stopBtn](Ref* sender){
        if(particle->isActive())
        {
            stopBtn->setTitleText("start");
            particle->stop();
            sound->stop();
        }
        else
        {
            stopBtn->setTitleText("stop");
            particle->start();
            sound->start();
        }
        
    });
    
    auto resumeBtn = cocos2d::ui::Button::create();
    this->addChild(resumeBtn);
    resumeBtn->setTitleText("pause");
    resumeBtn->setPosition(Vec2(100, 50));
    resumeBtn->addClickEventListener([particle, resumeBtn](Ref* sender){
        if(particle->isActive())
        {
            resumeBtn->setTitleText("resume");
            particle->pause();
        }
        else
        {
            resumeBtn->setTitleText("pause");
            particle->resume();
        }
        
    });

    return true;
}

void HelloWorld::menuCloseCallback(Ref* sender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
