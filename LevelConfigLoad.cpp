#include "LevelConfigLoader.h"

LevelConfig LevelConfigLoader::loadLevelConfig(int levelId)
{
	LevelConfig config;
	//πÿø®≈‰÷√
	if (levelId == 1)
	{
		//÷˜≈∆«¯≈‰÷√
		config.playfieldCards =
		{
			{CardFaceType::CFT_KING, CardSuitType::CST_CLUBS, {250, 1000}},
			{CardFaceType::CFT_THREE, CardSuitType::CST_CLUBS, {300, 800}},
			{CardFaceType::CFT_THREE, CardSuitType::CST_DIAMONDS, {350, 600}},
			{CardFaceType::CFT_THREE, CardSuitType::CST_CLUBS, {850, 1000}},
			{CardFaceType::CFT_THREE, CardSuitType::CST_CLUBS, {800, 800}},
			{CardFaceType::CFT_TWO, CardSuitType::CST_SPADES, {750, 600}}
		};

		// ÷≈∆∂—≈‰÷√
		config.stackCards =
		{
			{CardFaceType::CFT_THREE, CardSuitType::CST_CLUBS, {0, 0}},
			{CardFaceType::CFT_ACE, CardSuitType::CST_HEARTS, {0, 0}},
			{CardFaceType::CFT_FOUR, CardSuitType::CST_CLUBS, {0, 0}}
		};
	}
	return config;
}