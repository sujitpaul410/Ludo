#ifndef __MainMenu_SCENE_H__
#define __MainMenu_SCENE_H__

#include "cocos2d.h"

class MainMenu : public cocos2d::Scene
{
private:
    cocos2d::Vec2 deviceResolution;

public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    //selector callbacks
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuPlayCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
};

#endif
