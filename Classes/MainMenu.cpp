#include "MainMenu.h"
#include "Dice.h"
#include "Player.h"

USING_NS_CC;

#define audioInstance cocos2d::experimental::AudioEngine

cocos2d::ui::Button* MainMenu::playerButton = nullptr;

bool MainMenu::hasMadePlayerPlay = false;

cocos2d::Sprite* MainMenu::diceSprite = nullptr;

Player* MainMenu::bluePlayer = nullptr;
Player* MainMenu::redPlayer = nullptr;
Player* MainMenu::greenPlayer = nullptr;
Player* MainMenu::yellowPlayer = nullptr;
Player* MainMenu::currentlyPlaying = nullptr;


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
    diceSprite = Sprite::create("dice/dice_roll.png", Rect(0,370,100,70));
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
        this->addChild(diceSprite, 1, "dice");
        this->addChild(maskSprite, 2, "mask");
        this->addChild(textBG, 2, "titleTextBG");

    }

    //Players
    bluePlayer = new Player("ui/Tokens/Blue_Token.png", "BLUE");
    redPlayer = new Player("ui/Tokens/Red_Token2.png", "RED");
    greenPlayer = new Player("ui/Tokens/Green_Token.png", "GREEN");
    yellowPlayer = new Player("ui/Tokens/Yellow_Token1.png", "YELLOW");
    if (bluePlayer == nullptr || redPlayer == nullptr || greenPlayer == nullptr || yellowPlayer == nullptr)
    {
        log("bluePlayer is NULL");
    }

    //blue player's tokens
    auto bpFirstToken = bluePlayer->retrieveToken(1);
    auto bpSecondToken = bluePlayer->retrieveToken(2);
    auto bpThirdToken = bluePlayer->retrieveToken(3);
    auto bpFourthToken = bluePlayer->retrieveToken(4);
    if (bpFirstToken == nullptr || bpSecondToken == nullptr || bpThirdToken == nullptr || bpFourthToken == nullptr)
    {
        log("Blue Player's Token is NULL");
    }
    else
    {
        bpFirstToken->getButton()->ignoreContentAdaptWithSize(false);
        bpFirstToken->getButton()->setContentSize(Size(45, 45));
        bpFirstToken->getButton()->setPosition(Vec2(321, 258));
        //bpFirstToken->setTitleText("Button1");
        bpFirstToken->getButton()->setTouchEnabled(false);
        this->addChild(bpFirstToken->getButton(), 7, "bluePlayerFirstToken");

        bpSecondToken->getButton()->ignoreContentAdaptWithSize(false);
        bpSecondToken->getButton()->setContentSize(Size(45, 45));
        bpSecondToken->getButton()->setPosition(Vec2(321, 181));
        bpSecondToken->getButton()->setTouchEnabled(false);
        this->addChild(bpSecondToken->getButton(), 8, "bluePlayerSecondToken");

        bpThirdToken->getButton()->ignoreContentAdaptWithSize(false);
        bpThirdToken->getButton()->setContentSize(Size(45, 45));
        bpThirdToken->getButton()->setPosition(Vec2(405, 258));
        bpThirdToken->getButton()->setTouchEnabled(false);
        this->addChild(bpThirdToken->getButton(), 9, "bluePlayerThirdToken");

        bpFourthToken->getButton()->ignoreContentAdaptWithSize(false);
        bpFourthToken->getButton()->setContentSize(Size(45, 45));
        bpFourthToken->getButton()->setPosition(Vec2(405, 181));
        bpFourthToken->getButton()->setTouchEnabled(false);
        this->addChild(bpFourthToken->getButton(), 10, "bluePlayerFourthToken");
    }

    //red player's tokens
    auto rpFirstToken = redPlayer->retrieveToken(1);
    auto rpSecondToken = redPlayer->retrieveToken(2);
    auto rpThirdToken = redPlayer->retrieveToken(3);
    auto rpFourthToken = redPlayer->retrieveToken(4);
    if (rpFirstToken == nullptr || rpSecondToken == nullptr || rpThirdToken == nullptr || rpFourthToken == nullptr)
    {
        log("Red Player's Token is NULL");
    }
    else
    {
        rpFirstToken->getButton()->ignoreContentAdaptWithSize(false);
        rpFirstToken->getButton()->setContentSize(Size(45, 45));
        rpFirstToken->getButton()->setPosition(Vec2(322, 683));
        //bpFirstToken->setTitleText("Button1");
        rpFirstToken->getButton()->setTouchEnabled(false);
        this->addChild(rpFirstToken->getButton(), 11, "redPlayerFirstToken");

        rpSecondToken->getButton()->ignoreContentAdaptWithSize(false);
        rpSecondToken->getButton()->setContentSize(Size(45, 45));
        rpSecondToken->getButton()->setPosition(Vec2(322, 606));
        rpSecondToken->getButton()->setTouchEnabled(false);
        this->addChild(rpSecondToken->getButton(), 12, "redPlayerSecondToken");

        rpThirdToken->getButton()->ignoreContentAdaptWithSize(false);
        rpThirdToken->getButton()->setContentSize(Size(45, 45));
        rpThirdToken->getButton()->setPosition(Vec2(406, 683));
        rpThirdToken->getButton()->setTouchEnabled(false);
        this->addChild(rpThirdToken->getButton(), 13, "redPlayerThirdToken");

        rpFourthToken->getButton()->ignoreContentAdaptWithSize(false);
        rpFourthToken->getButton()->setContentSize(Size(45, 45));
        rpFourthToken->getButton()->setPosition(Vec2(406, 606));
        rpFourthToken->getButton()->setTouchEnabled(false);
        this->addChild(rpFourthToken->getButton(), 14, "redPlayerFourthToken");
    }

    //green player's tokens
    auto gpFirstToken = greenPlayer->retrieveToken(1);
    auto gpSecondToken = greenPlayer->retrieveToken(2);
    auto gpThirdToken = greenPlayer->retrieveToken(3);
    auto gpFourthToken = greenPlayer->retrieveToken(4);
    if (gpFirstToken == nullptr || gpSecondToken == nullptr || gpThirdToken == nullptr || gpFourthToken == nullptr)
    {
        log("Green Player's Token is NULL");
    }
    else
    {
        gpFirstToken->getButton()->ignoreContentAdaptWithSize(false);
        gpFirstToken->getButton()->setContentSize(Size(45, 45));
        gpFirstToken->getButton()->setPosition(Vec2(747, 683));
        //bpFirstToken->setTitleText("Button1");
        gpFirstToken->getButton()->setTouchEnabled(false);
        this->addChild(gpFirstToken->getButton(), 15, "greenPlayerFirstToken");

        gpSecondToken->getButton()->ignoreContentAdaptWithSize(false);
        gpSecondToken->getButton()->setContentSize(Size(45, 45));
        gpSecondToken->getButton()->setPosition(Vec2(747, 606));
        gpSecondToken->getButton()->setTouchEnabled(false);
        this->addChild(gpSecondToken->getButton(), 16, "greenPlayerSecondToken");

        gpThirdToken->getButton()->ignoreContentAdaptWithSize(false);
        gpThirdToken->getButton()->setContentSize(Size(45, 45));
        gpThirdToken->getButton()->setPosition(Vec2(831, 683));
        gpThirdToken->getButton()->setTouchEnabled(false);
        this->addChild(gpThirdToken->getButton(), 17, "greenPlayerThirdToken");

        gpFourthToken->getButton()->ignoreContentAdaptWithSize(false);
        gpFourthToken->getButton()->setContentSize(Size(45, 45));
        gpFourthToken->getButton()->setPosition(Vec2(831, 606));
        gpFourthToken->getButton()->setTouchEnabled(false);
        this->addChild(gpFourthToken->getButton(), 18, "greenPlayerFourthToken");
    }

    //yellow player's tokens
    auto ypFirstToken = yellowPlayer->retrieveToken(1);
    auto ypSecondToken = yellowPlayer->retrieveToken(2);
    auto ypThirdToken = yellowPlayer->retrieveToken(3);
    auto ypFourthToken = yellowPlayer->retrieveToken(4);
    if (ypFirstToken == nullptr || ypSecondToken == nullptr || ypThirdToken == nullptr || ypFourthToken == nullptr)
    {
        log("Yellow Player's Token is NULL");
    }
    else
    {
        ypFirstToken->getButton()->ignoreContentAdaptWithSize(false);
        ypFirstToken->getButton()->setContentSize(Size(45, 45));
        ypFirstToken->getButton()->setPosition(Vec2(747, 258));
        //bpFirstToken->setTitleText("Button1");
        ypFirstToken->getButton()->setTouchEnabled(false);
        this->addChild(ypFirstToken->getButton(), 19, "yellowPlayerFirstToken");

        ypSecondToken->getButton()->ignoreContentAdaptWithSize(false);
        ypSecondToken->getButton()->setContentSize(Size(45, 45));
        ypSecondToken->getButton()->setPosition(Vec2(747, 181));
        ypSecondToken->getButton()->setTouchEnabled(false);
        this->addChild(ypSecondToken->getButton(), 20, "yellowPlayerSecondToken");

        ypThirdToken->getButton()->ignoreContentAdaptWithSize(false);
        ypThirdToken->getButton()->setContentSize(Size(45, 45));
        ypThirdToken->getButton()->setPosition(Vec2(831, 258));
        ypThirdToken->getButton()->setTouchEnabled(false);
        this->addChild(ypThirdToken->getButton(), 21, "yellowPlayerThirdToken");

        ypFourthToken->getButton()->ignoreContentAdaptWithSize(false);
        ypFourthToken->getButton()->setContentSize(Size(45, 45));
        ypFourthToken->getButton()->setPosition(Vec2(831, 181));
        ypFourthToken->getButton()->setTouchEnabled(false);
        this->addChild(ypFourthToken->getButton(), 22, "yellowPlayerFourthToken");
    }

    currentlyPlaying = bluePlayer;
    hasMadePlayerPlay = false;

    //To get nouse positions
    //Only for Debug
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = [this](cocos2d::EventMouse* event) {
        // Cast Event to EventMouse for position details like above
        onMouseMove(event, bluePlayer);
    };
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);

    //Play Button for dice throwing
    playerButton = cocos2d::ui::Button::create("ui/diceBtn.png");
    playerButton->ignoreContentAdaptWithSize(false);
    playerButton->setContentSize(Size(60, 60));
    playerButton->setPosition(Vec2(140, 225));
    playerButton->setTouchEnabled(false);
    playerButton->setVisible(false);
    this->addChild(playerButton, 23, "playerButton");

    //BGM
    playBGM();

    //update schedule
    this->scheduleUpdate();
       
    return true;
}

//To get mouse positions
//Only for Debug
void MainMenu::onMouseMove(cocos2d::EventMouse* event, Player* player)
{

    //log("X: %f, Y: %f",event->getCursorX(), event->getCursorY());
    //player->getButton(1)->setPosition(Vec2(event->getCursorX(), event->getCursorY()));
    //player->move(player->getButton(1), 25);
}

void MainMenu::update(float dt)
{
    if (!bluePlayer->isWinner() && !redPlayer->isWinner() && !greenPlayer->isWinner() && !yellowPlayer->isWinner())
    {
        if (bluePlayer == currentlyPlaying && !hasMadePlayerPlay)
        {
            log("Blue Player's playing");
            makePlayerPlay(bluePlayer);
        }
    }
}

void MainMenu::hidePlayerButton()
{
    playerButton->setVisible(false);
    playerButton->setTouchEnabled(false);
}

void MainMenu::playRollDiceAnim()
{
    Dice::getInstance()->rollDice(diceSprite);

    //::::::::::::::::::::::::Delay:::::::::::::::::::::::::::::::::::::::::::::
    //float delay = 2.0f;
    //auto delayAction = DelayTime::create(delay);  // For 2 Seconds of Delay
    //auto funcCallback = CallFunc::create([]() {
    //    int rollVal = Dice::getInstance()->getLastRollVal();
    //    log("RollVal: %d", rollVal);
    //});
    //this->runAction(Sequence::create(delayAction, funcCallback, NULL));

    //bluePlayer->move(bluePlayer->retrieveToken(4), rollVal, this->getChildByName("bluePlayerFirstToken"));
}

void MainMenu::makePlayerPlay(Player* _player)
{
    playerButton->setTouchEnabled(true);
    playerButton->setVisible(true);
    playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, _player));
    adjustPlayerTokensOpactity(_player);
    hasMadePlayerPlay = true;
}

void MainMenu::passPlayerTurn()
{
    if (currentlyPlaying == bluePlayer)
    {
        log("passed to redPlayer");
        playerButton->setPosition(Vec2(playerButton->getPosition().x, 644));
        playerButton->setVisible(true);
        playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, redPlayer));
        adjustPlayerTokensOpactity(redPlayer);
        currentlyPlaying = redPlayer;
        return;
    }
    if (currentlyPlaying == redPlayer)
    {
        log("passed to greenPlayer");
        playerButton->setPosition(Vec2(1015, playerButton->getPosition().y));
        playerButton->setVisible(true);
        playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, greenPlayer));
        adjustPlayerTokensOpactity(greenPlayer);
        currentlyPlaying = greenPlayer;
        return;
    }
    if (currentlyPlaying == greenPlayer)
    {
        log("passed to yellowPlayer");
        playerButton->setPosition(Vec2(playerButton->getPosition().x, 221));
        playerButton->setVisible(true);
        playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, yellowPlayer));
        adjustPlayerTokensOpactity(yellowPlayer);
        currentlyPlaying = yellowPlayer;
        return;
    }
    if (currentlyPlaying == yellowPlayer)
    {
        log("passed to bluePlayer");
        playerButton->setPosition(Vec2(140, playerButton->getPosition().y));
        playerButton->setVisible(true);
        playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, bluePlayer));
        adjustPlayerTokensOpactity(bluePlayer);
        currentlyPlaying = bluePlayer;
        return;
    }
}


void MainMenu::adjustPlayerTokensOpactity(Player* _player)
{
    /*auto actionBlink = Blink::create(1.0, 3);
    auto _seq = RepeatForever::create(Sequence::create(actionBlink, NULL, NULL));
    redPlayer->getButton(1)->runAction(_seq);

    redPlayer->getButton(1)->setOpacity(GLubyte(120));
    redPlayer->getButton(2)->setOpacity(GLubyte(120));
    redPlayer->getButton(3)->setOpacity(GLubyte(120));
    redPlayer->getButton(4)->setOpacity(GLubyte(120));

    greenPlayer->getButton(1)->setOpacity(GLubyte(120));
    greenPlayer->getButton(2)->setOpacity(GLubyte(120));
    greenPlayer->getButton(3)->setOpacity(GLubyte(120));
    greenPlayer->getButton(4)->setOpacity(GLubyte(120));

    yellowPlayer->getButton(1)->setOpacity(GLubyte(120));
    yellowPlayer->getButton(2)->setOpacity(GLubyte(120));
    yellowPlayer->getButton(3)->setOpacity(GLubyte(120));
    yellowPlayer->getButton(4)->setOpacity(GLubyte(120));

    bluePlayer->getButton(1)->setOpacity(GLubyte(120));
    bluePlayer->getButton(2)->setOpacity(GLubyte(120));
    bluePlayer->getButton(3)->setOpacity(GLubyte(120));
    bluePlayer->getButton(4)->setOpacity(GLubyte(120));

    _player->getButton(1)->setOpacity(GLubyte(255));
    _player->getButton(2)->setOpacity(GLubyte(255));
    _player->getButton(3)->setOpacity(GLubyte(255));
    _player->getButton(4)->setOpacity(GLubyte(255));*/
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

