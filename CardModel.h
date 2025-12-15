#ifndef _CARD_MODEL_H_
#define _CARD_MODEL_H_

#include "CardDef.h"
#include "cocos2d.h"

USING_NS_CC;

class CardModel
{
public:
	CardModel(CardSuitType suit, CardFaceType face, Vec2 pos)
		:_suit(suit), _face(face), _position(pos), _isVisible(true), _cardId(generateCardId(suit, face))
	{
	}

	~CardModel() = default;

	int getCardId() const { return _cardId; }
	CardSuitType getSuit() const { return _suit; }
	CardFaceType getFace() const { return _face; }
	Vec2 getPosition() const { return _position; }
	bool isVisible() const { return _isVisible; }

	void setPosition(const Vec2& pos) { _position = pos; }
	void setVisible(bool visible) { _isVisible = visible; }

private:
	int _cardId;						//卡牌ID
	CardSuitType _suit;			//卡牌花色
	CardFaceType _face;			//牌面
	Vec2 _position;					//位置
	bool _isVisible;					//是否可见
};
#endif // !_CARD_MODEL_H_
