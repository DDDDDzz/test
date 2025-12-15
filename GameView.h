#ifndef _GAME_VIEW_H_
#define _GAME_VIEW_H_

#include"CardView.h"
#include"GameModel.h"
#include"MathUtil.h"
#include"UndoManager.h"
class GameView : public cocos2d::Scene
{
public:
    static Scene* createScene(GameModel* gameModel);
    virtual bool init();
    CREATE_FUNC(GameView);
    void cardCreate();
    void createUndoButton();
    void initTouchListener();
    void onPlayerClick(CardView* playCard,CardView* trayCard);
    void onStackClick(CardView* stackCard, CardView* trayCard);
    void updateTrayCardView(CardModel* cardModel);
    void onUndoButtonClicked(Ref* pSender);
    void refreshCardViews();
private:
    MathUtils math;
    GameModel* _gameModel;
    Node* _playerfieldLayer;                     // 主牌区节点
    Node* _stackLayer;                           // 备用牌+底牌堆节点
    CardView* _trayCardView;                    // 当前底牌视图
    std::vector<CardView*> _cardViews;           // 主牌视图
    std::vector<CardView*> _stackCardViews;      // 备用牌视图
};

#endif // !_GAME_VIEW_H_