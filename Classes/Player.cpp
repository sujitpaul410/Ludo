#include "Player.h"
#include "MainMenu.h"
#include<cstdlib>
#include "Dice.h"

USING_NS_CC;

Player::Player(std::string _spritePath, std::string _category)
{
	hasWon = false;
	category = _category;

	firstButton = new Token(1, _spritePath);
	secondButton = new Token(2, _spritePath);
	thirdButton = new Token(3, _spritePath);
	fourthButton = new Token(4, _spritePath);

	if (category == "BLUE")
	{
		firstButton->getButton()->addClickEventListener([this](Ref*)
			{
				//CCLOG("click works");
				int _lastRoll = Dice::getInstance()->getLastRollVal();
				this->move(firstButton, _lastRoll, Director::getInstance()->getRunningScene()->getChildByName("bluePlayerFirstToken"));
			});

		secondButton->getButton()->addClickEventListener([this](Ref*)
			{
				//CCLOG("click works");
				int _lastRoll = Dice::getInstance()->getLastRollVal();
				this->move(secondButton, _lastRoll, Director::getInstance()->getRunningScene()->getChildByName("bluePlayerSecondToken"));
			});

		thirdButton->getButton()->addClickEventListener([this](Ref*)
			{
				//CCLOG("click works");
				int _lastRoll = Dice::getInstance()->getLastRollVal();
				this->move(thirdButton, _lastRoll, Director::getInstance()->getRunningScene()->getChildByName("bluePlayerThirdToken"));
			});

		fourthButton->getButton()->addClickEventListener([this](Ref*)
			{
				//CCLOG("click works");
				int _lastRoll = Dice::getInstance()->getLastRollVal();
				this->move(fourthButton, _lastRoll, Director::getInstance()->getRunningScene()->getChildByName("bluePlayerFourthToken"));
			});
	}
}

cocos2d::ui::Button* Player::getButton(int _id)
{
	if (_id == 1)
	{
		return firstButton->getButton();
	}
	else if (_id == 2)
	{
		return secondButton->getButton();
	}
	else if (_id == 3)
	{
		return thirdButton->getButton();
	}
	else if (_id == 4)
	{
		return fourthButton->getButton();
	}

	else
		return nullptr;
}


void Player::move(Token* _token, int _steps, Node* _node)
{
	if (category == "BLUE")
	{

		//currentPos++;
		int _targetPos = _token->getCurrentPos() + _steps;
		//auto _node = Node::create();
		float delay = 0.1f;
		auto delayAction = DelayTime::create(delay);
		auto funcCallback = CallFunc::create([this, _token, _targetPos, _node]() {
			log("Delayed Func()");
			if (_token->getCurrentPos() < _targetPos)
			{
				_token->getButton()->setPosition(route[_token->getCurrentPos()]);
				auto _nextPos = _token->getCurrentPos();
				_nextPos++;
				_token->setCurrentPos(_nextPos);
			}
			else
			{
				_node->stopActionByTag(3333);
			}
		});
		auto _seq = RepeatForever::create(Sequence::create(delayAction, funcCallback, NULL));
		_seq->setTag(3333);
		_node->runAction(_seq);
	}
}


Token* Player::retrieveToken(int _id)
{
	if (_id == 1)
	{
		return firstButton;
	}
	else if (_id == 2)
	{
		return secondButton;
	}
	else if (_id == 3)
	{
		return thirdButton;
	}
	else if (_id == 4)
	{
		return fourthButton;
	}

	else
		return nullptr;
}


bool Player::isWinner()
{
	return hasWon;
}

void Player::playTurn()
{
	log("Playing Turn");
	MainMenu::hidePlayerButton();
	MainMenu::playRollDiceAnim();



	float const delay = 2.0f;
	auto delayAction = DelayTime::create(delay);
	auto funcCallback = CallFunc::create([this]() {
		log("Delayed Func()2");

		int _rollVal = Dice::getInstance()->getLastRollVal();
		log("RollVal: %d", _rollVal);

		int _numTokensInBase = 0;
		if (category == "BLUE")
		{
			if (firstButton->getButton()->getPosition().x == 321 && firstButton->getButton()->getPosition().y == 258)
			{
				_numTokensInBase++;
			}
			if (secondButton->getButton()->getPosition().x == 321 && secondButton->getButton()->getPosition().y == 181)
			{
				_numTokensInBase++;
			}
			if (thirdButton->getButton()->getPosition().x == 405 && thirdButton->getButton()->getPosition().y == 258)
			{
				_numTokensInBase++;
			}
			if (fourthButton->getButton()->getPosition().x == 405 && fourthButton->getButton()->getPosition().y == 181)
			{
				_numTokensInBase++;
			}
		}

		if (_numTokensInBase == 4 && _rollVal != 6)
		{
			log("pass to next player");
			MainMenu::passPlayerTurn();
		}
		else if (_numTokensInBase == 4 && _rollVal == 6)
		{
			log("Just for testing, passing to next player");
			MainMenu::passPlayerTurn();
		}
	});
	auto const _seq = Repeat::create(Sequence::create(delayAction, funcCallback, NULL), 1);
	Director::getInstance()->getRunningScene()->runAction(_seq);
}
