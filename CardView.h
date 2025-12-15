#ifndef _CARD_VIEW_H_
#define _CARD_VIEW_H_

#include "cocos2d.h"
#include "CardModel.h"

USING_NS_CC;

class CardView:public Sprite
{
public:
	CardView()=default;
	~CardView()=default;

	static CardView* create(CardModel* cardModel);
	bool init(CardModel* cardmodel);

	void playMoveToAnimation(const Vec2 targetPos, std::function<void()> callback);
	CardModel* getCardModel() {
		return _cardModel;
	}
private:
	CardModel* _cardModel;
};

#endif // !_CARD_VIEW_H_
