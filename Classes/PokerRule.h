#ifndef __POKERRULE_H__
#define __POKERRULE_H__

/*
���ƹ���:
-1 �����ϳ��ƹ���
0. ��С���������
1.���ţ���С˳��
2.һ�ԣ���С˳��
3.���ţ���С˳��
4.˳�ӣ���5�ţ�����ͬ��С�����
5.˫˳����3���ԣ�����ͬ��С����� ��
6.����һ�ŵ���  ����һ��
7.�Ĵ����ŵ���  �Ĵ�����

*/

#include <vector>
#include "Poker.h"
#include "cocos2d.h"
USING_NS_CC;

enum PokerRuleType
{
	PokerRuleError = -1,				//-1 �����ϳ��ƹ���
	PokerRuleDoubleKing,				//0. ��С���������
	PokerRuleSingle,					//1.���ţ���С˳��
	PokerRuleDouble,					//2.һ�ԣ���С˳��
	PokerRuleTrouble,				//3.���ţ���С˳��
	PokerRuleUltra,					//4.������ͬ  ը��
	PokerRuleLine,					//5.˳�ӣ���5�ţ�����ͬ��С�����
	PokerRuleDoubleLine,				//6.˫˳����3���ԣ�����ͬ��С����� ��
	PokerRuleTroubleWithSingle,		//7.����һ�ŵ���
	PokerRuleTroubleWithDouble,		//8.����һ��                             
	PokerRuleUltraWithTwoSingle,		//9.�Ĵ����ŵ���  
	PokerRuleUltraWithTwoDouble,		//10.�Ĵ�����
	PokerRulePlane					//11�ɻ�   6  8 10 ����
};

class PokerRule
{
public:
	//�ж���ѡ����������������
	static PokerRuleType checkPoker(const vector<Poker> &pokers);
	//�Ƚ��ƵĴ�С
	static bool compare(const vector<Poker> &last, const vector<Poker> &now);

private:

};





#endif // !__POKERRULE_H__

