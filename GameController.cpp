#include"GameController.h"
#include"LevelConfigLoader.h"
#include"GameModelFromLevelGenerator.h"
void GameController::startGame(int levelId)
{
	_currentLevelConfig = LevelConfigLoader::loadLevelConfig(levelId);
	_gameModel = GameModelFromLevelGenerator::getInstance()->generateGameModel(_currentLevelConfig);
	_gameView = GameView::createScene(_gameModel);
}

