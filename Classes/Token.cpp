#include "Token.h"
#include<cstdlib>

USING_NS_CC;

Token::Token(int _id, std::string _spritePath)
{
	button = cocos2d::ui::Button::create(_spritePath);
	id = _id;
	currentPos = 0;
}

cocos2d::ui::Button* Token::getButton()
{
	return button;
}

int Token::getCurrentPos()
{
	return currentPos;
}

void Token::setCurrentPos(int _pos)
{
	currentPos = _pos;
}
