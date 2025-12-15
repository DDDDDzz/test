#ifndef _LEVEL_CONFIG_LOADER_H_
#define _LEVEL_CONFIG_LOADER_H_

#include"LevelConfig.h"
#include"cocos2d.h"

USING_NS_CC;

class LevelConfigLoader
{
public:
	static LevelConfig loadLevelConfig(int levelId);
};

#endif // !_LEVEL_CONFIG_LOADER_H_
