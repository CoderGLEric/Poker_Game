#ifndef __POPKERSPIRTE_H__
#define __POPKERSPIRTE_H__

#include "cocos2d.h"
USING_NS_CC;
#include "Poker.h"
#include "extensions/cocos-ext.h"
USING_NS_CC_EXT;


class PopkerSpirte: public Sprite
{
public:
	static PopkerSpirte *createSprite(CCSize size,int num, PokerColor color);
	virtual bool init(CCSize size,int num,PokerColor color);
	
	void touchUpInside(CCObject* sender, Control::EventType controlEvent);
public:
	bool isChoosed;
	Poker mPoker;
};




#endif // !__POPKERSPIRTE_H__
