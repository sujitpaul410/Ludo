#include "MainMenu.h"
#include "Dice.h"
#include "Player.h"

USING_NS_CC;

#define audioInstance cocos2d::experimental::AudioEngine

cocos2d::ui::Button* MainMenu::playerButton = nullptr;

bool MainMenu::hasMadePlayerPlay = false;

bool MainMenu::isPlaying = false;

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

    Director::getInstance()->getOpenGLView()->setFrameSize(deviceResolution.x/1.25, deviceResolution.y/1.25);
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
        this->addChild(menu, 38);

        auto play = Menu::create(playItem, NULL);
        play->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 22));
        this->addChild(play, 39, "play");

        auto volume = Menu::create(volumeItem, NULL);
        volume->setPosition(Vec2(visibleSize.width / 2 - 200, visibleSize.height / 22));
        this->addChild(volume, 40, "volume");
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
        this->addChild(label, 34);
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
        maskSprite->setContentSize(Size(1024, 736));
        maskSprite->setOpacity(200);
        textBG->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + visibleSize.height - label->getContentSize().height-2));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0, "background");
        this->addChild(diceSprite, 35, "dice");
        this->addChild(maskSprite, 37, "mask");
        this->addChild(textBG, 33, "titleTextBG");

    }

    //Players
    bluePlayer = new Player("ui/Tokens/Blue_Token.png", "BLUE");
    redPlayer = new Player("ui/Tokens/Red_Token2.png", "RED");
    greenPlayer = new Player("ui/Tokens/Green_Token.png", "GREEN");
    yellowPlayer = new Player("ui/Tokens/Yellow_Token1.png", "YELLOW");
    if (bluePlayer == nullptr || redPlayer == nullptr || greenPlayer == nullptr || yellowPlayer == nullptr)
    {
        log("Player is NULL");
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
        setupAndAddToken(bpFirstToken, Vec2(321, 258), 7, "bluePlayerFirstToken");
        setupAndAddToken(bpSecondToken, Vec2(321, 181), 8, "bluePlayerSecondToken");
        setupAndAddToken(bpThirdToken, Vec2(405, 258), 9, "bluePlayerThirdToken");
        setupAndAddToken(bpFourthToken, Vec2(405, 181), 10, "bluePlayerFourthToken");
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
        setupAndAddToken(rpFirstToken, Vec2(322, 683), 11, "redPlayerFirstToken");
        setupAndAddToken(rpSecondToken, Vec2(322, 606), 12, "redPlayerSecondToken");
        setupAndAddToken(rpThirdToken, Vec2(406, 683), 13, "redPlayerThirdToken");
        setupAndAddToken(rpFourthToken, Vec2(406, 606), 14, "redPlayerFourthToken");
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
        setupAndAddToken(gpFirstToken, Vec2(747, 683), 15, "greenPlayerFirstToken");
        setupAndAddToken(gpSecondToken, Vec2(747, 606), 16, "greenPlayerSecondToken");
        setupAndAddToken(gpThirdToken, Vec2(831, 683), 17, "greenPlayerThirdToken");
        setupAndAddToken(gpFourthToken, Vec2(831, 606), 18, "greenPlayerFourthToken");
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
        setupAndAddToken(ypFirstToken, Vec2(747, 258), 19, "yellowPlayerFirstToken");
        setupAndAddToken(ypSecondToken, Vec2(747, 181), 20, "yellowPlayerSecondToken");
        setupAndAddToken(ypThirdToken, Vec2(831, 258), 21, "yellowPlayerThirdToken");
        setupAndAddToken(ypFourthToken, Vec2(831, 181), 22, "yellowPlayerFourthToken");
    }

    currentlyPlaying = bluePlayer;
    hasMadePlayerPlay = false;

    //To get nouse positions
    //Only for Debug
    /*auto listener = EventListenerMouse::create();
    listener->onMouseMove = [this](cocos2d::EventMouse* event) {
        // Cast Event to EventMouse for position details like above
        onMouseMove(event, bluePlayer);
    };
    _eventDispatcher->addEventListenerWithFixedPriority(listener, 1);*/

    //Play Button for dice throwing
    playerButton = cocos2d::ui::Button::create("ui/diceBtn.png");
    playerButton->ignoreContentAdaptWithSize(false);
    playerButton->setContentSize(Size(60, 60));
    playerButton->setPosition(Vec2(140, 225));
    playerButton->setTouchEnabled(false);
    playerButton->setVisible(false);
    this->addChild(playerButton, 23, "playerButton");

    //label_Winner
    status_label_Blue = Label::createWithTTF("Blue's Status", "fonts/Marker Felt.ttf", 35);
    if (status_label_Blue == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        status_label_Blue->setColor(Color3B::BLACK);
        status_label_Blue->setPosition(Vec2(356, 337));
        status_label_Blue->setVisible(false);

        // add the label as a child to this layer
        this->addChild(status_label_Blue, 34);
    }

    status_label_Red = Label::createWithTTF("Red's Status", "fonts/Marker Felt.ttf", 35);
    if (status_label_Red == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        status_label_Red->setColor(Color3B::BLACK);
        status_label_Red->setPosition(Vec2(356, 761));

        // add the label as a child to this layer
        this->addChild(status_label_Red, 34);
        status_label_Red->setVisible(false);
    }

    status_label_Green = Label::createWithTTF("Green's Status", "fonts/Marker Felt.ttf", 35);
    if (status_label_Green == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        status_label_Green->setColor(Color3B::BLACK);
        status_label_Green->setPosition(Vec2(788, 761));
        status_label_Green->setVisible(false);

        // add the label as a child to this layer
        this->addChild(status_label_Green, 34);
    }

    status_label_Yellow = Label::createWithTTF("Yellow's Status", "fonts/Marker Felt.ttf", 35);
    if (status_label_Yellow == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        status_label_Yellow->setColor(Color3B::BLACK);
        status_label_Yellow->setPosition(Vec2(788, 337));
        status_label_Yellow->setVisible(false);

        // add the label as a child to this layer
        this->addChild(status_label_Yellow, 34);
    }

    numPlayersFinishedGame = 0;

    //version
    auto credits = Label::createWithTTF("By,\nSujit Paul", "fonts/Marker Felt.ttf", 20);
    if (credits == nullptr)
    {
        problemLoading("'fonts/Marker Felt.ttf'");
    }
    else
    {
        credits->setPosition(Vec2(1094, 37));
        credits->setVisible(true);

        // add the label as a child to this layer
        this->addChild(credits, 37);
    }

    //BGM
    playBGM();

    //update schedule
    this->scheduleUpdate();
       
    return true;
}

//To get mouse positions
//Only for Debug
/*void MainMenu::onMouseMove(cocos2d::EventMouse* event, Player* player)
{

    log("X: %f, Y: %f",event->getCursorX(), event->getCursorY());
    player->getButton(1)->setPosition(Vec2(event->getCursorX(), event->getCursorY()));
    //player->getButton(1)->setPosition(Vec2(event->getCursorX(), event->getCursorY()));
    //player->move(player->getButton(1), 25);
}*/

void MainMenu::setupAndAddToken(Token* _token, Vec2 _pos, int _zOrder, std::string _name)
{
    _token->getButton()->ignoreContentAdaptWithSize(false);
    _token->getButton()->setContentSize(Size(45, 45));
    _token->getButton()->setPosition(_pos);
    //_token->setTitleText("Button1");
    _token->getButton()->setTouchEnabled(false);
    this->addChild(_token->getButton(), _zOrder, _name);
}

void MainMenu::update(float dt)
{
    if (!bluePlayer->hasCompletedGame() && !redPlayer->hasCompletedGame() && !greenPlayer->hasCompletedGame() && !yellowPlayer->hasCompletedGame())
    {
        if (bluePlayer == currentlyPlaying && !hasMadePlayerPlay)
        {
            log("Blue Player's playing");
            makePlayerPlay(bluePlayer);
        }
    }
    else
    {
        if (numPlayersFinishedGame == 0)
        {

            if (bluePlayer->hasCompletedGame())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Blue, "1st Place");
                numPlayersFinishedGame = 1;
            }
            else if (redPlayer->hasCompletedGame())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Red, "1st Place");
                numPlayersFinishedGame = 1;
            }
            else if (greenPlayer->hasCompletedGame())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Green, "1st Place");
                numPlayersFinishedGame = 1;
            }
            else if (yellowPlayer->hasCompletedGame())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Yellow, "1st Place");
                numPlayersFinishedGame = 1;
            }

            
        }
        else if (numPlayersFinishedGame == 1)
        {

            if (bluePlayer->hasCompletedGame() && !status_label_Blue->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Blue, "2nd Place");
                numPlayersFinishedGame = 2;
            }
            else if (redPlayer->hasCompletedGame() && !status_label_Red->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Red, "2nd Place");
                numPlayersFinishedGame = 2;
            }
            else if (greenPlayer->hasCompletedGame() && !status_label_Green->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Green, "2nd Place");
                numPlayersFinishedGame = 2;
            }
            else if (yellowPlayer->hasCompletedGame() && !status_label_Yellow->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Yellow, "2nd Place");
                numPlayersFinishedGame = 2;
            }

        }
        else if (numPlayersFinishedGame == 2)
        {

            if (bluePlayer->hasCompletedGame() && !status_label_Blue->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Blue, "3rd Place");
                numPlayersFinishedGame = 3;
            }
            else if (redPlayer->hasCompletedGame() && !status_label_Red->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Red, "3rd Place");
                numPlayersFinishedGame = 3;
            }
            else if (greenPlayer->hasCompletedGame() && !status_label_Green->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Green, "3rd Place");
                numPlayersFinishedGame = 3;
            }
            else if (yellowPlayer->hasCompletedGame() && !status_label_Yellow->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Yellow, "3rd Place");
                numPlayersFinishedGame = 3;
            }

        }
        else
        {

            if (!bluePlayer->hasCompletedGame() && !status_label_Blue->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Blue, "4th Place");
                numPlayersFinishedGame = 4;
            }
            else if (!redPlayer->hasCompletedGame() && !status_label_Red->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Red, "4th Place");
                numPlayersFinishedGame = 4;
            }
            else if (!greenPlayer->hasCompletedGame() && !status_label_Green->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Green, "4th Place");
                numPlayersFinishedGame = 4;
            }
            else if (!yellowPlayer->hasCompletedGame() && !status_label_Yellow->isVisible())
            {
                DeclareStatusOfPlayerAfterCompletion(status_label_Yellow, "4th Place");
                numPlayersFinishedGame = 4;
            }

            hidePlayerButton();

        }
    }
}

void MainMenu::DeclareStatusOfPlayerAfterCompletion(cocos2d::Label* _label, const std::string _string)
{
    _label->setString(_string);
    _label->setVisible(true);
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
    if (isPlaying)
        playerButton->setTouchEnabled(true);
    playerButton->setVisible(true);
    playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, _player));
    maintainZorderOfCurrentPlayer(_player);
    hasMadePlayerPlay = true;

    auto actionBlink = Blink::create(1.0, 1);
    auto _seq = RepeatForever::create(Sequence::create(FadeOut::create(0.2f), FadeIn::create(0.2f), NULL));
    playerButton->runAction(_seq->clone());
}

void MainMenu::passPlayerTurn()
{
    if (currentlyPlaying == bluePlayer)
    {
        passTurnToRedPlayer();
        return;
    }
    if (currentlyPlaying == redPlayer)
    {
        passTurnToGreenPlayer();
        return;
    }
    if (currentlyPlaying == greenPlayer)
    {
        passTurnToYellowPlayer();
        return;
    }
    if (currentlyPlaying == yellowPlayer)
    {
        passTurnToBluePlayer();
        return;
    }
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
        playerButton->setTouchEnabled(true);
    }
    else
    {
        playItem->setNormalSpriteFrame(SpriteFrame::create("ui/PLAY.png", Rect(0, 0, 63, 66)));
        this->getChildByName("mask")->setVisible(true);
        isPlaying = false;
        playerButton->setTouchEnabled(false);
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
    bgmID = audioInstance::play2d("sfx/bgm.mp3", true, 0.1f);
}

void MainMenu::stopBGM()
{
    audioInstance::stop(bgmID);
}


Player* MainMenu::getBluePlayer()
{
    return bluePlayer;
}
Player* MainMenu::getRedPlayer()
{
    return redPlayer;
}
Player* MainMenu::getGreenPlayer()
{
    return greenPlayer;
}
Player* MainMenu::getYellowPlayer()
{
    return yellowPlayer;
}

Vec2 MainMenu::getBluePlayerTokenPos(int _tokenID)
{
    if (_tokenID == 1)
    {
        return Vec2(321, 258);
    }
    else if (_tokenID == 2)
    {
        return Vec2(321, 181);
    }
    else if (_tokenID == 3)
    {
        return Vec2(405, 258);
    }
    else if (_tokenID == 4)
    {
        return Vec2(405, 181);
    }
}
Vec2 MainMenu::getRedPlayerTokenPos(int _tokenID)
{
    if (_tokenID == 1)
    {
        return Vec2(322, 683);
    }
    else if (_tokenID == 2)
    {
        return Vec2(322, 606);
    }
    else if (_tokenID == 3)
    {
        return Vec2(406, 683);
    }
    else if (_tokenID == 4)
    {
        return Vec2(406, 606);
    }
}
Vec2 MainMenu::getGreenPlayerTokenPos(int _tokenID)
{
    if (_tokenID == 1)
    {
        return Vec2(747, 683);
    }
    else if (_tokenID == 2)
    {
        return Vec2(747, 606);
    }
    else if (_tokenID == 3)
    {
        return Vec2(831, 683);
    }
    else if (_tokenID == 4)
    {
        return Vec2(831, 606);
    }
}
Vec2 MainMenu::getYellowPlayerTokenPos(int _tokenID)
{
    if (_tokenID == 1)
    {
        return Vec2(747, 258);
    }
    else if (_tokenID == 2)
    {
        return Vec2(747, 181);
    }
    else if (_tokenID == 3)
    {
        return Vec2(831, 258);
    }
    else if (_tokenID == 4)
    {
        return Vec2(831, 181);
    }
}

void MainMenu::maintainZorderOfCurrentPlayer(Player* _player)
{
    auto _scene = Director::getInstance()->getRunningScene();

    auto _bpFirstToken = _scene->getChildByName("bluePlayerFirstToken");
    auto _bpsecondToken = _scene->getChildByName("bluePlayerSecondToken");
    auto _bpThirdToken = _scene->getChildByName("bluePlayerThirdToken");
    auto _bpFourthToken = _scene->getChildByName("bluePlayerFourthToken");

    auto _rpFirstToken = _scene->getChildByName("redPlayerFirstToken");
    auto _rpsecondToken = _scene->getChildByName("redPlayerSecondToken");
    auto _rpThirdToken = _scene->getChildByName("redPlayerThirdToken");
    auto _rpFourthToken = _scene->getChildByName("redPlayerFourthToken");

    auto _gpFirstToken = _scene->getChildByName("greenPlayerFirstToken");
    auto _gpsecondToken = _scene->getChildByName("greenPlayerSecondToken");
    auto _gpThirdToken = _scene->getChildByName("greenPlayerThirdToken");
    auto _gpFourthToken = _scene->getChildByName("greenPlayerFourthToken");

    auto _ypFirstToken = _scene->getChildByName("yellowPlayerFirstToken");
    auto _ypsecondToken = _scene->getChildByName("yellowPlayerSecondToken");
    auto _ypThirdToken = _scene->getChildByName("yellowPlayerThirdToken");
    auto _ypFourthToken = _scene->getChildByName("yellowPlayerFourthToken");


    _bpFirstToken->setLocalZOrder(15);
    _bpsecondToken->setLocalZOrder(16);
    _bpThirdToken->setLocalZOrder(17);
    _bpFourthToken->setLocalZOrder(18);

    _rpFirstToken->setLocalZOrder(15);
    _rpsecondToken->setLocalZOrder(16);
    _rpThirdToken->setLocalZOrder(17);
    _rpFourthToken->setLocalZOrder(18);

    _gpFirstToken->setLocalZOrder(15);
    _gpsecondToken->setLocalZOrder(16);
    _gpThirdToken->setLocalZOrder(17);
    _gpFourthToken->setLocalZOrder(18);

    _ypFirstToken->setLocalZOrder(15);
    _ypsecondToken->setLocalZOrder(16);
    _ypThirdToken->setLocalZOrder(17);
    _ypFourthToken->setLocalZOrder(18);

    if (_player->getCategory() == "BLUE")
    {
        _bpFirstToken->setLocalZOrder(19);
        _bpsecondToken->setLocalZOrder(20);
        _bpThirdToken->setLocalZOrder(21);
        _bpFourthToken->setLocalZOrder(22);
    }
    else if (_player->getCategory() == "RED")
    {
        _rpFirstToken->setLocalZOrder(19);
        _rpsecondToken->setLocalZOrder(20);
        _rpThirdToken->setLocalZOrder(21);
        _rpFourthToken->setLocalZOrder(22);
    }
    else if (_player->getCategory() == "GREEN")
    {
        _gpFirstToken->setLocalZOrder(19);
        _gpsecondToken->setLocalZOrder(20);
        _gpThirdToken->setLocalZOrder(21);
        _gpFourthToken->setLocalZOrder(22);
    }
    else if (_player->getCategory() == "YELLOW")
    {
        _ypFirstToken->setLocalZOrder(19);
        _ypsecondToken->setLocalZOrder(20);
        _ypThirdToken->setLocalZOrder(21);
        _ypFourthToken->setLocalZOrder(22);
    }
}

void MainMenu::playDiceMovementSfx()
{
    audioInstance::play2d("sfx/click.mp3", false, 1.0f);
}
void MainMenu::playDiceRollSfx()
{
    audioInstance::play2d("sfx/dice_roll.mp3", false, 1.0f);
}
void MainMenu::playTokenElinationSfx()
{
    audioInstance::play2d("sfx/token_elimination.mp3", false, 1.0f);
}
void MainMenu::playTokenHomeSfx()
{
    audioInstance::play2d("sfx/token_home.mp3", false, 1.0f);
}

void MainMenu::passTurnToBluePlayer()
{
    if (!bluePlayer->hasCompletedGame())
    {
        log("passed to bluePlayer");
        playerButton->setPosition(Vec2(140, playerButton->getPosition().y));
        playerButton->setVisible(true);
        if (isPlaying)
            playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, bluePlayer));
        maintainZorderOfCurrentPlayer(bluePlayer);
        currentlyPlaying = bluePlayer;
    }
    else
    {
        currentlyPlaying = bluePlayer;
        playerButton->setPosition(Vec2(140, playerButton->getPosition().y));
        passPlayerTurn();
    }
}
void MainMenu::passTurnToRedPlayer()
{
    if (!redPlayer->hasCompletedGame())
    {
        log("passed to redPlayer");
        playerButton->setPosition(Vec2(playerButton->getPosition().x, 644));
        playerButton->setVisible(true);
        if (isPlaying)
            playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, redPlayer));
        maintainZorderOfCurrentPlayer(redPlayer);
        currentlyPlaying = redPlayer;
    }
    else
    {
        currentlyPlaying = redPlayer;
        playerButton->setPosition(Vec2(playerButton->getPosition().x, 644));
        passPlayerTurn();
    }
}
void MainMenu::passTurnToGreenPlayer()
{
    if (!greenPlayer->hasCompletedGame())
    {
        log("passed to greenPlayer");
        playerButton->setPosition(Vec2(1015, playerButton->getPosition().y));
        playerButton->setVisible(true);
        if (isPlaying)
            playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, greenPlayer));
        maintainZorderOfCurrentPlayer(greenPlayer);
        currentlyPlaying = greenPlayer;
    }
    else
    {
        currentlyPlaying = greenPlayer;
        playerButton->setPosition(Vec2(1015, playerButton->getPosition().y));
        passPlayerTurn();
    }
}
void MainMenu::passTurnToYellowPlayer()
{
    if (!yellowPlayer->hasCompletedGame())
    {
        log("passed to yellowPlayer");
        playerButton->setPosition(Vec2(playerButton->getPosition().x, 221));
        playerButton->setVisible(true);
        if (isPlaying)
            playerButton->setTouchEnabled(true);
        playerButton->addTouchEventListener(CC_CALLBACK_0(Player::playTurn, yellowPlayer));
        maintainZorderOfCurrentPlayer(yellowPlayer);
        currentlyPlaying = yellowPlayer;
    }
    else
    {
        currentlyPlaying = yellowPlayer;
        playerButton->setPosition(Vec2(playerButton->getPosition().x, 221));
        passPlayerTurn();
    }
}