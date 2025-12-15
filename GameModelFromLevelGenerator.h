#ifndef _GAME_MODEL_FROM_LEVEL_GENERATOR_H_
#define  _GAME_MODEL_FROM_LEVEL_GENERATOR_H_

#include"GameModel.h"
#include"LevelConfig.h"

class GameModelFromLevelGenerator
{
public:
	static GameModelFromLevelGenerator* getInstance();

	GameModel* generateGameModel(const LevelConfig& config);

private:
	GameModelFromLevelGenerator() = default;
	~GameModelFromLevelGenerator() = default;
};


#endif // ! _GAME_MODEL_FROM_LEVEL_GENERATOR_H_
