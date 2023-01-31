#include "Player.h"
#include "MainMenu.h"
#include<cstdlib>
#include "Dice.h"

USING_NS_CC;


Player::Player(std::string _spritePath, std::string _category)
{
	hasWon = false;
	category = _category;
	currentRollVal = 0;
	hasAdvantageTurn = false;

	firstButton = new Token(1, _spritePath);
	secondButton = new Token(2, _spritePath);
	thirdButton = new Token(3, _spritePath);
	fourthButton = new Token(4, _spritePath);

	if (category == "BLUE")
	{
		firstButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(firstButton, "bluePlayerFirstToken");
			});

		secondButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(secondButton, "bluePlayerSecondToken");
			});

		thirdButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(thirdButton, "bluePlayerThirdToken");
			});

		fourthButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(fourthButton, "bluePlayerFourthToken");
			});
	}
	if (category == "RED")
	{
		firstButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(firstButton, "redPlayerFirstToken");
			});

		secondButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(secondButton, "redPlayerSecondToken");
			});

		thirdButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(thirdButton, "redPlayerThirdToken");
			});

		fourthButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(fourthButton, "redPlayerFourthToken");
			});
	}
	if (category == "GREEN")
	{
		firstButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(firstButton, "greenPlayerFirstToken");
			});

		secondButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(secondButton, "greenPlayerSecondToken");
			});

		thirdButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(thirdButton, "greenPlayerThirdToken");
			});

		fourthButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(fourthButton, "greenPlayerFourthToken");
			});
	}
	if (category == "YELLOW")
	{
		firstButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(firstButton, "yellowPlayerFirstToken");
			});

		secondButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(secondButton, "yellowPlayerSecondToken");
			});

		thirdButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(thirdButton, "yellowPlayerThirdToken");
			});

		fourthButton->getButton()->addClickEventListener([this](Ref*)
			{
				setTokenClickEvent(fourthButton, "yellowPlayerFourthToken");
			});
	}
}

void Player::setTokenClickEvent(Token* _button, std::string _buttonName)
{
	//CCLOG("click works");
	setButtonActive(firstButton->getButton(), false);
	setButtonActive(secondButton->getButton(), false);
	setButtonActive(thirdButton->getButton(), false);
	setButtonActive(fourthButton->getButton(), false);
	if (currentRollVal == 0)
	{
		this->move(_button, 1, Director::getInstance()->getRunningScene()->getChildByName(_buttonName));
		MainMenu::makePlayerPlay(this);
	}
	else if (currentRollVal == 6)
	{
		this->move(_button, 6, Director::getInstance()->getRunningScene()->getChildByName(_buttonName));
		MainMenu::makePlayerPlay(this);
	}
	else
	{
		this->move(_button, currentRollVal, Director::getInstance()->getRunningScene()->getChildByName(_buttonName));

		float delay = 0.7f;
		auto delayAction = DelayTime::create(delay);
		auto funcCallback = CallFunc::create([this]() {
			if (this->hasAdvantageTurn)
			{
				hasAdvantageTurn = false;
				MainMenu::makePlayerPlay(this);
			}
			else
			{
				MainMenu::passPlayerTurn();
			}
		});
		auto _seq = Repeat::create(Sequence::create(delayAction, funcCallback, NULL), 1);
		Director::getInstance()->getRunningScene()->runAction(_seq);
	}
}

void Player::setButtonActive(cocos2d::ui::Button* _button, bool _state)
{
	_button->setTouchEnabled(_state);
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
	firstButton->getButton()->stopAllActions();
	//firstButton->getButton()->setVisible(true);
	firstButton->getButton()->setOpacity(GLubyte(255));
	secondButton->getButton()->stopAllActions();
	//secondButton->getButton()->setVisible(true);
	secondButton->getButton()->setOpacity(GLubyte(255));
	thirdButton->getButton()->stopAllActions();
	//thirdButton->getButton()->setVisible(true);
	thirdButton->getButton()->setOpacity(GLubyte(255));
	fourthButton->getButton()->stopAllActions();
	//fourthButton->getButton()->setVisible(true);
	fourthButton->getButton()->setOpacity(GLubyte(255));

	if (category == "BLUE")
	{
		if (_token == firstButton && (firstButton->getButton()->getPosition().x == 321 && firstButton->getButton()->getPosition().y == 258))
		{
			_steps = 1;
		}
		if (_token == secondButton && (secondButton->getButton()->getPosition().x == 321 && secondButton->getButton()->getPosition().y == 181))
		{
			_steps = 1;
		}
		if (_token == thirdButton && (thirdButton->getButton()->getPosition().x == 405 && thirdButton->getButton()->getPosition().y == 258))
		{
			_steps = 1;
		}
		if (_token == fourthButton && (fourthButton->getButton()->getPosition().x == 405 && fourthButton->getButton()->getPosition().y == 181))
		{
			_steps = 1;
		}
	}
	if (category == "RED")
	{
		if (_token == firstButton && (firstButton->getButton()->getPosition().x == 322 && firstButton->getButton()->getPosition().y == 683))
		{
			_steps = 1;
		}
		if (_token == secondButton && (secondButton->getButton()->getPosition().x == 322 && secondButton->getButton()->getPosition().y == 606))
		{
			_steps = 1;
		}
		if (_token == thirdButton && (thirdButton->getButton()->getPosition().x == 406 && thirdButton->getButton()->getPosition().y == 683))
		{
			_steps = 1;
		}
		if (_token == fourthButton && (fourthButton->getButton()->getPosition().x == 406 && fourthButton->getButton()->getPosition().y == 606))
		{
			_steps = 1;
		}
	}
	if (category == "GREEN")
	{
		if (_token == firstButton && (firstButton->getButton()->getPosition().x == 747 && firstButton->getButton()->getPosition().y == 683))
		{
			_steps = 1;
		}
		if (_token == secondButton && (secondButton->getButton()->getPosition().x == 747 && secondButton->getButton()->getPosition().y == 606))
		{
			_steps = 1;
		}
		if (_token == thirdButton && (thirdButton->getButton()->getPosition().x == 831 && thirdButton->getButton()->getPosition().y == 683))
		{
			_steps = 1;
		}
		if (_token == fourthButton && (fourthButton->getButton()->getPosition().x == 831 && fourthButton->getButton()->getPosition().y == 606))
		{
			_steps = 1;
		}
	}
	if (category == "YELLOW")
	{
		if (_token == firstButton && (firstButton->getButton()->getPosition().x == 747 && firstButton->getButton()->getPosition().y == 258))
		{
			_steps = 1;
		}
		if (_token == secondButton && (secondButton->getButton()->getPosition().x == 747 && secondButton->getButton()->getPosition().y == 181))
		{
			_steps = 1;
		}
		if (_token == thirdButton && (thirdButton->getButton()->getPosition().x == 831 && thirdButton->getButton()->getPosition().y == 258))
		{
			_steps = 1;
		}
		if (_token == fourthButton && (fourthButton->getButton()->getPosition().x == 831 && fourthButton->getButton()->getPosition().y == 181))
		{
			_steps = 1;
		}
	}

	//currentPos++;
	int _targetPos = _token->getCurrentPos() + _steps;
	//auto _node = Node::create();
	float delay = 0.1f;
	auto delayAction = DelayTime::create(delay);
	auto funcCallback = CallFunc::create([this, _token, _targetPos, _node]() {
		log("Delayed Func()");
	if (_token->getCurrentPos() < _targetPos)
	{
		if (category == "BLUE")
			_token->getButton()->setPosition(route[_token->getCurrentPos()]);
		else if (category == "RED")
			_token->getButton()->setPosition(routeRed[_token->getCurrentPos()]);
		if (category == "GREEN")
			_token->getButton()->setPosition(routeGreen[_token->getCurrentPos()]);
		if (category == "YELLOW")
			_token->getButton()->setPosition(routeYellow[_token->getCurrentPos()]);
		auto _nextPos = _token->getCurrentPos();
		_nextPos++;
		_token->setCurrentPos(_nextPos);
	}
	else
	{
		_node->stopActionByTag(3333);
		log("CURRENT_POS: %d, IS_SAFE_POINT: %d", _token->getCurrentPos(), isTokenInSafeZone(_token->getCurrentPos()));
		if (category == "RED" && !isTokenInSafeZone(_token->getCurrentPos()))
		{
			auto _bluePlayer = MainMenu::getBluePlayer();
			auto _greenPlayer = MainMenu::getGreenPlayer();
			auto _yellowPlayer = MainMenu::getYellowPlayer();

			//BLUE
			if (_bluePlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-1 collided with RED");
				_bluePlayer->retrieveToken(1)->setCurrentPos(0);
				_bluePlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-2 collided with RED");
				_bluePlayer->retrieveToken(2)->setCurrentPos(0);
				_bluePlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-3 collided with RED");
				_bluePlayer->retrieveToken(3)->setCurrentPos(0);
				_bluePlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-4 collided with RED");
				_bluePlayer->retrieveToken(4)->setCurrentPos(0);
				_bluePlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//GREEN
			else if (_greenPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-1 collided with RED");
				_greenPlayer->retrieveToken(1)->setCurrentPos(0);
				_greenPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-2 collided with RED");
				_greenPlayer->retrieveToken(2)->setCurrentPos(0);
				_greenPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-3 collided with RED");
				_greenPlayer->retrieveToken(3)->setCurrentPos(0);
				_greenPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-4 collided with RED");
				_greenPlayer->retrieveToken(4)->setCurrentPos(0);
				_greenPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//YELLOW
			else if (_yellowPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-1 collided with RED");
				_yellowPlayer->retrieveToken(1)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-2 collided with RED");
				_yellowPlayer->retrieveToken(2)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-3 collided with RED");
				_yellowPlayer->retrieveToken(3)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-4 collided with RED");
				_yellowPlayer->retrieveToken(4)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}
		}
		if (category == "GREEN" && !isTokenInSafeZone(_token->getCurrentPos()))
		{
			auto _bluePlayer = MainMenu::getBluePlayer();
			auto _redPlayer = MainMenu::getRedPlayer();
			auto _yellowPlayer = MainMenu::getYellowPlayer();

			//BLUE
			if (_bluePlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-1 collided with GREEN");
				_bluePlayer->retrieveToken(1)->setCurrentPos(0);
				_bluePlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-2 collided with GREEN");
				_bluePlayer->retrieveToken(2)->setCurrentPos(0);
				_bluePlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-3 collided with GREEN");
				_bluePlayer->retrieveToken(3)->setCurrentPos(0);
				_bluePlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-4 collided with GREEN");
				_bluePlayer->retrieveToken(4)->setCurrentPos(0);
				_bluePlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//RED
			else if (_redPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-1 collided with GREEN");
				_redPlayer->retrieveToken(1)->setCurrentPos(0);
				_redPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-2 collided with GREEN");
				_redPlayer->retrieveToken(2)->setCurrentPos(0);
				_redPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-3 collided with GREEN");
				_redPlayer->retrieveToken(3)->setCurrentPos(0);
				_redPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-4 collided with GREEN");
				_redPlayer->retrieveToken(4)->setCurrentPos(0);
				_redPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//YELLOW
			else if (_yellowPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-1 collided with GREEN");
				_yellowPlayer->retrieveToken(1)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-2 collided with GREEN");
				_yellowPlayer->retrieveToken(2)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-3 collided with GREEN");
				_yellowPlayer->retrieveToken(3)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-4 collided with GREEN");
				_yellowPlayer->retrieveToken(4)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}
		}
		if (category == "YELLOW" && !isTokenInSafeZone(_token->getCurrentPos()))
		{
			auto _bluePlayer = MainMenu::getBluePlayer();
			auto _greenPlayer = MainMenu::getGreenPlayer();
			auto _redPlayer = MainMenu::getRedPlayer();

			//BLUE
			if (_bluePlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-1 collided with YELLOW");
				_bluePlayer->retrieveToken(1)->setCurrentPos(0);
				_bluePlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-2 collided with YELLOW");
				_bluePlayer->retrieveToken(2)->setCurrentPos(0);
				_bluePlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-3 collided with YELLOW");
				_bluePlayer->retrieveToken(3)->setCurrentPos(0);
				_bluePlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_bluePlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("BLUE-4 collided with YELLOW");
				_bluePlayer->retrieveToken(4)->setCurrentPos(0);
				_bluePlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getBluePlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//GREEN
			else if (_greenPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-1 collided with YELLOW");
				_greenPlayer->retrieveToken(1)->setCurrentPos(0);
				_greenPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-2 collided with YELLOW");
				_greenPlayer->retrieveToken(2)->setCurrentPos(0);
				_greenPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-3 collided with YELLOW");
				_greenPlayer->retrieveToken(3)->setCurrentPos(0);
				_greenPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-4 collided with YELLOW");
				_greenPlayer->retrieveToken(4)->setCurrentPos(0);
				_greenPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//RED
			else if (_redPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-1 collided with YELLOW");
				_redPlayer->retrieveToken(1)->setCurrentPos(0);
				_redPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-2 collided with YELLOW");
				_redPlayer->retrieveToken(2)->setCurrentPos(0);
				_redPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-3 collided with YELLOW");
				_redPlayer->retrieveToken(3)->setCurrentPos(0);
				_redPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-4 collided with YELLOW");
				_redPlayer->retrieveToken(4)->setCurrentPos(0);
				_redPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}
		}
		if (category == "BLUE" && !isTokenInSafeZone(_token->getCurrentPos()))
		{
			auto _redPlayer = MainMenu::getRedPlayer();
			auto _greenPlayer = MainMenu::getGreenPlayer();
			auto _yellowPlayer = MainMenu::getYellowPlayer();

			//RED
			if (_redPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-1 collided with BLUE");
				_redPlayer->retrieveToken(1)->setCurrentPos(0);
				_redPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-2 collided with BLUE");
				_redPlayer->retrieveToken(2)->setCurrentPos(0);
				_redPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-3 collided with BLUE");
				_redPlayer->retrieveToken(3)->setCurrentPos(0);
				_redPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_redPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("RED-4 collided with BLUE");
				_redPlayer->retrieveToken(4)->setCurrentPos(0);
				_redPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getRedPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//GREEN
			else if (_greenPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-1 collided with BLUE");
				_greenPlayer->retrieveToken(1)->setCurrentPos(0);
				_greenPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-2 collided with BLUE");
				_greenPlayer->retrieveToken(2)->setCurrentPos(0);
				_greenPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-3 collided with BLUE");
				_greenPlayer->retrieveToken(3)->setCurrentPos(0);
				_greenPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_greenPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("GREEN-4 collided with BLUE");
				_greenPlayer->retrieveToken(4)->setCurrentPos(0);
				_greenPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getGreenPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}

			//YELLOW
			else if (_yellowPlayer->retrieveToken(1)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-1 collided with BLUE");
				_yellowPlayer->retrieveToken(1)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(1)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(1));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(2)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-2 collided with BLUE");
				_yellowPlayer->retrieveToken(2)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(2)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(2));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(3)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-3 collided with BLUE");
				_yellowPlayer->retrieveToken(3)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(3)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(3));
				hasAdvantageTurn = true;
			}
			else if (_yellowPlayer->retrieveToken(4)->getButton()->getPosition() == _token->getButton()->getPosition())
			{
				log("YELLOW-4 collided with BLUE");
				_yellowPlayer->retrieveToken(4)->setCurrentPos(0);
				_yellowPlayer->retrieveToken(4)->getButton()->setPosition(MainMenu::getYellowPlayerTokenPos(4));
				hasAdvantageTurn = true;
			}
		}
	}
		});
	auto _seq = RepeatForever::create(Sequence::create(delayAction, funcCallback, NULL));
	_seq->setTag(3333);
	_node->runAction(_seq);
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

std::string Player::getCategory()
{
	return category;
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

		currentRollVal = Dice::getInstance()->getLastRollVal();
		log("RollVal: %d", currentRollVal);

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
		if (category == "RED")
		{
			if (firstButton->getButton()->getPosition().x == 322 && firstButton->getButton()->getPosition().y == 683)
			{
				_numTokensInBase++;
			}
			if (secondButton->getButton()->getPosition().x == 322 && secondButton->getButton()->getPosition().y == 606)
			{
				_numTokensInBase++;
			}
			if (thirdButton->getButton()->getPosition().x == 406 && thirdButton->getButton()->getPosition().y == 683)
			{
				_numTokensInBase++;
			}
			if (fourthButton->getButton()->getPosition().x == 406 && fourthButton->getButton()->getPosition().y == 606)
			{
				_numTokensInBase++;
			}
		}
		if (category == "GREEN")
		{
			if (firstButton->getButton()->getPosition().x == 747 && firstButton->getButton()->getPosition().y == 683)
			{
				_numTokensInBase++;
			}
			if (secondButton->getButton()->getPosition().x == 747 && secondButton->getButton()->getPosition().y == 606)
			{
				_numTokensInBase++;
			}
			if (thirdButton->getButton()->getPosition().x == 831 && thirdButton->getButton()->getPosition().y == 683)
			{
				_numTokensInBase++;
			}
			if (fourthButton->getButton()->getPosition().x == 831 && fourthButton->getButton()->getPosition().y == 606)
			{
				_numTokensInBase++;
			}
		}
		if (category == "YELLOW")
		{
			if (firstButton->getButton()->getPosition().x == 747 && firstButton->getButton()->getPosition().y == 258)
			{
				_numTokensInBase++;
			}
			if (secondButton->getButton()->getPosition().x == 747 && secondButton->getButton()->getPosition().y == 181)
			{
				_numTokensInBase++;
			}
			if (thirdButton->getButton()->getPosition().x == 831 && thirdButton->getButton()->getPosition().y == 258)
			{
				_numTokensInBase++;
			}
			if (fourthButton->getButton()->getPosition().x == 831 && fourthButton->getButton()->getPosition().y == 181)
			{
				_numTokensInBase++;
			}
		}

		if (_numTokensInBase == 4 && currentRollVal != 6)
		{
			log("pass to next player");
			MainMenu::passPlayerTurn();
		}
		else if (_numTokensInBase == 4 && currentRollVal == 6)
		{
			currentRollVal = 0;
			setButtonActive(firstButton->getButton(), true);
			setButtonActive(secondButton->getButton(), true);
			setButtonActive(thirdButton->getButton(), true);
			setButtonActive(fourthButton->getButton(), true);

			auto actionBlink = Blink::create(1.0, 1);
			auto _seq = RepeatForever::create(Sequence::create(FadeOut::create(0.2f), FadeIn::create(0.2f), NULL));
			firstButton->getButton()->runAction(_seq);
			secondButton->getButton()->runAction(_seq->clone());
			thirdButton->getButton()->runAction(_seq->clone());
			fourthButton->getButton()->runAction(_seq->clone());
		}
		else if (_numTokensInBase < 4 && currentRollVal != 6)
		{
			auto actionBlink = Blink::create(1.0, 1);
			auto _seq = RepeatForever::create(Sequence::create(FadeOut::create(0.2f), FadeIn::create(0.2f), NULL));

			if (category == "BLUE")
			{
				if (!(firstButton->getButton()->getPosition().x == 321 && firstButton->getButton()->getPosition().y == 258))
				{
					setButtonActive(firstButton->getButton(), true);

					firstButton->getButton()->runAction(_seq->clone());
				}
				if (!(secondButton->getButton()->getPosition().x == 321 && secondButton->getButton()->getPosition().y == 181))
				{
					setButtonActive(secondButton->getButton(), true);

					secondButton->getButton()->runAction(_seq->clone());
				}
				if (!(thirdButton->getButton()->getPosition().x == 405 && thirdButton->getButton()->getPosition().y == 258))
				{
					setButtonActive(thirdButton->getButton(), true);

					thirdButton->getButton()->runAction(_seq->clone());
				}
				if (!(fourthButton->getButton()->getPosition().x == 405 && fourthButton->getButton()->getPosition().y == 181))
				{
					setButtonActive(fourthButton->getButton(), true);

					fourthButton->getButton()->runAction(_seq->clone());
				}
			}
			if (category == "RED")
			{
				if (!(firstButton->getButton()->getPosition().x == 322 && firstButton->getButton()->getPosition().y == 683))
				{
					setButtonActive(firstButton->getButton(), true);

					firstButton->getButton()->runAction(_seq->clone());
				}
				if (!(secondButton->getButton()->getPosition().x == 322 && secondButton->getButton()->getPosition().y == 606))
				{
					setButtonActive(secondButton->getButton(), true);

					secondButton->getButton()->runAction(_seq->clone());
				}
				if (!(thirdButton->getButton()->getPosition().x == 406 && thirdButton->getButton()->getPosition().y == 683))
				{
					setButtonActive(thirdButton->getButton(), true);

					thirdButton->getButton()->runAction(_seq->clone());
				}
				if (!(fourthButton->getButton()->getPosition().x == 406 && fourthButton->getButton()->getPosition().y == 606))
				{
					setButtonActive(fourthButton->getButton(), true);

					fourthButton->getButton()->runAction(_seq->clone());
				}
			}
			if (category == "GREEN")
			{
				if (!(firstButton->getButton()->getPosition().x == 747 && firstButton->getButton()->getPosition().y == 683))
				{
					setButtonActive(firstButton->getButton(), true);

					firstButton->getButton()->runAction(_seq->clone());
				}
				if (!(secondButton->getButton()->getPosition().x == 747 && secondButton->getButton()->getPosition().y == 606))
				{
					setButtonActive(secondButton->getButton(), true);

					secondButton->getButton()->runAction(_seq->clone());
				}
				if (!(thirdButton->getButton()->getPosition().x == 831 && thirdButton->getButton()->getPosition().y == 683))
				{
					setButtonActive(thirdButton->getButton(), true);

					thirdButton->getButton()->runAction(_seq->clone());
				}
				if (!(fourthButton->getButton()->getPosition().x == 831 && fourthButton->getButton()->getPosition().y == 606))
				{
					setButtonActive(fourthButton->getButton(), true);

					fourthButton->getButton()->runAction(_seq->clone());
				}
			}
			if (category == "YELLOW")
			{
				if (!(firstButton->getButton()->getPosition().x == 747 && firstButton->getButton()->getPosition().y == 258))
				{
					setButtonActive(firstButton->getButton(), true);

					firstButton->getButton()->runAction(_seq->clone());
				}
				if (!(secondButton->getButton()->getPosition().x == 747 && secondButton->getButton()->getPosition().y == 181))
				{
					setButtonActive(secondButton->getButton(), true);

					secondButton->getButton()->runAction(_seq->clone());
				}
				if (!(thirdButton->getButton()->getPosition().x == 831 && thirdButton->getButton()->getPosition().y == 258))
				{
					setButtonActive(thirdButton->getButton(), true);

					thirdButton->getButton()->runAction(_seq->clone());
				}
				if (!(fourthButton->getButton()->getPosition().x == 831 && fourthButton->getButton()->getPosition().y == 181))
				{
					setButtonActive(fourthButton->getButton(), true);

					fourthButton->getButton()->runAction(_seq->clone());
				}
			}
		}
		else if (_numTokensInBase < 4 && currentRollVal == 6)
		{
			currentRollVal = 6;
			setButtonActive(firstButton->getButton(), true);
			setButtonActive(secondButton->getButton(), true);
			setButtonActive(thirdButton->getButton(), true);
			setButtonActive(fourthButton->getButton(), true);

			auto actionBlink = Blink::create(1.0, 1);
			auto _seq = RepeatForever::create(Sequence::create(FadeOut::create(0.2f), FadeIn::create(0.2f), NULL));
			firstButton->getButton()->runAction(_seq);
			secondButton->getButton()->runAction(_seq->clone());
			thirdButton->getButton()->runAction(_seq->clone());
			fourthButton->getButton()->runAction(_seq->clone());
		}
	});
	auto const _seq = Repeat::create(Sequence::create(delayAction, funcCallback, NULL), 1);
	Director::getInstance()->getRunningScene()->runAction(_seq);
}


bool Player::isTokenInSafeZone(int _pos)
{
	switch (_pos)
	{
	case 1:
	case 9:
	case 14:
	case 22:
	case 27:
	case 35:
	case 40:
	case 48:
	case 52:
	case 53:
	case 54:
	case 55:
	case 56:
	case 57:
		return true;
		break;

	default:
		return false;
		break;
	}

}