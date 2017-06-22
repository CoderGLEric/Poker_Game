#include "Player.h"

void Player::catchPoker(PopkerSpirte*pokerSprite)//抓牌
{
	mPokers.insert(make_pair(pokerSprite->mPoker.mNum, pokerSprite));
}

void Player::obtainSurplusPokers(PopkerSpirte * pokerSprite)
{
	mPokers.insert(make_pair(pokerSprite->mPoker.mNum, pokerSprite));
	this->refreUI();
}

void Player::vieForLairdShip()//抢地主
{
	this->mLairdShip = true;
}

vector<Poker> Player::outPoker(vector<Poker> lastPlayerOutPokers)//出牌
{
	vector<Poker> m;
	vector<Poker> now;
	multimap<int, PopkerSpirte*, greater<int>> v;
	list<PopkerSpirte*> uiv;
	for (multimap<int, PopkerSpirte*, greater<int>>::iterator it = mPokers.begin(); it != mPokers.end(); ++it)
	{
		if ((*it).second->isChoosed)
		{
			uiv.push_back((*it).second);
			now.push_back((*it).second->mPoker);
		}
		else
		{
			v.insert(make_pair((*it).second->mPoker.mNum, (*it).second));
		}
	}

	//查看出牌符合规则
	if (lastPlayerOutPokers.empty())
	{
		PokerRuleType type = PokerRule::checkPoker(now);
		log("now type==%d", type);
		if (type == -1)
		{
			log("out poker is wrong");
			//出牌错误还是当前玩家出牌
			return m;
		}
	}
	else
	{
		PokerRuleType type = PokerRule::checkPoker(now);
		log("now type==%d", type);
		if (type == -1)
		{
			log("out poker is wrong");
			//出牌错误还是当前玩家出牌
			return m;
		}
		bool isTrue = PokerRule::compare(lastPlayerOutPokers, now);
		log("isTrue === %d", isTrue);
		if (!isTrue)
		{
			log("out poker is tai xiao l! laji!");
			//出牌错误还是当前玩家出牌
			return m;
		}
	}
	lastPlayerOutPokers.swap(now);

	mPokers.clear();
	mPokers.swap(v);
	for (list<PopkerSpirte*>::iterator it = uiv.begin(); it != uiv.end(); ++it)
	{
		(*it)->removeAllChildrenWithCleanup(true);
	}
	this->refreUI();
	return lastPlayerOutPokers;

}

void Player::refreUI()
{
	int distance = 20;
	int w = 45;
	int h = 120;
	int space = 30;
	int y = 300;
	int i = 0;
	if (playerIdx == 2)
	{
		distance = 450;
		y = 50;
	}
	if (playerIdx == 3)
	{
		distance = 950;
	}
	for (multimap<int, PopkerSpirte*, greater<int>>::iterator it = mPokers.begin(); it != mPokers.end(); ++it)
	{
		(*it).second->setZOrder(i++);
		(*it).second->setPosition(Point(distance += space, y));
	}
}
