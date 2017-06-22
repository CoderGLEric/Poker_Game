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
	void catchPoker(PopkerSpirte*pokerSprite);//ץ��
	void obtainSurplusPokers(PopkerSpirte*pokerSprite);//��õ���
	void vieForLairdShip();//������
	vector<Poker> outPoker(vector<Poker> lastPlayerOutPokers);//����

	void refreUI();//ˢ���Ƶ�λ��
public:
	int playerIdx;//������ұ��
	bool mLairdShip;//�������
	multimap<int, PopkerSpirte*,greater<int>> mPokers;//������
};


#endif // !__PLAYER_H__
