#ifndef _GAME_MODEL_H_
#define _GAME_MODEL_H_

#include "CardModel.h"

USING_NS_CC;

class GameModel
{
public:
	GameModel() = default;
	~GameModel()
	{
		for (auto card : playfieldCards) delete card;
		for (auto card : stackCards)delete card;
		delete trayCard;
	}
	
	std::vector<CardModel*> playfieldCards;				//Ö÷ÅÆÇø¿¨ÅÆ
	std::vector<CardModel*> stackCards;					//±¸ÓÃÅÆ¶Ñ
	std::stack<CardModel*>trayCards;							//µ×ÅÆ¶Ñ
	CardModel* trayCard = nullptr;				//µ×ÅÆ
	int currentStackCardIndex = 0;								//µ±Ç°µ×ÅÆË÷Òý
};
#endif // !_GAME_MODEL_H_
