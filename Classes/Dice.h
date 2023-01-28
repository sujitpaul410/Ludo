#ifndef __Dice_SCENE_H__
#define __Dice_SCENE_H__

#include "cocos2d.h"


class Dice
{
private:
	static Dice* instance;
	int lastRollVal;

	Dice(int _lastRollVal);

public:
	void rollDice(cocos2d::Sprite* _sprite);
	int getLastRollVal();

	static Dice* getInstance();
};

#endif

