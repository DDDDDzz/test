#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_
#include"GameView.h"
#include"LevelConfig.h"
#include"GameModel.h"
class GameController
{
public:
    // 启动游戏，加载指定关卡配置并初始化
    void startGame(int levelId);

    cocos2d::Scene* getGameView() { return _gameView; }

private:
    cocos2d::Scene* _gameView;
    LevelConfig _currentLevelConfig;
    GameModel* _gameModel;
};

#endif //  _GAME_CONTROLLER_H_
