#include "Dice.h"
#include<cstdlib>

USING_NS_CC;

Dice* Dice::instance = 0;

//Animates dice sprite
void Dice::rollDice(Sprite* _sprite)
{
	srand((unsigned)time(NULL));
	int _random = 1 + rand() % 6;
	this->lastRollVal = _random;

	Vector<SpriteFrame*> _animFrames(6);
	const char _str[100] = "dice/dice_roll.png";

	//creating 6 six animation frames for the 6 sides of dice
	for (int i = 1; i < 7; i++)
	{
		auto _frame= SpriteFrame::create(_str, Rect(0, 0, 100, 70));
		switch (i)
		{
		case 1:
			_frame = SpriteFrame::create(_str, Rect(0, 0, 100, 70));
			_animFrames.pushBack(_frame);
			break;
		case 2:
			_frame = SpriteFrame::create(_str, Rect(0, 70, 100, 70));
			_animFrames.pushBack(_frame);
			break;
		case 3:
			_frame = SpriteFrame::create(_str, Rect(0, 160, 100, 70));
			_animFrames.pushBack(_frame);
			break;
		case 4:
			_frame = SpriteFrame::create(_str, Rect(0, 230, 100, 70));
			_animFrames.pushBack(_frame);
			break;
		case 5:
			_frame = SpriteFrame::create(_str, Rect(0, 300, 100, 70));
			_animFrames.pushBack(_frame);
			break;
		case 6:
			_frame = SpriteFrame::create(_str, Rect(0, 370, 100, 70));
			_animFrames.pushBack(_frame);
			break;
		};
	}
	auto _animation = Animation::createWithSpriteFrames(_animFrames, 0.15f);
	auto _animate = Animate::create(_animation);

	//_sprite->runAction(_animate);

	//using callback to set the dice face as per the random number
	auto callbackAction = CallFunc::create([_sprite, _random, this]() {

			switch (_random)
			{
			case 1:
				_sprite->setTextureRect(Rect(0, 0, 100, 70));
				break;
			case 2:
				_sprite->setTextureRect(Rect(0, 70, 100, 70));
				break;
			case 3:
				_sprite->setTextureRect(Rect(0, 160, 100, 70));
				break;
			case 4:
				_sprite->setTextureRect(Rect(0, 230, 100, 70));
				break;
			case 5:
				_sprite->setTextureRect(Rect(0, 300, 100, 70));
				break;
			case 6:
				_sprite->setTextureRect(Rect(0, 370, 100, 70));
				break;
			};

		});
	_sprite->runAction(Sequence::create(_animate, callbackAction, nullptr));
}

int Dice::getLastRollVal()
{
	return lastRollVal;
}

//Only one instace is enough
Dice* Dice::getInstance()
{
	if (!instance)
	{
		instance = new Dice(0);
	}
	return instance;
}

Dice::Dice(int _lastRollVal)
{
	lastRollVal = _lastRollVal;
}
