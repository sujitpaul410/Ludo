#include "MainMenu.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    return MainMenu::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
}

bool MainMenu::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    //Resolution
    deviceResolution = Vec2(1152, 864);

    Director::getInstance()->getOpenGLView()->setFrameSize(deviceResolution.x, deviceResolution.y);
    Director::getInstance()->getOpenGLView()->setDesignResolutionSize(deviceResolution.x, deviceResolution.y, ResolutionPolicy::EXACT_FIT);
    auto const visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 const origin = Director::getInstance()->getVisibleOrigin();

    //MenuItems
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float const x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float const y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    auto playItem = MenuItemImage::create(
        "PLAY.png",
        "PLAY_pressed.png",
        CC_CALLBACK_1(MainMenu::menuPlayCallback, this));
    auto play = Menu::create(playItem, NULL);
    play->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height/22));
    this->addChild(play, 4, "play");

    //label
    auto label = Label::createWithTTF(":: Ludo ::", "fonts/Marker Felt.ttf", 35);
    if (label == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label->setPosition(Vec2(origin.x + visibleSize.width/2,
                                origin.y + visibleSize.height - label->getContentSize().height));

        // add the label as a child to this layer
        this->addChild(label, 1);
    }

    // Background
    auto sprite = Sprite::create("ludo.jpg");
    auto diceSprite = Sprite::create("dice_roll.png", Rect(0,370,100,70));
    auto maskSprite = Sprite::create("mask.png");
    if (sprite == nullptr)
    {
        problemLoading("'ludo.jpg'");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        diceSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        maskSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        maskSprite->setOpacity(200);

        // add the sprite as a child to this layer
        this->addChild(sprite, 0, "background");
        this->addChild(diceSprite, 1);
        this->addChild(maskSprite, 2, "mask");

    }
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}

void MainMenu::menuPlayCallback(Ref* pSender)
{
}
