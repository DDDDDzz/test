#include"GameModelFromLevelGenerator.h"

GameModelFromLevelGenerator* GameModelFromLevelGenerator::getInstance()
{
	static GameModelFromLevelGenerator instance;
	return &instance;
}

GameModel* GameModelFromLevelGenerator::generateGameModel(const LevelConfig& config)
{
	GameModel* gameModel = new GameModel();

	//生成主牌区卡牌
	for (auto cardConfig : config.playfieldCards)
	{
		CardModel* card = new CardModel(
			cardConfig.cardSuit,
			cardConfig.cardFace,
			cardConfig.position
		);
		gameModel->playfieldCards.push_back(card);
	}

	//生成备用牌堆
	for (auto cardConfig : config.stackCards)
	{
		CardModel* card = new CardModel(
			cardConfig.cardSuit,
			cardConfig.cardFace,
			cardConfig.position
		);
		gameModel->stackCards.push_back(card);
	}
	return gameModel;
}