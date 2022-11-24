#include "MainMenu.h"

USING_NS_CC;

#define audioInstance cocos2d::experimental::AudioEngine

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
                                           "ui/exit.png",
                                           "ui/exit_pressed.png",
                                           CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    playItem = MenuItemImage::create(
        "ui/PLAY.png",
        "ui/PLAY_pressed.png",
        CC_CALLBACK_1(MainMenu::menuPlayCallback, this));


    volumeItem = MenuItemImage::create(
        "ui/volume.png",
        "ui/mute.png",
        CC_CALLBACK_1(MainMenu::menuVolumeCallback, this));


    if (closeItem == nullptr || playItem==nullptr || volumeItem==nullptr)
    {
        problemLoading("UI sprites");
    }
    else
    {
        // create menu, it's an autorelease object
        auto menu = Menu::create(closeItem, NULL);
        menu->setPosition(Vec2(visibleSize.width / 2 + 200, visibleSize.height / 22));
        this->addChild(menu, 6);

        auto play = Menu::create(playItem, NULL);
        play->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 22));
        this->addChild(play, 4, "play");

        auto volume = Menu::create(volumeItem, NULL);
        volume->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 22));
        this->addChild(volume, 5, "volume");
    }


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
        this->addChild(label, 3);
    }

    // Background
    auto sprite = Sprite::create("background/ludo.jpg");
    auto diceSprite = Sprite::create("dice/dice_roll.png", Rect(0,370,100,70));
    auto maskSprite = Sprite::create("background/mask.png");
    auto textBG = Sprite::create("ui/textHolder.png");

    if (sprite == nullptr || diceSprite == nullptr || maskSprite == nullptr || textBG == nullptr)
    {
        problemLoading("Background & other UI sprites");
    }
    else
    {
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
        diceSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        maskSprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
        maskSprite->setOpacity(200);
        textBG->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height-2));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0, "background");
        this->addChild(diceSprite, 1);
        this->addChild(maskSprite, 2, "mask");
        this->addChild(textBG, 2, "titleTextBG");

    }

    //BGM
    playBGM();
    
    return true;
}


void MainMenu::menuCloseCallback(Ref* pSender)
{
    clickID = audioInstance::play2d("sfx/click.mp3", false, 1.0f);

    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

void MainMenu::menuPlayCallback(Ref* pSender)
{
    clickID = audioInstance::play2d("sfx/click.mp3", false, 1.0f);
    if (!isPlaying)
    {
        playItem->setNormalSpriteFrame(SpriteFrame::create("ui/LOCK.png", Rect(0, 0, 63, 66)));
        this->getChildByName("mask")->setVisible(false);
        isPlaying = true;
    }
    else
    {
        playItem->setNormalSpriteFrame(SpriteFrame::create("ui/PLAY.png", Rect(0, 0, 63, 66)));
        this->getChildByName("mask")->setVisible(true);
        isPlaying = false;
    }
}
void MainMenu::menuVolumeCallback(Ref* pSender)
{
    clickID = audioInstance::play2d("sfx/click.mp3", false, 1.0f);

    if (!isMuted)
    {
        volumeItem->setNormalSpriteFrame(SpriteFrame::create("ui/mute.png", Rect(0, 0, 50, 50)));
        stopBGM();
        isMuted = true;
    }
    else
    {
        volumeItem->setNormalSpriteFrame(SpriteFrame::create("ui/volume.png", Rect(0, 0, 50, 50)));
        playBGM();
        isMuted = false;
    }
}

void MainMenu::playBGM()
{
    bgmID = audioInstance::play2d("sfx/bgm.mp3", true, 0.04f);
}

void MainMenu::stopBGM()
{
    audioInstance::stop(bgmID);
}

