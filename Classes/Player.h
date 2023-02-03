#ifndef __Player_SCENE_H__
#define __Player_SCENE_H__

#include "cocos2d.h"
#include "Token.h"

USING_NS_CC;

class Player
{
private:

	bool hasWon;
	std::string category;


	//four tokens for each player
	Token* firstButton;
	Token* secondButton;
	Token* thirdButton;
	Token* fourthButton;

	//route
	cocos2d::Vec2 route[57] = { Vec2(529,149),
								Vec2(529,195),
								Vec2(529,243),
								Vec2(529,290),
								Vec2(529,337),
								Vec2(481,384),
								Vec2(434,384),
								Vec2(387,384),
								Vec2(340,384),
								Vec2(293,384),
								Vec2(244,384),
								Vec2(244,431),
								Vec2(244,479),
								Vec2(293,479),
								Vec2(340,479),
								Vec2(387,479),
								Vec2(434,479),
								Vec2(482,479),
								Vec2(528,527),
								Vec2(528,574),
								Vec2(528,621),
								Vec2(528,668),
								Vec2(528,714),
								Vec2(528,763),
								Vec2(576,763),
								Vec2(624,763),
								Vec2(624,716),
								Vec2(624,668),
								Vec2(624,620),
								Vec2(624,574),
								Vec2(624,526),
								Vec2(671,479),
								Vec2(719,479),
								Vec2(765,479),
								Vec2(813,479),
								Vec2(862,479),
								Vec2(906,479),
								Vec2(906,432),
								Vec2(906,385),
								Vec2(860,385),
								Vec2(812,385),
								Vec2(766,385),
								Vec2(718,385),
								Vec2(671,385),
								Vec2(622,337),
								Vec2(622,290),
								Vec2(622,243),
								Vec2(622,195),
								Vec2(623,148),
								Vec2(622,100),
								Vec2(576,100),
								
								Vec2(576,147),
								Vec2(576,195),
								Vec2(576,243),
								Vec2(576,290),
								Vec2(576,337),
								Vec2(576,390) };

	cocos2d::Vec2 routeRed[57] = {	Vec2(293,479),
									Vec2(340,479),
									Vec2(387,479),
									Vec2(434,479),
									Vec2(482,479),
									Vec2(528,527),
									Vec2(528,574),
									Vec2(528,621),
									Vec2(528,668),
									Vec2(528,714),
									Vec2(528,763),
									Vec2(576,763),
									Vec2(624,763),
									Vec2(624,716),
									Vec2(624,668),
									Vec2(624,620),
									Vec2(624,574),
									Vec2(624,526),
									Vec2(671,479),
									Vec2(719,479),
									Vec2(765,479),
									Vec2(813,479),
									Vec2(862,479),
									Vec2(906,479),
									Vec2(906,432),
									Vec2(906,385),
									Vec2(860,385),
									Vec2(812,385),
									Vec2(766,385),
									Vec2(718,385),
									Vec2(671,385),
									Vec2(622,337),
									Vec2(622,290),
									Vec2(622,243),
									Vec2(622,195),
									Vec2(623,148),
									Vec2(622,100),
									Vec2(576,100),
									Vec2(529,100),
									Vec2(529,149),
									Vec2(529,195),
									Vec2(529,243),
									Vec2(529,290),
									Vec2(529,337),
									Vec2(481,384),
									Vec2(434,384),
									Vec2(387,384),
									Vec2(340,384),
									Vec2(293,384),
									Vec2(244,384),
									Vec2(244,431),
	

									Vec2(292,432),
									Vec2(340,432),
									Vec2(387,431),
									Vec2(434,431),
									Vec2(482,431),
									Vec2(531,431), };

	cocos2d::Vec2 routeGreen[57] = { 
									Vec2(624,716),
									Vec2(624,668),
									Vec2(624,620),
									Vec2(624,574),
									Vec2(624,526),
									Vec2(671,479),
									Vec2(719,479),
									Vec2(765,479),
									Vec2(813,479),
									Vec2(862,479),
									Vec2(906,479),
									Vec2(906,432),
									Vec2(906,385),
									Vec2(860,385),
									Vec2(812,385),
									Vec2(766,385),
									Vec2(718,385),
									Vec2(671,385),
									Vec2(622,337),
									Vec2(622,290),
									Vec2(622,243),
									Vec2(622,195),
									Vec2(623,148),
									Vec2(622,100),
									Vec2(576,100),
									Vec2(529,100),
									Vec2(529,149),
									Vec2(529,195),
									Vec2(529,243),
									Vec2(529,290),
									Vec2(529,337),
									Vec2(481,384),
									Vec2(434,384),
									Vec2(387,384),
									Vec2(340,384),
									Vec2(293,384),
									Vec2(244,384),
									Vec2(244,431),
									Vec2(244,479),
									Vec2(293,479),
									Vec2(340,479),
									Vec2(387,479),
									Vec2(434,479),
									Vec2(482,479),
									Vec2(528,527),
									Vec2(528,574),
									Vec2(528,621),
									Vec2(528,668),
									Vec2(528,714),
									Vec2(528,763),
									Vec2(576,763),

									Vec2(576,716),
									Vec2(576,668),
									Vec2(576,621),
									Vec2(576,574),
									Vec2(576,526),
									Vec2(576,474) };

	cocos2d::Vec2 routeYellow[57] ={
									Vec2(860,385),
									Vec2(812,385),
									Vec2(766,385),
									Vec2(718,385),
									Vec2(671,385),
									Vec2(622,337),
									Vec2(622,290),
									Vec2(622,243),
									Vec2(622,195),
									Vec2(623,148),
									Vec2(622,100),
									Vec2(576,100),
									Vec2(529,100),
									Vec2(529,149),
									Vec2(529,195),
									Vec2(529,243),
									Vec2(529,290),
									Vec2(529,337),
									Vec2(481,384),
									Vec2(434,384),
									Vec2(387,384),
									Vec2(340,384),
									Vec2(293,384),
									Vec2(244,384),
									Vec2(244,431),
									Vec2(244,479),
									Vec2(293,479),
									Vec2(340,479),
									Vec2(387,479),
									Vec2(434,479),
									Vec2(482,479),
									Vec2(528,527),
									Vec2(528,574),
									Vec2(528,621),
									Vec2(528,668),
									Vec2(528,714),
									Vec2(528,763),
									Vec2(576,763),
									Vec2(624,763),
									Vec2(624,716),
									Vec2(624,668),
									Vec2(624,620),
									Vec2(624,574),
									Vec2(624,526),
									Vec2(671,479),
									Vec2(719,479),
									Vec2(765,479),
									Vec2(813,479),
									Vec2(862,479),
									Vec2(906,479),
									Vec2(906,432),

									Vec2(860,432),
									Vec2(813,432),
									Vec2(765,432),
									Vec2(719,432),
									Vec2(671,432),
									Vec2(619,432) };

	void moveOneStep(float dt);

	int currentRollVal;

	void setButtonActive(cocos2d::ui::Button* _button, bool _state);
	void Player::setTokenClickEvent(Token* _button, std::string _buttonName);

	bool isTokenInSafeZone(int _pos);
	bool hasAdvantageTurn;

public:
	Player(std::string _spritePath, std::string _category);
	cocos2d::ui::Button* getButton(int _id);

	Token* retrieveToken(int _id);

	void move(Token* _token, int _steps, Node* _node);

	bool hasCompletedGame();

	void playTurn();

	//DEBUG
	std::string getCategory();
};

#endif

