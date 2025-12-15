#include"GameView.h"

USING_NS_CC;

Scene* GameView::createScene(GameModel* gameModel)
{
    auto scene= GameView::create();
    scene->_gameModel = gameModel;
    scene->_trayCardView = nullptr;
    scene->cardCreate();
    scene->createUndoButton();
    scene->initTouchListener();
    return scene;
}

bool GameView::init()
{
    if (!Scene::init()) { return false; }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    // 1. 主牌区布局
    _playerfieldLayer = LayerColor::create(Color4B::GRAY);
    _playerfieldLayer->setContentSize(Size(1080.0f, 1500.0f));
    _playerfieldLayer->setPosition(0.0f, 580.0f);
    addChild(_playerfieldLayer);
    // 2. 备用牌+底牌堆区布局
    _stackLayer = LayerColor::create(Color4B::BLUE);
    _stackLayer->setContentSize(Size(1080.0f, 580.0f));
    _stackLayer->setPosition(0.0f, 0.0f);
    addChild(_stackLayer);
    return true;
}
    
void GameView::cardCreate()
{
    _cardViews.clear();
    _stackCardViews.clear();
    for (auto cardModel : _gameModel->playfieldCards)
    {
        auto cardView = CardView::create(cardModel);
        cardView->setPosition(cardModel->getPosition());
        cardView->setContentSize(Size(182.0f, 282.0f));
        cardView->setAnchorPoint(Vec2(0, 0));
        cardView->setTag(cardModel->getCardId());
        _playerfieldLayer->addChild(cardView);
        _cardViews.push_back(cardView);
    }
    int idx=1;
    for (auto cardModel : _gameModel->stackCards)
    {
        auto cardView = CardView::create(cardModel);
        cardView->setPosition(100*idx,_stackLayer->getContentSize().height/2);
        cardView->setContentSize(Size(182.0f, 282.0f));
        cardView->setAnchorPoint(Vec2(0, 0));
        cardView->setTag(cardModel->getCardId());
        _stackLayer->addChild(cardView);
        _stackCardViews.push_back(cardView);
        idx++;
    }
    if (!_gameModel->trayCards.empty())
    {
        auto initTrayModel = _gameModel->trayCards.top();
        updateTrayCardView(initTrayModel);
    }
}

void GameView::updateTrayCardView(CardModel* cardModel)
{
    if (_trayCardView != nullptr) {
        _trayCardView->removeFromParent();
        _trayCardView = nullptr;
    }

    // 2. 创建新的trayCardView（使用卡牌模型数据）
    _trayCardView = CardView::create(cardModel);
    if (_trayCardView == nullptr) {
        return;
    }
    _trayCardView->setContentSize(Size(182.0f, 282.0f)); 
    _trayCardView->setAnchorPoint(Vec2(0, 0)); 
    _trayCardView->setPosition(_stackLayer->getContentSize() / 2.0f);
    _trayCardView->setLocalZOrder(10);
    _trayCardView->setTag(cardModel->getCardId()); // 可选：设置tag

    _stackLayer->addChild(_trayCardView);
}

void GameView::createUndoButton() 
{
    MenuItemFont::setFontName("Marker Felt");
    MenuItemFont* label = MenuItemFont::create("回退",CC_CALLBACK_1(GameView::onUndoButtonClicked,this));
    label->setScale(1.7);
    label->setColor(Color3B::BLACK);

    Menu* newMenu = Menu::create(label, nullptr);
    newMenu->setPosition(900, _stackLayer->getContentSize().height / 2);
    this->addChild(newMenu);
}

void GameView::initTouchListener()
{
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true); // 恢复事件吞噬，避免穿透
    listener->onTouchBegan = [this](Touch* touch, Event* event){
            bool isTouchCard = false;
            Vec2 touchWorldPos = touch->getLocation();
            for (auto cardView : _cardViews){
                if (cardView){
                    Vec2 touchLocalPos = _playerfieldLayer->convertToNodeSpace(touchWorldPos);
                    Rect cardRect(cardView->getPositionX()-91 , cardView->getPositionY()-141 , 182,282);
                    if (cardRect.containsPoint(touchLocalPos)){
                        GameView::onPlayerClick(cardView, _trayCardView);
                        isTouchCard = true;
                        break;
                    }
                }
            }
            for (auto cardView : _stackCardViews) {
                if (cardView) {
                    Vec2 touchLocalPos = _stackLayer->convertToNodeSpace(touchWorldPos);
                    Rect cardRect(cardView->getPositionX() - 91, cardView->getPositionY() - 141, 182, 282);
                    if (cardRect.containsPoint(touchLocalPos)) {
                        onStackClick(cardView, _trayCardView);
                        isTouchCard = true;
                        break;
                    }
                }
            }
            return isTouchCard;
        };
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithFixedPriority(listener, -1);
}

void GameView::onPlayerClick(CardView* playCard, CardView* trayCard)
{
    if (_gameModel->trayCards.empty()) {
        return;
    }
    CardModel* trayCardModel = _gameModel->trayCards.top();
    if (math.isFaceContinuous(playCard->getCardModel()->getFace(), trayCardModel->getFace()))
    {
        UndoModel undoModel(OperationType::PLAYER_FIELD_CARD, playCard->getCardModel());
        UndoManager::getInstance()->recordUndo(undoModel);

        CardModel* playCardModel = playCard->getCardModel();
        _gameModel->trayCards.push(playCardModel);
        auto it = std::remove(_gameModel->playfieldCards.begin(), _gameModel->playfieldCards.end(), playCardModel);
        _gameModel->playfieldCards.erase(it, _gameModel->playfieldCards.end());

        playCard->removeFromParent();
        auto viewIt = std::remove(_cardViews.begin(), _cardViews.end(), playCard);
        _cardViews.erase(viewIt, _cardViews.end());
        updateTrayCardView(playCardModel);
    }
}

void GameView::onStackClick(CardView* stackCard, CardView* trayCard)
{
    UndoModel undoModel(OperationType::STACK_CARD, stackCard->getCardModel());
    UndoManager::getInstance()->recordUndo(undoModel);

    CardModel* stackCardModel = stackCard->getCardModel();
    _gameModel->trayCards.push(stackCardModel);
    auto it = std::remove(_gameModel->stackCards.begin(), _gameModel->stackCards.end(), stackCardModel);
    _gameModel->stackCards.erase(it, _gameModel->stackCards.end());
    stackCard->removeFromParent();
    auto viewIt = std::remove(_stackCardViews.begin(), _stackCardViews.end(), stackCard);
    _stackCardViews.erase(viewIt, _stackCardViews.end());
    updateTrayCardView(stackCardModel);
}
void GameView::onUndoButtonClicked(Ref* pSender)
{
    // 1. 获取UndoManager实例，判断是否有可撤销的操作
    UndoManager* undoMgr = UndoManager::getInstance();
    if (!undoMgr->hasUndo()) {
        CCLOG("没有可回退的操作！");
        return;
    }

    // 2. 撤销上一步操作
    UndoModel* undoModel = undoMgr->undo();
    if (undoModel == nullptr) {
        return;
    }

    // 3. 恢复游戏模型的状态（核心修正：移除冗余的底牌push）
    CardModel* movedCard = undoModel->getMovedCard();

    // 3.1 弹出当前的底牌（仅这一步，即可恢复到操作前的底牌）
    if (!_gameModel->trayCards.empty()) {
        _gameModel->trayCards.pop();
    }

    // 3.2 将被移动的卡牌放回原来的容器
    if (undoModel->getOpType() == OperationType::PLAYER_FIELD_CARD) {
        // 放回主牌区（添加到容器末尾）
        _gameModel->playfieldCards.push_back(movedCard);
    }
    else if (undoModel->getOpType() == OperationType::STACK_CARD) {
        // 放回stack区（添加到容器末尾，可根据需求调整位置）
        _gameModel->stackCards.push_back(movedCard);
    }

    // 4. 刷新界面（重新创建卡牌视图）
    refreshCardViews();

    // 5. 释放动态分配的UndoModel（避免内存泄漏）
    delete undoModel;
}

void GameView::refreshCardViews()
{
    // 1. 移除所有现有卡牌视图
    for (auto cardView : _cardViews) {
        if (cardView) {
            cardView->removeFromParent();
        }
    }
    for (auto cardView : _stackCardViews) {
        if (cardView) {
            cardView->removeFromParent();
        }
    }
    // 移除底牌视图
    if (_trayCardView != nullptr) {
        _trayCardView->removeFromParent();
        _trayCardView = nullptr;
    }

    // 2. 清空视图容器
    _cardViews.clear();
    _stackCardViews.clear();

    // 3. 重新创建卡牌视图（复用cardCreate的逻辑）
    cardCreate();
}
