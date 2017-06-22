#include "PopkerSpirte.h"
#include "AppMicraos.h"

PopkerSpirte * PopkerSpirte::createSprite(CCSize size, int num, PokerColor color)
{
	PopkerSpirte *sprite = new PopkerSpirte;
	if (sprite && sprite->init(size,num,color))
	{
		sprite->autorelease();
		return sprite;
	}
	else
	{
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}
}

bool PopkerSpirte::init(CCSize size, int num, PokerColor color)
{
	mPoker = Poker(num, color);
	this->isChoosed = false;
	setAnchorPoint(ccp(0, 0));
	num = num == 15 ? 2 : num;
	string str;
	switch (color)
	{
	case PokerColor_Red:
		str = UTEXT("红\n");
		break;
	case PokerColor_Black:
		str = UTEXT("黑\n");
		break;
	case PokerColor_Flower:
		str = UTEXT("花\n");
		break;
	case PokerColor_Piece:
		str = UTEXT("块\n");
		break;
	}

	//按钮标题  
	LabelTTF* title = LabelTTF::create(" ", "Marker Felt", 25);
	//正常状态下的按钮图片  
	Scale9Sprite* btnNormal = Scale9Sprite::create("floor.jpg");
	//创建按钮，按钮的大小根据标题自动调整  
	ControlButton *btn = ControlButton::create(title, btnNormal);
	btn->setTag(102);
	//强制设置按钮大小，如果按钮超过这个范围，则自动扩大  
	btn->setPreferredSize(size);
	//btn->setAnchorPoint(ccp(0, 0));
	btn->setPosition(ccp(0, 0));
	btn->addTargetWithActionForControlEvents(this, cccontrol_selector(PopkerSpirte::touchUpInside), Control::EventType::TOUCH_UP_INSIDE);
	addChild(btn);
	//16(小王) 17(大王)//11(J) 12(Q) 13(K) 14(尖)
	if (num==16 || num == 17)
	{
		str = num == 16 ? string(UTEXT("小\n王")) : string(UTEXT("大\n王"));
	}
	else if (num == 11)
	{
		str += string("J");
	}
	else if (num == 12)
	{
		str += string("Q");
	}
	else if (num == 13)
	{
		str += string("K");
	}
	else if (num == 14)
	{
		str += string("A");
	}
	else
	{
		str += to_string(num);	
	}
	LabelTTF* numberTTF = LabelTTF::create(str.c_str(), "Marker Felt", 30);
	numberTTF->setPosition(ccp(10, size.height-10));
	btn->addChild(numberTTF);
	return true;
}

void PopkerSpirte::touchUpInside(CCObject* sender, Control::EventType controlEvent)
{
	ControlButton *btn = (ControlButton *)sender;
	int distance;
	if (this->isChoosed)
	{
		this->isChoosed = false;
		distance = -10;
	}
	else
	{
		this->isChoosed = true;
		distance = 10;
	}
	CCJumpBy *to = CCJumpBy::create(0.2, ccp(0, distance),1,1);
	btn->runAction(to);
}
