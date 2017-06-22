#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
using namespace std;
#include <map>
#include "Poker.h"
#include <functional>
#include <iterator>
#include "PopkerSpirte.h"
#include "PokerRule.h"

class Player
{
public:
	void catchPoker(PopkerSpirte*pokerSprite);//抓牌
	void obtainSurplusPokers(PopkerSpirte*pokerSprite);//获得底牌
	void vieForLairdShip();//抢地主
	vector<Poker> outPoker(vector<Poker> lastPlayerOutPokers);//出牌

	void refreUI();//刷新牌的位置
public:
	int playerIdx;//几号玩家标记
	bool mLairdShip;//地主标记
	multimap<int, PopkerSpirte*,greater<int>> mPokers;//持有牌
};


#endif // !__PLAYER_H__
