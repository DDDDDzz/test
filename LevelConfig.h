#ifndef _LEVEL_CONFIG_H_
#define _LEVEL_CONFIG_H_

#include "CardDef.h"
#include "cocos2d.h"

USING_NS_CC;

struct CardConfig
{
	CardFaceType cardFace;
	CardSuitType cardSuit;
	Vec2 position;
};

class LevelConfig
{
public:
	LevelConfig() = default;
	~LevelConfig() = default;

	std::vector<CardConfig>playfieldCards;				//÷˜≈∆«¯ø®≈∆≈‰÷√
	std::vector<CardConfig>stackCards;						// ÷≈∆∂—≈‰÷√
};

#endif // !_LEVEL_CONFIG_H_
