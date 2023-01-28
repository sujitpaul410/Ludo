#ifndef __Token_SCENE_H__
#define __Token_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Token
{
private:

	cocos2d::ui::Button* button;
	int id;
	int currentPos;

public:
	Token(int _id, std::string _spritePath);

	cocos2d::ui::Button* getButton();
	int getCurrentPos();
	void setCurrentPos(int _pos);
};

#endif

