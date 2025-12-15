#ifndef UNDO_MODEL_H
#define UNDO_MODEL_H

#include "CardModel.h"
#include <stack>

// 操作类型枚举：区分是主牌区还是stack区的卡牌操作
enum class OperationType {
    PLAYER_FIELD_CARD,  // 主牌区卡牌移动
    STACK_CARD          // stack区卡牌移动
};

class UndoModel {
public:
    UndoModel(OperationType type, CardModel* movedCard) :
        _opType(type), _movedCard(movedCard) {
    }

    OperationType getOpType() const { return _opType; }
    CardModel* getMovedCard() const { return _movedCard; }
private:
    OperationType _opType;          // 操作类型
    CardModel* _movedCard;          // 被移动的卡牌模型
};

#endif // UNDO_MODEL_H