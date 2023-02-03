#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"
#include "AudioEngine.h"
#include "Player.h"

class MainMenu : public cocos2d::Scene
{
private:
    cocos2d::Vec2 deviceResolution;
    cocos2d::MenuItemImage* volumeItem;
    cocos2d::MenuItemImage* playItem;
    static cocos2d::Sprite* diceSprite;
    
    bool isMuted;
    static bool isPlaying;
    int bgmID;
    int clickID;

    //selector callbacks
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    void menuVolumeCallback(cocos2d::Ref* pSender);

    void playBGM();
    void stopBGM();

    static Player* bluePlayer;
    static Player* redPlayer;
    static Player* greenPlayer;
    static Player* yellowPlayer;

    static Player* currentlyPlaying;

    static cocos2d::ui::Button* playerButton;

    static bool hasMadePlayerPlay;

    static void maintainZorderOfCurrentPlayer(Player* _player);

    cocos2d::Label* status_label_Blue;
    cocos2d::Label* status_label_Red;
    cocos2d::Label* status_label_Green;
    cocos2d::Label* status_label_Yellow;

    int numPlayersFinishedGame;

    void DeclareStatusOfPlayerAfterCompletion(cocos2d::Label* _label, const std::string _string);

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
        
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);

    //Only for Debug
    //Used for getting positions
    void onMouseMove(cocos2d::EventMouse* event, Player* player);

    virtual void update(float dt);

    static void hidePlayerButton();
    static void playRollDiceAnim();

    static void makePlayerPlay(Player* _player);

    static void passPlayerTurn();

    static Player* getBluePlayer();
    static Player* getRedPlayer();
    static Player* getGreenPlayer();
    static Player* getYellowPlayer();

    static Vec2 getBluePlayerTokenPos(int _tokenID);
    static Vec2 getRedPlayerTokenPos(int _tokenID);
    static Vec2 getGreenPlayerTokenPos(int _tokenID);
    static Vec2 getYellowPlayerTokenPos(int _tokenID);

    static void playDiceMovementSfx();
    static void playDiceRollSfx();
    static void playTokenElinationSfx();
    static void playTokenHomeSfx();
};

#endif
