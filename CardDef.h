#ifndef  _CARD_DEF_H_
#define _CARD_DEF_H_

//花色类型
enum CardSuitType
{
    CS_NONE = -1,
    CST_CLUBS,								//梅花
    CST_DIAMONDS,						//方块
    CST_HEARTS,							//红桃
    CST_SPADES,							//黑桃
    CST_NUM_CARD_SUIT_TYPE	//花色类型的总数
};

// 正面类型
enum CardFaceType
{
    CFT_NONE = -1,
    CFT_ACE,
    CFT_TWO,
    CFT_THREE,
    CFT_FOUR,
    CFT_FIVE,
    CFT_SIX,
    CFT_SEVEN,
    CFT_EIGHT,
    CFT_NINE,
    CFT_TEN,
    CFT_JACK,
    CFT_QUEEN,
    CFT_KING,
    CFT_NUM_CARD_FACE_TYPES
};
//给每个卡牌编号
static int generateCardId(CardSuitType suit, CardFaceType face)
{
    return static_cast<int>(suit) * 13 + static_cast<int>(face);
}
#endif // ! CARD_DEF_H
