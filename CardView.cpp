#include"CardView.h"
#include"cocos2d.h"

CardView* CardView::create(CardModel* cardModel)
{
	auto cardView = new CardView();
	if (cardView && cardView->init(cardModel))
	{
		cardView->autorelease();
		return cardView;
	}

	delete cardView;
	return nullptr;
}

bool CardView::init(CardModel* cardModel)
{
	if (!Sprite::init()) return false;
	auto general = Sprite::create("card_general.png");
	addChild(general);
	_cardModel = cardModel;
	std::string suitStr[] = { "suits/club.png","suits/diamond.png", "suits/heart.png", "suits/spade.png" };
	std::string number[] = { "A","2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	CardSuitType suit = cardModel->getSuit();
	auto suitView = Sprite::create(suitStr[static_cast<int>(suit)].c_str());
	suitView->setPosition( 60,80);
	std::string bigNumberPath;
	std::string smallNumberPath;
	if (suit == CardSuitType::CST_CLUBS || suit == CardSuitType::CST_SPADES)
	{
		bigNumberPath=("number/big_black_"+number[static_cast<int>(cardModel->getFace())] + ".png").c_str();
		smallNumberPath = ("number/small_black_"+ number[static_cast<int>(cardModel->getFace())] + ".png").c_str();
	}
	if (suit == CardSuitType::CST_DIAMONDS || suit == CardSuitType::CST_HEARTS)
	{
		bigNumberPath = ("number/big_red_" + number[static_cast<int>(cardModel->getFace())] + ".png").c_str();
		smallNumberPath = ("number/small_red_" + number[static_cast<int>(cardModel->getFace())] + ".png").c_str();
	}
	auto bigNumberView = Sprite::create(bigNumberPath);
	auto smallNumberView = Sprite::create(smallNumberPath);
	bigNumberView->setPosition(this->getContentSize() .width/ 2,this->getContentSize().height/2-10);
	smallNumberView->setPosition(-60,80);
	this->addChild(suitView);
	this->addChild(bigNumberView);
	this->addChild(smallNumberView);
	return true;
}