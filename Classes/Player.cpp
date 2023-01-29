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

		MainMenu::passPlayerTurn();
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
	firstButton->getButton()->setVisible(true);
	secondButton->getButton()->stopAllActions();
	secondButton->getButton()->setVisible(true);
	thirdButton->getButton()->stopAllActions();
	thirdButton->getButton()->setVisible(true);
	fourthButton->getButton()->stopAllActions();
	fourthButton->getButton()->setVisible(true);

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

			auto actionBlink = Blink::create(1.0, 3);
			auto _seq = RepeatForever::create(Sequence::create(actionBlink, NULL, NULL));
			firstButton->getButton()->runAction(_seq);
			secondButton->getButton()->runAction(_seq->clone());
			thirdButton->getButton()->runAction(_seq->clone());
			fourthButton->getButton()->runAction(_seq->clone());
		}
		else if (_numTokensInBase < 4 && currentRollVal != 6)
		{
			auto actionBlink = Blink::create(1.0, 3);
			auto _seq = RepeatForever::create(Sequence::create(actionBlink, NULL, NULL));

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

			auto actionBlink = Blink::create(1.0, 3);
			auto _seq = RepeatForever::create(Sequence::create(actionBlink, NULL, NULL));
			firstButton->getButton()->runAction(_seq);
			secondButton->getButton()->runAction(_seq->clone());
			thirdButton->getButton()->runAction(_seq->clone());
			fourthButton->getButton()->runAction(_seq->clone());
		}
	});
	auto const _seq = Repeat::create(Sequence::create(delayAction, funcCallback, NULL), 1);
	Director::getInstance()->getRunningScene()->runAction(_seq);
}
